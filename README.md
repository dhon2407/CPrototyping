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


def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <folder_path>")
        sys.exit(1)

    folder_path = sys.argv[1]

    if not os.path.isdir(folder_path):
        print("Error: Folder not found!")
        sys.exit(1)

    divisions = extract_divisions_from_directory(folder_path)
    for line_num, char_pos, division in divisions:
        print(f"Line {line_num}, Character {char_pos + 1}: {division}")

if __name__ == "__main__":
    main()

########## ADB Device checking ##########
```
@echo off
@REM Test Batch Script

:loopWaitDisconnect

powershell Start-Sleep -m 500
adb devices | findstr /c:"emulator-5554" > nul
if %ERRORLEVEL% equ 0 (
    echo %DATE:~0,10%%TIME:~0,8% Device still running
    goto :loopWaitDisconnect
)

:loopWaitReconnect

powershell Start-Sleep -m 500
adb devices | findstr /c:"emulator-5554" > nul
if %ERRORLEVEL% equ 1 (
    echo %DATE:~0,10%%TIME:~0,8% Device not yet booted
    goto :loopWaitReconnect
)

echo %DATE:~0,10%%TIME:~0,8% Device rebooted!
```

python
```
import csv
import re
import sys

def parse_top_dump(input_file, output_csv):
    # Define a regex pattern to match lines that contain '%Cpu(s)' information
    cpu_line_pattern = re.compile(r'^CPU:\s+([\d.]+)%\s*usr\s+([\d.]+)%\s*sys\s+[\d.]+%\s*nic\s+([\d.]+)%\s*idle')

    with open(input_file, 'r') as infile, open(output_csv, 'w', newline='') as outfile:
        csv_writer = csv.writer(outfile)
        csv_writer.writerow(['usr', 'sys', 'idle'])

        # Loop through each line to find matches
        for line in infile:
            match = cpu_line_pattern.match(line)
            if match:
                usr = match.group(1)
                sys = match.group(2)
                idle = match.group(3)
                csv_writer.writerow([usr, sys, idle])
            else:
                # Print unmatched lines for debugging
                print(f"No match: {line.strip()}")

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <input_file>")
        sys.exit(1)

    input_file = sys.argv[1]
    output_csv = 'cpu_usage.csv'  # Output CSV file
    parse_top_dump(input_file, output_csv)
```

