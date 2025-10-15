      |                                                    ^~~~~~~~~~~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:16:33: error: \u2018gb_cpu_t\u2019 {aka \u2018struct gb_cpu_s\u2019} has no member named \u2018freg\u2019
   16 | #define CLEAR_FLAG(cpu,f) ((cpu)->freg&=~(f))
      |                                 ^~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:17:57: note: in expansion of macro \u2018CLEAR_FLAG\u2019
   17 | #define UPDATE_FLAG(cpu,f,cond) ((cond)?SET_FLAG(cpu,f):CLEAR_FLAG(cpu,f))
      |                                                         ^~~~~~~~~~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:107:52: note: in expansion of macro \u2018UPDATE_FLAG\u2019
  107 |         case 0x05: cpu->l=(cpu->l<<1)|(cpu->l>>7); UPDATE_FLAG(cpu,FLAG_Z,cpu->l==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(cpu->l&0x80)!=0); return 8;
      |                                                    ^~~~~~~~~~~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:16:33: error: \u2018gb_cpu_t\u2019 {aka \u2018struct gb_cpu_s\u2019} has no member named \u2018freg\u2019
   16 | #define CLEAR_FLAG(cpu,f) ((cpu)->freg&=~(f))
      |                                 ^~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:107:87: note: in expansion of macro \u2018CLEAR_FLAG\u2019
  107 | (cpu->l<<1)|(cpu->l>>7); UPDATE_FLAG(cpu,FLAG_Z,cpu->l==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(cpu->l&0x80)!=0); return 8;
      |                                                             ^~~~~~~~~~

/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:15:31: error: \u2018gb_cpu_t\u2019 {aka \u2018struct gb_cpu_s\u2019} has no member named \u2018freg\u2019
   15 | #define SET_FLAG(cpu,f) ((cpu)->freg|=(f))
      |                               ^~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:17:41: note: in expansion of macro \u2018SET_FLAG\u2019
   17 | #define UPDATE_FLAG(cpu,f,cond) ((cond)?SET_FLAG(cpu,f):CLEAR_FLAG(cpu,f))
      |                                         ^~~~~~~~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:107:118: note: in expansion of macro \u2018UPDATE_FLAG\u2019
  107 | _FLAG(cpu,FLAG_Z,cpu->l==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(cpu->l&0x80)!=0); return 8;
      |                                                             ^~~~~~~~~~~

/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:16:33: error: \u2018gb_cpu_t\u2019 {aka \u2018struct gb_cpu_s\u2019} has no member named \u2018freg\u2019
   16 | #define CLEAR_FLAG(cpu,f) ((cpu)->freg&=~(f))
      |                                 ^~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:17:57: note: in expansion of macro \u2018CLEAR_FLAG\u2019
   17 | #define UPDATE_FLAG(cpu,f,cond) ((cond)?SET_FLAG(cpu,f):CLEAR_FLAG(cpu,f))
      |                                                         ^~~~~~~~~~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:107:118: note: in expansion of macro \u2018UPDATE_FLAG\u2019
  107 | _FLAG(cpu,FLAG_Z,cpu->l==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(cpu->l&0x80)!=0); return 8;
      |                                                             ^~~~~~~~~~~

/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:108:80: error: \u2018core_state_t\u2019 {aka \u2018struct core_state_s\u2019} has no member named \u2018mmu\u2019
  108 |  uint16_t hl=get_hl(cpu); uint8_t val=gb_mmu_read_byte(state->mmu,hl); val=(val<<1)|(val>>7); gb_mmu_write_byte(state->mmu,hl,val); UPDATE_FLAG(cpu,FLAG_Z,val==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(val&0x80)!=0); return 16;}
      |                                                             ^~

/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:108:137: error: \u2018core_state_t\u2019 {aka \u2018struct core_state_s\u2019} has no member named \u2018mmu\u2019
  108 | ate->mmu,hl); val=(val<<1)|(val>>7); gb_mmu_write_byte(state->mmu,hl,val); UPDATE_FLAG(cpu,FLAG_Z,val==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(val&0x80)!=0); return 16;}
      |                                                             ^~

/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:15:31: error: \u2018gb_cpu_t\u2019 {aka \u2018struct gb_cpu_s\u2019} has no member named \u2018freg\u2019
   15 | #define SET_FLAG(cpu,f) ((cpu)->freg|=(f))
      |                               ^~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:17:41: note: in expansion of macro \u2018SET_FLAG\u2019
   17 | #define UPDATE_FLAG(cpu,f,cond) ((cond)?SET_FLAG(cpu,f):CLEAR_FLAG(cpu,f))
      |                                         ^~~~~~~~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:108:152: note: in expansion of macro \u2018UPDATE_FLAG\u2019
  108 | al=(val<<1)|(val>>7); gb_mmu_write_byte(state->mmu,hl,val); UPDATE_FLAG(cpu,FLAG_Z,val==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(val&0x80)!=0); return 16;}
      |                                                             ^~~~~~~~~~~

/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:16:33: error: \u2018gb_cpu_t\u2019 {aka \u2018struct gb_cpu_s\u2019} has no member named \u2018freg\u2019
   16 | #define CLEAR_FLAG(cpu,f) ((cpu)->freg&=~(f))
      |                                 ^~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:17:57: note: in expansion of macro \u2018CLEAR_FLAG\u2019
   17 | #define UPDATE_FLAG(cpu,f,cond) ((cond)?SET_FLAG(cpu,f):CLEAR_FLAG(cpu,f))
      |                                                         ^~~~~~~~~~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:108:152: note: in expansion of macro \u2018UPDATE_FLAG\u2019
  108 | al=(val<<1)|(val>>7); gb_mmu_write_byte(state->mmu,hl,val); UPDATE_FLAG(cpu,FLAG_Z,val==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(val&0x80)!=0); return 16;}
      |                                                             ^~~~~~~~~~~

/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:16:33: error: \u2018gb_cpu_t\u2019 {aka \u2018struct gb_cpu_s\u2019} has no member named \u2018freg\u2019
   16 | #define CLEAR_FLAG(cpu,f) ((cpu)->freg&=~(f))
      |                                 ^~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:108:184: note: in expansion of macro \u2018CLEAR_FLAG\u2019
  108 | te_byte(state->mmu,hl,val); UPDATE_FLAG(cpu,FLAG_Z,val==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(val&0x80)!=0); return 16;}
      |                                                             ^~~~~~~~~~

/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:15:31: error: \u2018gb_cpu_t\u2019 {aka \u2018struct gb_cpu_s\u2019} has no member named \u2018freg\u2019
   15 | #define SET_FLAG(cpu,f) ((cpu)->freg|=(f))
      |                               ^~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:17:41: note: in expansion of macro \u2018SET_FLAG\u2019
   17 | #define UPDATE_FLAG(cpu,f,cond) ((cond)?SET_FLAG(cpu,f):CLEAR_FLAG(cpu,f))
      |                                         ^~~~~~~~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:108:215: note: in expansion of macro \u2018UPDATE_FLAG\u2019
  108 | ATE_FLAG(cpu,FLAG_Z,val==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(val&0x80)!=0); return 16;}
      |                                                             ^~~~~~~~~~~

/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:16:33: error: \u2018gb_cpu_t\u2019 {aka \u2018struct gb_cpu_s\u2019} has no member named \u2018freg\u2019
   16 | #define CLEAR_FLAG(cpu,f) ((cpu)->freg&=~(f))
      |                                 ^~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:17:57: note: in expansion of macro \u2018CLEAR_FLAG\u2019
   17 | #define UPDATE_FLAG(cpu,f,cond) ((cond)?SET_FLAG(cpu,f):CLEAR_FLAG(cpu,f))
      |                                                         ^~~~~~~~~~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:108:215: note: in expansion of macro \u2018UPDATE_FLAG\u2019
  108 | ATE_FLAG(cpu,FLAG_Z,val==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(val&0x80)!=0); return 16;}
      |                                                             ^~~~~~~~~~~

/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:15:31: error: \u2018gb_cpu_t\u2019 {aka \u2018struct gb_cpu_s\u2019} has no member named \u2018freg\u2019
   15 | #define SET_FLAG(cpu,f) ((cpu)->freg|=(f))
      |                               ^~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:17:41: note: in expansion of macro \u2018SET_FLAG\u2019
   17 | #define UPDATE_FLAG(cpu,f,cond) ((cond)?SET_FLAG(cpu,f):CLEAR_FLAG(cpu,f))
      |                                         ^~~~~~~~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:109:52: note: in expansion of macro \u2018UPDATE_FLAG\u2019
  109 |         case 0x07: cpu->a=(cpu->a<<1)|(cpu->a>>7); UPDATE_FLAG(cpu,FLAG_Z,cpu->a==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(cpu->a&0x80)!=0); return 8;
      |                                                    ^~~~~~~~~~~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:16:33: error: \u2018gb_cpu_t\u2019 {aka \u2018struct gb_cpu_s\u2019} has no member named \u2018freg\u2019
   16 | #define CLEAR_FLAG(cpu,f) ((cpu)->freg&=~(f))
      |                                 ^~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:17:57: note: in expansion of macro \u2018CLEAR_FLAG\u2019
   17 | #define UPDATE_FLAG(cpu,f,cond) ((cond)?SET_FLAG(cpu,f):CLEAR_FLAG(cpu,f))
      |                                                         ^~~~~~~~~~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:109:52: note: in expansion of macro \u2018UPDATE_FLAG\u2019
  109 |         case 0x07: cpu->a=(cpu->a<<1)|(cpu->a>>7); UPDATE_FLAG(cpu,FLAG_Z,cpu->a==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(cpu->a&0x80)!=0); return 8;
      |                                                    ^~~~~~~~~~~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:16:33: error: \u2018gb_cpu_t\u2019 {aka \u2018struct gb_cpu_s\u2019} has no member named \u2018freg\u2019
   16 | #define CLEAR_FLAG(cpu,f) ((cpu)->freg&=~(f))
      |                                 ^~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:109:87: note: in expansion of macro \u2018CLEAR_FLAG\u2019
  109 | (cpu->a<<1)|(cpu->a>>7); UPDATE_FLAG(cpu,FLAG_Z,cpu->a==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(cpu->a&0x80)!=0); return 8;
      |                                                             ^~~~~~~~~~

/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:15:31: error: \u2018gb_cpu_t\u2019 {aka \u2018struct gb_cpu_s\u2019} has no member named \u2018freg\u2019
   15 | #define SET_FLAG(cpu,f) ((cpu)->freg|=(f))
      |                               ^~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:17:41: note: in expansion of macro \u2018SET_FLAG\u2019
   17 | #define UPDATE_FLAG(cpu,f,cond) ((cond)?SET_FLAG(cpu,f):CLEAR_FLAG(cpu,f))
      |                                         ^~~~~~~~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:109:118: note: in expansion of macro \u2018UPDATE_FLAG\u2019
  109 | _FLAG(cpu,FLAG_Z,cpu->a==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(cpu->a&0x80)!=0); return 8;
      |                                                             ^~~~~~~~~~~

/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:16:33: error: \u2018gb_cpu_t\u2019 {aka \u2018struct gb_cpu_s\u2019} has no member named \u2018freg\u2019
   16 | #define CLEAR_FLAG(cpu,f) ((cpu)->freg&=~(f))
      |                                 ^~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:17:57: note: in expansion of macro \u2018CLEAR_FLAG\u2019
   17 | #define UPDATE_FLAG(cpu,f,cond) ((cond)?SET_FLAG(cpu,f):CLEAR_FLAG(cpu,f))
      |                                                         ^~~~~~~~~~
/home/ubuntu/Desktop/gameboy-perfect-core/src/common/cpu.c:109:118: note: in expansion of macro \u2018UPDATE_FLAG\u2019
  109 | _FLAG(cpu,FLAG_Z,cpu->a==0); CLEAR_FLAG(cpu,FLAG_N|FLAG_H); UPDATE_FLAG(cpu,FLAG_C,(cpu->a&0x80)!=0); return 8;
      |                                                             ^~~~~~~~~~~

make[2]: *** [CMakeFiles/gameboy_perfect_core_libretro.dir/build.make:118: CMakeFiles/gameboy_perfect_core_libretro.dir/src/common/cpu.c.o] Error 1
make[1]: *** [CMakeFiles/Makefile2:83: CMakeFiles/gameboy_perfect_core_libretro.dir/all] Error 2
make: *** [Makefile:91: all] Error 2
ubuntu@ubuntu:~/Desktop/gameboy-perfect-core$ 

