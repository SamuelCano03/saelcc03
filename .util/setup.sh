#!/bin/zsh

template_file="~/saelcc03/.util/template.cpp"

for letter in {a..g}; do
    cp "$template_file" "${letter}.cpp"
done

cp golang/template golang/main.go

echo "All done sir Sam"
