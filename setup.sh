#!/bin/zsh

template_file="template.cpp"

for letter in {a..l}; do
    cp "$template_file" "${letter}.cpp"
done

echo "All done sir Sam"
