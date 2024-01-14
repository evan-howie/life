# life

Efficient implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) using C++ SFML.

![Glider](images/glider.gif)

## Install dependencies
```bash
sudo apt install cmake
sudo apt install libsfml-dev
```

## Build
```bash
git clone git@github.com:evan-howie/life.git
cd life
mkdir build && cd build
cmake ..
make
```
## Usage
To run the game of life with a randomly initialized board from the build directory:
```bash
./life
```

To create a custom board and load it:
From the build directory, open the editor
```bash
./life_editor grid_width grid_height file_name
```
Create your desired map and close the editor.

Then, open the game with the map command line argument.
```bash
./life --map ../maps/filename
```
Note: if your map is a different size from your game board, you will have to change the GRID_WIDTH and GRID_HEIGHT macros defined in src/main.cpp to match.
