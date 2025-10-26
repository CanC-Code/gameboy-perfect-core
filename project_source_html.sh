#!/bin/bash
# project_source_html.sh
# Generates a static HTML mirror of a local Git repo for readable file contents.

# CONFIGURATION
REPO_DIR="."   # path to your local repo
OUTPUT_FILE="./index.html"          # output HTML file
TITLE="gameboy-perfect-core Mirror"

# Check if repo exists
if [ ! -d "$REPO_DIR" ]; then
    echo "Error: Repo directory $REPO_DIR does not exist."
    exit 1
fi

# Start HTML
cat <<EOT > "$OUTPUT_FILE"
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>$TITLE</title>
<style>
body { font-family: monospace; background: #f4f4f4; padding: 1rem; }
h2 { margin-top: 2rem; font-size: 1rem; }
pre { background: #2d2d2d; color: #f8f8f2; padding: 0.5rem; overflow-x: auto; white-space: pre-wrap; border-radius: 4px; margin-bottom: 2rem; }
</style>
</head>
<body>
<h1>$TITLE</h1>
EOT

# Loop through all files in the repo
cd "$REPO_DIR"
# Find all regular files (exclude .git)
find . -type f ! -path "*/.git/*" | sort | while read -r file; do
    # Escape HTML characters
    content=$(sed 's/&/\&amp;/g; s/</\&lt;/g; s/>/\&gt;/g;' "$file")
    echo "<h2>$file</h2>" >> "$OUTPUT_FILE"
    echo "<pre>$content</pre>" >> "$OUTPUT_FILE"
done

# End HTML
cat <<EOT >> "$OUTPUT_FILE"
</body>
</html>
EOT

echo "Static HTML mirror generated: $OUTPUT_FILE"
