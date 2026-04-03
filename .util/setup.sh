#!/bin/zsh

coder="saelcc03"
# C++ setup
template_file="$HOME/$coder/.util/template.cpp"
for letter in {a..g}; do
    cp "$template_file" "${letter}.cpp"
done

# Golang setup
cp $HOME"/$coder/.golang/template" $HOME"/$coder/.golang/main.go"

echo "All done sir $coder"
