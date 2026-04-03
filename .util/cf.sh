if [ -z "$1" ]; then
  echo "Ig you need an argument. Use contest id or name of contest"
  return 1
fi

mkdir -p .cfontests/"$1"

mv *.cpp .cfontests/"$1"/ 2>/dev/null

$(dirname "$0")/setup.sh

echo "Congrats! Now everyone knows you participated on $1"
