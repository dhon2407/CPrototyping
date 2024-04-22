extract_divisions() {
    local file="$1"
    local division_pattern='[^/]*\/[^/]*'
    local in_comment=false
    local line_num=0

    while IFS= read -r line; do
        ((line_num++))
        if $in_comment; then
            if [[ "$line" == *"*/"* ]]; then
                in_comment=false
                line="${line#*/*/}"
            else
                continue
            fi
        fi

        if [[ "$line" == *"/*"* ]]; then
            if [[ "$line" == *"*/"* ]]; then
                line="${line%%*/\**}"
            else
                in_comment=true
                line="${line%%/*}"
            fi
        fi

        if ! [[ "$line" =~ \/\/ ]]; then  # Exclude single-line comments
            echo "$line" | grep -n -o -E "$division_pattern" | while IFS=: read -r match_line match_division; do
                echo "Line $line_num, Position $((match_division+1)): $match_division"
            done
        fi
    done < "$file"
}


import os
import re

def extract_divisions_from_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    division_pattern = re.compile(r'([^/]|^)\/([^/]|$)')

    divisions = []
    in_multiline_comment = False

    for line_num, line in enumerate(lines, start=1):
        if '/*' in line:
            in_multiline_comment = True
        if '*/' in line:
            in_multiline_comment = False
            continue
        if in_multiline_comment:
            continue
        match = division_pattern.search(line)
        if match:
            divisions.append((line_num, match.start(), line.strip()))

    return divisions

def extract_divisions_from_directory(folder_path):
    divisions = []
    for root, _, files in os.walk(folder_path):
        for file_name in files:
            if file_name.endswith('.c'):
                file_path = os.path.join(root, file_name)
                file_divisions = extract_divisions_from_file(file_path)
                divisions.extend(file_divisions)
    return divisions

folder_path = 'path/to/your/folder'
divisions = extract_divisions_from_directory(folder_path)
for line_num, char_pos, division in divisions:
    print(f"Line {line_num}, Character {char_pos + 1}: {division}")
