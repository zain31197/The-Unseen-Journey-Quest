# DSA_ASSIGNMENT_2
The Unseen Journey Quest
The Unseen Journey Quest is a grid-based game developed in C++ where the player navigates through a dungeon to find a hidden key and exit through a door. The dungeon contains coins, traps (bombs), and obstacles. The player must collect coins, avoid traps, and find the exit door after collecting the key. The game offers three levels of difficulty—Easy, Medium, and Hard.

Features
Grid-Based Movement: The player moves within the grid using the keys w, a, s, and d for up, left, down, and right movements respectively.
Randomly Generated Dungeon: The dungeon elements such as the player's starting position (P), key (K), exit door (D), bombs (B), and coins (C) are randomly placed.
Undo Feature: The player has a limited number of undo moves depending on the difficulty level, allowing them to reverse their last movement.
Scoring System: The player gains points for each coin collected and for the number of unused moves remaining when they exit the dungeon successfully.
Difficulty Levels:
Easy: Larger grid with more moves and undo opportunities.
Medium: Moderate grid with fewer moves and undo opportunities.
Hard: Smallest grid with minimal moves and undo opportunities.
Gameplay
The game begins with a randomly generated dungeon grid based on the selected difficulty level.
The objective is to find the key (K), collect coins (C), and exit through the door (D) while avoiding traps (B).
If the player steps on a bomb (B), the game ends immediately.
The player cannot move in the opposite direction of their last move without using an undo.
Controls
w: Move up
a: Move left
s: Move down
d: Move right
u: Undo the last move (limited uses based on difficulty level)
q: Quit the game
Code Structure
node Class: Represents each cell in the grid. It stores the element (P, K, D, etc.) and pointers to adjacent nodes (up, down, left, right).
stack Class: A custom stack implementation to store the player's movement history for the undo feature.
grid Class: Manages the creation and manipulation of the dungeon grid, including placing random elements, calculating distances, and generating hints.
playermovement Class: Handles the player’s movements, collects coins, uses undo, and checks game status.
Scoring System
Coins: Each coin collected adds 2 points and provides an additional undo move.
Remaining Moves: For every unused move at the end of the game, the player gains 1 point.
Final Score Calculation: The sum of points from collected coins and unused moves.
Game Levels
Easy:
Grid Size: 10x10
Initial Undo Moves: 6
Initial Move Limit: Game start distance + 6
Medium:
Grid Size: 15x15
Initial Undo Moves: 4
Initial Move Limit: Game start distance + 2
Hard:
Grid Size: 20x20
Initial Undo Moves: 1
Initial Move Limit: Game start distance
Future Enhancements
Add support for diagonal movements.
Implement a graphical interface using libraries like Ncurses or SFML for better visualization.
Add more elements such as traps that move or doors that require multiple keys.
License
This project is licensed under the MIT License. Feel free to modify and distribute as you wish.

Author
Zain Shahid

Enjoy the game!