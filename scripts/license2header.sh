#!/usr/bin/env sh
function generate(){
    input_file="$1"
    output_file="$2"
    var_name=${3^^}


    if [ ! -f "$input_file" ]; then
    echo "Error: File '$input_file' not found."
    exit 1
    fi

    # Remove any existing output file
    if [ -f "$output_file" ]; then
        rm "$output_file"
    fi


    header_guard="${var_name}_H_"

    cat <<EOF > "$output_file"
#ifndef $header_guard
#define $header_guard

EOF

    echo "static char const* $var_name = " >> "$output_file"
    while IFS= read -r line; do
    # Escape special characters
    escaped_line=$(echo "$line" | sed 's/\\/\\\\/g; s/"/\\"/g')
    echo "\"$escaped_line\\n\"" >> "$output_file"
    done < "$input_file"

    echo "\"\";" >> "$output_file"



    cat <<EOF >> "$output_file"

#endif // $header_guard
EOF

}

# remove directory
file=$(basename $1)
name="${file%.*}"

generate $1 $2 $name

headers="$headers licenses/$basename.h"
