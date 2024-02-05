#!/bin/sh
# Writer
# This script writes content to a file
# Author: Andy Pabst
# Date: 1/30/24

# Check the number of arguments
if [ $# -ne 2 ]; then
    echo "Usage: $0 <file_path> <content>"
    exit 1
fi

path=$1
content=$2

# Ensure the directory exists or create it
if [ -d "$(dirname "$path")" ]; then
    touch "$path"
else
    mkdir -p "$(dirname "$path")" && touch "$path"
fi

# Check if the file is created successfully
if [ -f "$path" ]; then
    echo "$content" > "$path"
    echo "Content written to $path."
else
    echo "Error: File could not be created."
    exit 1
fi
