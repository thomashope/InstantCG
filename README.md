# InstantCG
A port of [QuickCG](https://lodev.org/quickcg/) by Lode Vandevenne to SDL2

## Using InstantCG

Copy instantcg.h and instantcg.cpp into your project directory, make sure you are linking with SDL2, and compile.

To do this from the command line on mac or linux would look something like this:

```
clang++ *.cpp -lSDL2
```

There are a few ways you could install SDL2. On linux it should be availble from your package manager, on mac or windows you can grab the .framework or .lib/.dll files from the github [releases](https://github.com/libsdl-org/SDL/releases) page, altenatively on mac you can use homebrew `brew install sdl2`.

The example folder in this repo also bundles the SDL2 libs which you could also use to get started, although they are probably not up to date.

## Building The Examples

Both SDL2 and [premake](https://premake.github.io/) have been bundled with the repo so you can quickly build the exmaples.

### Windows from Git Bash

```
cd examples
./premake vs2019
start build/vs2019/InstantCG.sln
```

In the solution explorer, right click the example you want to run and select 'Set as Startup Project', then press F5 to build and run.

### Mac from Terminal.app

```
cd examples
./premake xcode4
open build/xcode4/InstantCG.xcworkspace
```

Select the project by clicking the current project name in the top bar in Xcode, run by pressing the play button in the top left.