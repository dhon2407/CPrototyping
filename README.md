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
