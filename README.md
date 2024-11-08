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

python cpu load
```
import csv
import re
import sys
import os

def parse_top_dump(input_file, csv_writer, folder_name):
    # Define a regex pattern to match 'CPU:' lines in your format
    cpu_line_pattern = re.compile(r'^CPU:\s+([\d.]+)%\s*usr\s+([\d.]+)%\s*sys\s+[\d.]+%\s*nic\s+([\d.]+)%\s*idle')

    with open(input_file, 'r') as infile:
        for line in infile:
            match = cpu_line_pattern.match(line)
            if match:
                usr = match.group(1)
                sys = match.group(2)
                idle = match.group(3)
                # Write data to the aggregated CSV with an additional column for folder name
                csv_writer.writerow([folder_name, usr, sys, idle])

def process_files_in_folder(base_folder, output_file):
    with open(output_file, 'w', newline='') as outfile:
        csv_writer = csv.writer(outfile)
        csv_writer.writerow(['folder_name', 'usr', 'sys', 'idle'])  # Header with folder name column

        for root, _, files in os.walk(base_folder):
            folder_name = os.path.basename(root)
            for file in files:
                if file.endswith('.txt'):  # Adjust the extension if needed
                    input_file = os.path.join(root, file)
                    print(f"Processing {input_file}")
                    parse_top_dump(input_file, csv_writer, folder_name)

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <base_folder>")
        sys.exit(1)

    base_folder = sys.argv[1]
    output_file = 'aggregated_cpu_usage.csv'  # Output CSV file for aggregated data
    process_files_in_folder(base_folder, output_file)
```

######## mem usage ########
```
import csv
import re
import sys
import os

def clean_line(line):
    # Remove terminal control characters (e.g., escape sequences)
    cleaned_line = re.sub(r'\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])', '', line)
    return cleaned_line

def parse_mem_dump(input_file, csv_writer, folder_name):
    # Define a regex pattern to match 'Mem:' lines
    mem_line_pattern = re.compile(r'^Mem:\s+([\d]+)K\s*used,\s+([\d]+)K\s*free')

    with open(input_file, 'r') as infile:
        for line in infile:
            # Clean up potential control characters
            line = clean_line(line)
            match = mem_line_pattern.match(line)
            if match:
                used = match.group(1)
                free = match.group(2)
                # Write data to the aggregated CSV with an additional column for folder name
                csv_writer.writerow([folder_name, used, free])

def process_files_in_folder(base_folder, output_file):
    with open(output_file, 'w', newline='') as outfile:
        csv_writer = csv.writer(outfile)
        csv_writer.writerow(['folder_name', 'used_mem', 'free_mem'])  # Header with folder name column

        for root, _, files in os.walk(base_folder):
            folder_name = os.path.basename(root)
            for file in files:
                if file.endswith('.txt'):  # Adjust the extension if needed
                    input_file = os.path.join(root, file)
                    print(f"Processing {input_file}")
                    parse_mem_dump(input_file, csv_writer, folder_name)

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <base_folder>")
        sys.exit(1)

    base_folder = sys.argv[1]
    output_file = 'aggregated_mem_usage.csv'  # Output CSV file for aggregated data
    process_files_in_folder(base_folder, output_file)
```
