# Pong Game

A classic Pong game written in C++ with [raylib 4.5.0](https://github.com/raysan5/raylib/releases/tag/4.5.0).
Control the right paddle and play against a computer-controlled opponent.

## Controls

- **Up Arrow**: move the player paddle up.
- **Down Arrow**: move the player paddle down.
- **Close the window**: quit the game.

## Project structure

```text
PongGame/
├── src/
│   ├── main.cpp       # Initializes raylib and runs the game loop
│   ├── Game.h/.cpp    # Game state, scores, collisions, and court drawing
│   ├── Ball.h/.cpp    # Ball movement, wall bounces, and resets
│   └── Paddle.h/.cpp  # Player and CPU paddle behaviour
├── CMakeLists.txt     # CMake build configuration
├── Makefile           # w64devkit/GNU Make build configuration
└── README.md
```

## Requirements

- Windows
- [raylib 4.5.0](https://github.com/raysan5/raylib/releases/tag/4.5.0)
- For the Makefile workflow: [w64devkit](https://github.com/skeeto/w64devkit/releases), including GNU Make and a C++ compiler
- For the CMake workflow: [CMake](https://cmake.org/download/)

The examples below assume w64devkit is installed at `C:/raylib/w64devkit` and raylib is located at `C:/raylib/raylib`.
Adjust these paths when your installation uses different locations.

## Build with Makefile

Run this from the project directory in PowerShell:

```powershell
C:/raylib/w64devkit/bin/make.exe RAYLIB_PATH=C:/raylib/raylib PROJECT_NAME=main
```

This produces `main.exe` in the project root.

## Build with CMake

Run this from the project directory in PowerShell:

```powershell
cmake -S . -B build -DRAYLIB_ROOT=C:/raylib/raylib
cmake --build build
```

`CMakeLists.txt` lists the project source files, chooses C++14, adds raylib, and creates the `PongGame` executable. The `RAYLIB_ROOT` option points CMake to a local raylib source directory.

If raylib has already been installed as a CMake package, omit `-DRAYLIB_ROOT=...`.

## Run

After the Makefile build:

```powershell
./main.exe
```

After the CMake build:

```powershell
./build/PongGame.exe
```

If Windows reports a missing compiler DLL, run the game in a w64devkit terminal or add `C:/raylib/w64devkit/bin` to your `PATH`.
