#include "cpu.h"
#include "mmu.h"
#include "ppu.h"
#include "apu.h"
#include "core_state.h"
#include <stdint.h>
#include <string.h>

// CPU Flags
#define FLAG_Z 0x80
#define FLAG_N 0x40
#define FLAG_H 0x20
#define FLAG_C 0x10

#define SET_FLAG(cpu,f) ((cpu)->freg|=(f))
#define CLEAR_FLAG(cpu,f) ((cpu)->freg&=~(f))
#define UPDATE_FLAG(cpu,f,cond) ((cond)?SET_FLAG(cpu,f):CLEAR_FLAG(cpu,f))

// Register helpers
static inline uint16_t get_bc(gb_cpu_t *cpu){return (cpu->b<<8)|cpu->c;}
static inline void set_bc(gb_cpu_t *cpu,uint16_t val){cpu->b=val>>8; cpu->c=val&0xFF;}
static inline uint16_t get_de(gb_cpu_t *cpu){return (cpu->d<<8)|cpu->e;}
static inline void set_de(gb_cpu_t *cpu,uint16_t val){cpu->d=val>>8; cpu->e=val&0xFF;}
static inline uint16_t get_hl(gb_cpu_t *cpu){return (cpu->h<<8)|cpu->l;}
static inline void set_hl(gb_cpu_t *cpu,uint16_t val){cpu->h=val>>8; cpu->l=val&0xFF;}

// Stack helpers
static inline void push_word(gb_cpu_t *cpu, mmu_t *mmu, uint16_t val){
    gb_mmu_write_byte(mmu,--cpu->sp,(val>>8)&0xFF);
    gb_mmu_write_byte(mmu,--cpu->sp,val&0xFF);
}
static inline uint16_t pop_word(gb_cpu_t *cpu, mmu_t *mmu){
    uint16_t val = gb_mmu_read_byte(mmu,cpu->sp++);
    val |= gb_mmu_read_byte(mmu,cpu->sp++)<<8;
    return val;
}

// Forward CB executor
static int gb_cpu_execute_cb(uint8_t cb_opcode, gb_cpu_t *cpu, core_state_t *state);

// Reset CPU
void gb_cpu_reset(gb_cpu_t *cpu){
    if(!cpu) return;
    memset(cpu,0,sizeof(gb_cpu_t));
    cpu->sp=0xFFFE;
    cpu->pc=0x0100;
    cpu->ime_enabled=0;
}

// Step CPU
void gb_cpu_step(gb_cpu_t *cpu, core_state_t *state){
    if(!cpu||!state||!state->mmu) return;

    uint8_t opcode = gb_mmu_read_byte(state->mmu,cpu->pc++);
    int cycles=0;

    if(opcode==0xCB){
        uint8_t cb_opcode=gb_mmu_read_byte(state->mmu,cpu->pc++);
        cycles=gb_cpu_execute_cb(cb_opcode,cpu,state);
    }else{
        switch(opcode){
            case 0x00: cycles=4; break; // NOP
            case 0x01: cpu->c=gb_mmu_read_byte(state->mmu,cpu->pc++);
                     cpu->b=gb_mmu_read_byte(state->mmu,cpu->pc++); cycles=12; break; // LD BC,nn
            case 0x02: gb_mmu_write_byte(state->mmu,get_bc(cpu),cpu->a); cycles=8; break; // LD (BC),A
            case 0x03: set_bc(cpu,get_bc(cpu)+1); cycles=8; break; // INC BC
            case 0x04: cpu->b++; UPDATE_FLAG(cpu,FLAG_Z,cpu->b==0);
                     CLEAR_FLAG(cpu,FLAG_N); UPDATE_FLAG(cpu,FLAG_H,(cpu->b&0x0F)==0); cycles=4; break; // INC B
            case 0x05: cpu->b--; UPDATE_FLAG(cpu,FLAG_Z,cpu->b==0);
                     SET_FLAG(cpu,FLAG_N); UPDATE_FLAG(cpu,FLAG_H,(cpu->b&0x0F)==0x0F); cycles=4; break; // DEC B
            case 0x06: cpu->b=gb_mmu_read_byte(state->mmu,cpu->pc++); cycles=8; break; // LD B,n
            case 0x07:{ uint8_t c=cpu->a>>7; cpu->a=(cpu->a<<1)|c; UPDATE_FLAG(cpu,FLAG_C,c); CLEAR_FLAG(cpu,FLAG_N|FLAG_H|FLAG_Z); cycles=4;}break; // RLCA
            case 0x08:{ uint16_t addr=gb_mmu_read_byte(state->mmu,cpu->pc++);
                        addr|=gb_mmu_read_byte(state->mmu,cpu->pc++)<<8;
                        gb_mmu_write_byte(state->mmu,addr,cpu->sp&0xFF);
                        gb_mmu_write_byte(state->mmu,addr+1,cpu->sp>>8);
                        cycles=20;}break; // LD (nn),SP
            case 0x09:{ uint16_t hl=get_hl(cpu); uint16_t bc=get_bc(cpu); uint32_t res=hl+bc;
                        CLEAR_FLAG(cpu,FLAG_N); UPDATE_FLAG(cpu,FLAG_H,(hl&0x0FFF)+(bc&0x0FFF)>0x0FFF);
                        UPDATE_FLAG(cpu,FLAG_C,res>0xFFFF); set_hl(cpu,res&0xFFFF); cycles=8;}break; // ADD HL,BC
            case 0x0A: cpu->a=gb_mmu_read_byte(state->mmu,get_bc(cpu)); cycles=8; break; // LD A,(BC)
            case 0x0B: set_bc(cpu,get_bc(cpu)-1); cycles=8; break; // DEC BC
            case 0x0C: cpu->c++; UPDATE_FLAG(cpu,FLAG_Z,cpu->c==0); CLEAR_FLAG(cpu,FLAG_N); UPDATE_FLAG(cpu,FLAG_H,(cpu->c&0x0F)==0); cycles=4; break; // INC C
            case 0x0D: cpu->c--; UPDATE_FLAG(cpu,FLAG_Z,cpu->c==0); SET_FLAG(cpu,FLAG_N); UPDATE_FLAG(cpu,FLAG_H,(cpu->c&0x0F)==0x0F); cycles=4; break; // DEC C
            case 0x0E: cpu->c=gb_mmu_read_byte(state->mmu,cpu->pc++); cycles=8; break; // LD C,n
            case 0x0F:{ uint8_t c=cpu->a&1; cpu->a=(cpu->a>>1)|(c<<7); UPDATE_FLAG(cpu,FLAG_C,c); CLEAR_FLAG(cpu,FLAG_Z|FLAG_N|FLAG_H); cycles=4;}break; // RRCA
            case 0x10: cpu->halted=1; cpu->pc++; cycles=4; break; // STOP
            case 0x76: cpu->halted=1; cycles=4; break; // HALT
            case 0xF3: cpu->ime_enabled=0; cycles=4; break; // DI
            case 0xFB: cpu->ime_enabled=1; cycles=4; break; // EI
            default: cycles=4; break; // TODO: fill remaining opcodes
        }
    }

    gb_ppu_step(&state->ppu,cycles);
    gb_apu_step(&state->apu,cycles);
}

// CB-prefixed opcodes
static int gb_cpu_execute_cb(uint8_t cb_opcode, gb_cpu_t *cpu, core_state_t *state){
    switch(cb_opcode){
        case 0x00: cpu->b=(cpu->b<<1)|(cpu->b>>7); UPDATE_FLAG(cpu,FLAG_Z,cpu->b==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(cpu->b&0x80)!=0); return 8;
        case 0x01: cpu->c=(cpu->c<<1)|(cpu->c>>7); UPDATE_FLAG(cpu,FLAG_Z,cpu->c==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(cpu->c&0x80)!=0); return 8;
        case 0x02: cpu->d=(cpu->d<<1)|(cpu->d>>7); UPDATE_FLAG(cpu,FLAG_Z,cpu->d==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(cpu->d&0x80)!=0); return 8;
        case 0x03: cpu->e=(cpu->e<<1)|(cpu->e>>7); UPDATE_FLAG(cpu,FLAG_Z,cpu->e==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(cpu->e&0x80)!=0); return 8;
        case 0x04: cpu->h=(cpu->h<<1)|(cpu->h>>7); UPDATE_FLAG(cpu,FLAG_Z,cpu->h==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(cpu->h&0x80)!=0); return 8;
        case 0x05: cpu->l=(cpu->l<<1)|(cpu->l>>7); UPDATE_FLAG(cpu,FLAG_Z,cpu->l==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(cpu->l&0x80)!=0); return 8;
        case 0x06:{ uint16_t hl=get_hl(cpu); uint8_t val=gb_mmu_read_byte(state->mmu,hl); val=(val<<1)|(val>>7); gb_mmu_write_byte(state->mmu,hl,val); UPDATE_FLAG(cpu,FLAG_Z,val==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(val&0x80)!=0); return 16;}
        case 0x07: cpu->a=(cpu->a<<1)|(cpu->a>>7); UPDATE_FLAG(cpu,FLAG_Z,cpu->a==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(cpu->a&0x80)!=0); return 8;
        default: return 8; // TODO: implement all remaining CB opcodes (rotates, shifts, swaps, BIT/RES/SET)
    }
}
