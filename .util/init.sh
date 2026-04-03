#!/bin/zsh

oldPath=$(pwd)
parentDir=$(dirname "$oldPath")
echo "What's your warrrior name? (cf handle)"
read coder
if [[ -z "$coder" ]]; then
  echo "Empty name. Funny eh? I'll delete your root directory..."
  exit 1
fi

newPath="$parentDir/$coder"

if [[ "$oldPath" != "$newPath" ]]; then
  mv "$oldPath" "$newPath"
  echo "Repo renamed B)"
fi

cd $newPath

chmod +x .util/setup.sh .util/gpc.sh

echo "\n# --- CP Aliases for $coder ---" >> ~/.zshrc
echo "alias setup='$newPath/.util/setup.sh'" >> ~/.zshrc
echo "alias gpc='$newPath/.util/gpc.sh'" >> ~/.zshrc
echo "alias cf='$newPath/.util/cf.sh'" >> ~/.zshrc
echo "------------------------------------------"
echo "Welcome to the family, warrior $coder"
echo "Aliases 'setup' and 'gpc' added to your .zshrc"
echo "------------------------------------------"
echo "Please, run: source ~/.zshrc"
