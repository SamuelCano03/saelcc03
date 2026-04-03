## 🚀 Quick Start Guide

Clone this branch if you wanna be a winner

1. **Starter kit:**
   ```bash
   git clone -b starter --single-branch https://github.com/SamuelCano03/saelcc03.git
   cd saelcc03
   ```

2. **Initialize your profile**:
   ```bash
   ./.util/init.sh
   ```

3. **Use and enjoy:**
- After initializing, please run `source ~/.zshrc`
- `gpc` is an alias for `g++ -DLOCAL "$1" -o .z.out && ./.z.out`
- Running `gpc a.cpp` allows you to compile and execute at the same time
- It also includes a pretty debugger in `.debug.cpp`, use it with any var with `dbg(my_var,other_var);`
- Run `setup` to clean the files with `template.cpp`
- If you did a cf contest, use `cf {contestid}`. It will save your progress in `.cfcontests/{contestid}` and clean your wksp

