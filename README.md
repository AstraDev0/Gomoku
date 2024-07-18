# Gomoku AI Bot

## Overview
This project implements a Gomoku AI bot capable of playing the game on a 20x20 board against other bots. Gomoku, also known as Five in a Row, is a game where two players take turns placing stones on a grid, aiming to be the first to achieve five stones in a row, either vertically, horizontally, or diagonally.

## Requirements
- Your bot must compile and run on both Windows and Linux.
- Use of standard libraries only; no external libraries like TensorFlow or scikit-learn.
- Your bot must comply with the communication protocol for interacting with other bots.
- Maximum of 5 seconds per move and 70 MB memory limit per bot.
- Automatic defeat on making a forbidden move.

## Implementation
- **Language:** Implemented in C++.
- **Compilation:** Managed via Makefile supporting `make`, `re`, `clean`, and `fclean` commands.
- **Source Files:** All relevant source files, excluding unnecessary files like binaries or temporary files, are included.

## Game Rules
- Players take turns placing stones on the board.
- The game ends when a player achieves five stones in a row (vertically, horizontally, or diagonally).

## Evaluation
- **Play to Win:** Bot must recognize and play winning moves when given pre-filled boards.
- **Challenge Local Bots:** Compete against bots of various levels to accumulate victories for tournament qualification.
- **Efficiency:** Bot performance is evaluated based on its ability to play effectively within the specified time and memory limits.

## Technical Details
- **Board Representation:** Utilize optimized data structures to manage the game board efficiently.
- **Algorithm Choice:** Implement an algorithm (e.g., Minimax, Monte Carlo, Machine Learning) for decision making based on performance requirements.
- **Compilation and Testing:** Ensure cross-platform compatibility through rigorous testing on both Windows and Linux environments.

## Usage
1. Clone the repository.
2. Compile the bot using the provided Makefile.
    ```bash
    make
    ```
3. Run the bot executable.
    ```bash
    ./pbrain-gomoku-ai
    ```
4. Ensure the bot can communicate and play effectively against other bots or predefined game scenarios.

## Author
- Matthis Brocheton
- Louis de Caumont

## License
This project is licensed under the [License Name] License - see the LICENSE file for details.

## Acknowledgments
- Mention any acknowledgments or resources used in developing the bot (e.g., references to algorithms, inspiration from other projects).
