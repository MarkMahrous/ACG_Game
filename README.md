# ACG_Game: Avoid, Collect, and Goal Game

## Introduction
ACG_Game, which stands for "Avoid, Collect, and Goal Game," is a 2D top-view game developed using OpenGL and glut.h in C++. This game challenges players to navigate a virtual world filled with obstacles, collectibles, and power-ups while striving to reach the final goal. The game's central concept can be summarized as follows:

### General Idea
In this assignment, you are tasked with implementing a 2D top-view game of your own design. The game's primary elements include the player, the final goal, obstacles that the player must avoid, and collectibles and power-ups that the player can collect.

### Game Components
- **The Player**: Positioned in the middle of the screen at the beginning of the game, the player can move freely within the game borders using keyboard controls. The player's orientation aligns with their direction of motion.

- **Obstacles**: Strategically placed around the scene, these obstacles pose a challenge to the player. Colliding with obstacles or the game boundary results in the player losing one of their five lives. A health bar at the top of the screen displays the player's remaining lives.

- **Collectables**: These items are randomly positioned in the scene for each game run. Collecting collectables increases the player's game score. The scene should contain at least five collectable objects.

- **Power-Ups**: The game features two types of power-ups, each with unique functionality. Power-ups appear randomly at various positions in the scene and remain fixed until acquired by the player. The effect of a power-up lasts for a few seconds before deactivating. Players can miss power-ups if they do not collide with them. Importantly, power-ups do not affect the player's health bar.

- **Game Environment**: The player starts at a fixed position in the center of the screen. Obstacles are distributed throughout the scene, while collectables and power-ups are placed randomly. The player's health, game score, and remaining game time are displayed on the screen.

### Game Objective
The game's primary objective is to reach the final goal while avoiding obstacles, collecting collectables, and using power-ups strategically. The game ends under the following conditions:
- The player loses all of their lives due to collisions with obstacles or the game boundary.
- The game timer runs out.

Upon game completion, an end game screen is displayed to replace the game scene, indicating whether the player has won or lost.

## Implementation
ACG_Game is developed using C++ in Visual Studio and relies on the OpenGL library and the glut.h header for graphics rendering. Players can control the game through keyboard input to move in four directions and interact with the game environment.

## How to Run the Game
Follow these steps to run ACG_Game:
1. Set up your development environment with Visual Studio.
2. Ensure you have the necessary OpenGL and glut.h libraries installed.
3. Open the Game by running OpenGL2DTemplate.sln with Visual Studio.
4. Compile and run the game code, and you can start playing.

Have fun playing ACG_Game, where you'll need to avoid obstacles, collect collectables, use power-ups wisely, and reach the final goal to win the game!
