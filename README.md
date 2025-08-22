# cub3D

A simple 3D game engine built with C, inspired by the legendary Wolfenstein 3D. This project implements raycasting to create a pseudo-3D perspective in a 2D world.

## 📖 About

cub3D is part of the 1337med/42 school curriculum, designed to introduce students to the basics of computer graphics, raycasting algorithms, and game development concepts. The project creates a dynamic view inside a maze where the player can navigate using basic controls.

## 🎮 Features

- **Raycasting Engine**: Implements raycasting algorithm to render 3D-like walls from a 2D map
- **Real-time Rendering**: Smooth real-time graphics using MiniLibX
- **Player Movement**: 
  - Move forward/backward with W/S keys
  - Strafe left/right with A/D keys
  - Rotate view with left/right arrow keys
- **Textured Walls**: Different textures for North, South, East, and West walls
- **Map Parsing**: Custom map format with validation
- **Floor and Ceiling Colors**: Configurable RGB colors

## 🛠️ Technical Implementation

### Core Components
- **Raycasting**: Mathematical calculations to determine wall distances and heights
- **DDA Algorithm**: Digital Differential Analyzer for ray-wall intersection
- **Texture Mapping**: Applying textures to walls based on ray hit position
- **Player Management**: Position, direction, and movement handling
- **Map Validation**: Ensuring map integrity and proper formatting

### Graphics Library
- **MiniLibX**: 42's graphics library for window management and pixel manipulation
- **Image Buffer**: Double buffering for smooth rendering
- **Color Management**: RGB color handling and manipulation

## 📋 Requirements

- **OS**: Linux or macOS
- **Compiler**: gcc with flags `-Wall -Wextra -Werror`
- **Graphics**: MiniLibX library

## 🚀 Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/rekoune/cub3D.git
   cd cub3D
   ```

2. **Compile the project**:
   ```bash
   make
   ```

3. **Run the game**:
   ```bash
   ./cub3D maps/map.cub
   ```

## 🗺️ Map Format

The game uses `.cub` files with the following format:

```
NO ./textures/north_wall.png
SO ./textures/south_wall.png
WE ./textures/west_wall.png
EA ./textures/east_wall.png

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Map Elements:
- `1`: Wall
- `0`: Empty space
- `N/S/E/W`: Player starting position and orientation
- `NO/SO/WE/EA`: Texture paths for walls
- `F`: Floor color (RGB)
- `C`: Ceiling color (RGB)
