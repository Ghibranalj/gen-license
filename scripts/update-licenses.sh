#!/bin/bash

# Define the JSON data as a here document
json_data=$(curl -s  https://api.github.com/licenses)

# Function to fetch the body content from a URL
fetch_body() {
    local url="$1"
    local body
    body=$(curl -s $url | jq -r '.body' |  sed 's/"/\\"/g')

    body=$(echo "$body" | while IFS= read -r line; do
            echo "\"$line\\n\""
    done)
    echo "$body"
}

# Generate C code for the struct array
cat <<EOF
#ifndef LICENSES_H_
#define LICENSES_H_

// Define a struct type
typedef struct License {
    char key[20];
    char name[100];
    char *body ; // Change the size to fit your needs
} License;

static struct License licenses[] = {
EOF

length=0
# Parse the JSON data and generate C struct array initialization
echo "$json_data" | jq -c '.[]' | while IFS= read -r line; do
    key=$(echo "$line" | jq -r '.key')
    name=$(echo "$line" | jq -r '.name' | sed 's/"/\\"/g')
    echo "Fetching $key" >&2

    url=$(echo "$line" | jq -r '.url')
    body=$(fetch_body "$url")
    length=$(expr $length + 1)
    cat <<EOF
        {
            .key="$key",
            .name="$name",
            .body=""
$body
        },
EOF

done
cat <<EOF
};

#endif // LICENSES_H
EOF

