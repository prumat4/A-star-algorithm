# A-star-algorithm
## Overview
  The program is a simple pathfinding visualization tool that uses the SDL library to draw a grid and allow the user to interact with it. The main class is called "Run" and contains several member functions for handling different aspects of the program. The program allows the user to place obstacles on the grid, set the starting and ending points, and then automatically use A* algorithm to find the shortest path between the two points.

In addition to the pathfinding functionality, the program also includes a simple menu that allows the user to choose between running the pathfinding algorithm or displaying instructions on how to use the program. The user interacts with the menu using the mouse and keyboard, and the program responds accordingly by updating the display.

## Usage examle
![](https://github.com/prumat4/A-star-algorithm/blob/main/README-data/usage2.gif)

## Instruction
- press 'C' to set obstacle (you can hold the key and move cursor) 				
- press 'X' to set walkable (you can hold the key and move cursor)
- L(R)CTRL + LMB to set start					
- L(R)SHIFT + LMB  to set end
- ESC to leave A*/Instruction

## How to build
1. Install SDL2 library
2. Clone this repo
3. Run cmake . and then make A-star-algorithm
4. run ./A-star-algorithm 

## Here some more output
