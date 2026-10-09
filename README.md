# warp example
This is a basic example project to show how to setup and use `warp`.

## How to use
- To clone this project, you MUST use `git clone --recurse-submodules`
- If you cloned without this flag, the `warp` submodule will be missing, you can add it with `git submodule update --init --recursive`
- Open a terminal in the root of this repository and launch `make`
  - I recommend `make -j` for faster compile time
- Launch the program with `./warp_example`
- Close the program with the *ESCAPE* key

> You should see a spinning wooden crate if everything worked correctly.  
>
> You should also be able to freely move the camera with *WASD*, *SPACE* to go up and *LSHIFT* to go down.

## warp submodule
If you want your project to automatically use a newer latest version of `warp`, do the following in your repo's root:
```sh
git submodule update --remote warp
git add warp
git commit -m "Update warp"
git push
```
Or just use **`./update_warp.sh`**, it's easier.