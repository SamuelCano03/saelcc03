if [ -z "$1" ]; then
  echo "❌ Usage: save <contest_id or name>"
  return 1
fi

mkdir -p .cfontests/"$1"

mv *.cpp .cfontests/"$1"/ 2>/dev/null

setup

echo "Congrats! Now everyone knows you participated on $1"
