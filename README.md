# retro-snake-game
This game has been written entirely in pure C, and a concerted effort has been made to adhere to the principles of the object design pattern throughout the development process. While every attempt has been made to ensure the code's quality, it's acknowledged that there may be occasional oversights and minor imperfections. Therefore, any guidance or advice is greatly welcomed and appreciated.

Furthermore, it's important to note that this project harnesses the capabilities of RayLib, an open-source C library specifically tailored for video game development and real-time graphics programming. RayLib's versatility and robust feature set have been instrumental in bringing this game to life.

# Game demo
![](https://github.com/khaledmust/retro-snake-game/blob/main/output.gif)

# Getting Started
## Prerequisite
- [RayLib](https://www.raylib.com/): Install RayLib on your system to be able to build the game.
## Installation
### 1. Clone the repository:

``` sh
git clone https://github.com/khaledmust/retro-snake-game.git
```

### 2. Navigate to the project directory

``` sh
cd retro-snake-game
```

### 3. Compile and run the game

``` sh
make

./my_game
```

# Game Mechanics
## Snake Body
The snake's body is represented as a deque data structure, which allows us to efficiently execute push and pop operations on both ends of the data structure. Leveraging this inherent property of deques, we can effectively simulate the movement of our snake within the game.

## Snake Movement
The snake's movement is achieved through a process of pushing and popping nodes in the direction of motion, a control mechanism orchestrated by the `GameObject_Snake_Update()` function. In this process, we examine the content of the head node, which includes its coordinates. We then perform a vector addition operation by combining the head's current coordinates with the snake's present direction. Following this calculation, we remove the tail node and subsequently insert the new head node along with its updated coordinates into the snake's data structure.

Using the coordinates associated with each node, the `GameObject_Draw_Snake()` function is responsible for rendering the snake on the screen.

## Food Position
The food object is structured with several attributes, one of which is a set of vector coordinates that determine its position on the screen.

The actual coordinates for the food object are determined dynamically by the `Food_GenerateRandomPosition()` function, which generates a random value within the range of 0 to 25. These generated values represent the coordinates within the game's play area.

Once the coordinates are generated, the drawing function utilizes these values to render the food object on the screen.

To ensure a crucial functionality, we have implemented a check to verify if the randomly generated position coincides with any part of the snake's body. If such an overlap is detected, preventing the food object from appearing on the screen, the `Food_PositionInDeque()` function is called to generate a new random position until a suitable and unoccupied location is found.

## Game Over
The game reaches a conclusion when the snake's head makes contact with either the boundaries of the playing field or its own body. This check is facilitated by the `Game_CheckCollisionWithGrid()` function. When a collision is identified, this function initiates a call to the `Game_Reset()` function, which effectively reverts the snake's body to its original state, allowing for a fresh start.

# Game Architecture Overview
## 1. Main Loop
The game is built around a game loop that continually updates and renders the game's state.

## 2. Game Objects
The primary game components are represented as objects, following an object-oriented design pattern. These objects include:
- `Snake`: Represents the player-controlled snake.
- `Food`: Represents the food item that the snake must consume.
- `Game`: Manages the overall game state and logic.

## RayLib Integration
The game leverages the RayLib library for graphics rendering and input handling. RayLib provides functions for window creation, drawing shapes, and handling user input.
