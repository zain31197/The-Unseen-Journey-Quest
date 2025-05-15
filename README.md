# The Unseen Journey Quest

The Unseen Journey Quest is a grid-based dungeon exploration game developed in **C++**. The player navigates through a procedurally generated dungeon, collecting coins, avoiding deadly traps, and ultimately finding a key to unlock the exit. The game challenges players with limited moves and offers an undo feature to backtrack — all depending on the chosen difficulty level.

---

## 🎮 Features

- **Grid-Based Movement:** Navigate the dungeon using `w`, `a`, `s`, `d` keys.
- **Random Dungeon Generation:** Player (P), Key (K), Exit Door (D), Bombs (B), and Coins (C) are all placed randomly.
- **Undo Mechanic:** A limited undo option allows players to reverse previous moves.
- **Difficulty Modes:** Easy, Medium, and Hard with varying grid sizes, move limits, and undo allowances.
- **Scoring System:**
  - Coins: +2 points per coin
  - Unused Moves: +1 point per move remaining when exiting the dungeon

---

## 🧠 Code Architecture

### 🔹 `node` Class
- Represents each cell in the grid.
- Stores character (`P`, `K`, `D`, `B`, `C`, etc.)
- Contains pointers to adjacent nodes (`up`, `down`, `left`, `right`)

### 🔹 `stack` Class
- Custom implementation to store move history.
- Used for undo functionality.

### 🔹 `grid` Class
- Responsible for grid creation and random element placement.
- Handles calculation of path distances and hint generation.

### 🔹 `playermovement` Class
- Manages movement logic, coin collection, trap checks, and undo operation.

---

## 🧪 Gameplay

1. Select a difficulty level:
   - **Easy** (10x10 grid, 6 undos, extra moves)
   - **Medium** (15x15 grid, 4 undos)
   - **Hard** (20x20 grid, 1 undo, minimal moves)

2. Explore the dungeon:
   - Use `w`, `a`, `s`, `d` to move.
   - Find the **key (K)**.
   - Collect **coins (C)**.
   - Avoid **bombs (B)** — stepping on one ends the game.
   - Reach the **door (D)** to win.

3. Use `u` to undo your last move (limited by difficulty).
4. Use `q` to quit the game.

---

## 🧮 Scoring

| Action              | Points     |
|---------------------|------------|
| Coin Collected (C)  | +2         |
| Each Remaining Move | +1         |
| Hitting a Bomb (B)  | Game Over  |

---

## 🔧 Controls

| Key | Action         |
|-----|----------------|
| `w` | Move Up        |
| `a` | Move Left      |
| `s` | Move Down      |
| `d` | Move Right     |
| `u` | Undo Move      |
| `q` | Quit Game      |

---

## 🚀 Future Enhancements

- Diagonal movement support.
- Graphical UI using **Ncurses** or **SFML**.
- New elements: moving traps, multi-key doors.
- Multiplayer mode or AI opponent.
- Save/load game states.

---

## 🧑‍💻 Author

**Zain Shahid**

---

## 📜 License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).  
Feel free to fork, modify, and distribute!

---

## 🎉 Enjoy the game and may your journey be unseen but victorious!
