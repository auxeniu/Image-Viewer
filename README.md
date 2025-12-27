# Image Viewer

This repository contains a minimal image viewer written in C that uses SDL2 for rendering. The program reads raw image data from standard input and displays it in a window, making it suitable for Unix-style pipelines and simple experimentation with image data streams.

## Features
- Implemented in C with SDL2
- Reads image data from standard input
- Designed to work with piped input
- Lightweight and minimal dependencies

## Requirements
- GCC (or compatible C compiler)
- SDL2 development libraries
- A Unix-like environment (Linux, macOS, or WSL)

## SDL2 Installation

### Debian / Ubuntu
```bash
sudo apt update  
sudo apt install libsdl2-dev
```

### Arch Linux
```bash
sudo pacman -S sdl2
```
### Fedora
```bash
sudo dnf install SDL2-devel
```
### macOS (Homebrew)
```bash
brew install sdl2
```
## Build
Compile the program using the following command:
```bash
gcc -Wall -Wextra -g -o iv iv.c `sdl2-config --cflags --libs`
```
## Usage
The program expects image data to be provided via standard input:
```bash
cat image-binary.txt | ./iv
```
Replace `image-binary.txt` with a file containing the binary image data you want to display.

## Notes
- The input format must match what the program expects (raw/binary image data; check the code for further documentation).
- Error handling and format support are intentionally minimal, as the project is meant to be simple and educational.

## License
This project is provided as-is. Refer to the repository for licensing details.
