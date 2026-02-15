# SIV - Simple Image Viewer

A lightweight image viewer built in C

## Supported Platforms -
* Windows 🪟

## Build

### For Windows(MSVC) - 
* Visual Studio 2026
* Git

1. Open _Visual Studio Developer Shell_

2. Clone _siv_ repo from github
```
git clone https://github.com/Mage-100/siv
cd ./siv
```
3. Clone _SDL_ into dependencies folder
```
mkdir ./dependencies
git clone https://github.com/libsdl-org/SDL ./dependencies/SDL
```

4. Build the project
```
mkdir ./build
cmake -S . -B ./build
cmake --build ./build
```

5. Run _siv_ :
`./build/siv.exe`

## Usage
`siv.exe <path_to_image_file>`
