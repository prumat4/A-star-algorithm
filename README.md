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
![Screenshot from 2023-03-20 21-49-31](https://user-images.githubusercontent.com/108902150/226463275-2de3d8de-3e01-4af9-a6da-7597ad1097f4.png)

![Screenshot from 2023-03-20 21-50-17](https://user-images.githubusercontent.com/108902150/226463421-09f5697f-1ad6-419d-afb7-61eb9ee05016.png)

![Screenshot from 2023-03-20 21-51-15](https://user-images.githubusercontent.com/108902150/226463427-df688fa3-a8d4-41a4-9b13-5e897105cb16.png)

![Screenshot from 2023-03-20 21-54-23](https://user-images.githubusercontent.com/108902150/226463429-d002bae8-51a0-4ffb-bb75-20399cded359.png)

![Screenshot from 2023-03-20 21-57-22](https://user-images.githubusercontent.com/108902150/226463431-c378b17a-3e0d-4327-a615-a52151def281.png)

![Screenshot from 2023-03-20 21-58-38](https://user-images.githubusercontent.com/108902150/226463435-8de826ad-ca1a-4df4-8670-c2ef32eafeb8.png)

![Screenshot from 2023-03-20 21-58-42](https://user-images.githubusercontent.com/108902150/226463436-5623c504-5bbb-47ba-87d3-ef332f790018.png)
