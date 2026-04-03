#!/bin/zsh

SCRIPT_PATH=$(readlink -f "$0")
REPO_ROOT=$(dirname $(dirname "$SCRIPT_PATH"))

coder=$(basename "$REPO_ROOT")

# C++ setup
template_file="$REPO_ROOT/.util/template.cpp"
for letter in {a..g}; do
    cp "$template_file" "${letter}.cpp"
done

# Golang setup
cp "$REPO_ROOT/.golang/template" "$REPO_ROOT/.golang/main.go"

echo "All done sir $coder"
