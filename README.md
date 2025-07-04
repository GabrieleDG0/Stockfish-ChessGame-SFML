# Chess Game Engine using Stockfish and C++ SFML 

## Introduction 
This software is a modern chess application that combines the thrill of chess with the power of artificial intelligence. Utilising the Simple and Fast Multimedia Library (SFML) for graphics and the renowned Stockfish chess engine for intelligent gameplay, this application allows users to engage in challenging chess games against a computer opponent or another human player. Users can create an initial configuration of chess pieces and watch the game unfold by making strategic decisions based on their understanding of chess.

## Download and Requirements
To run the application, visit the Releases section on GitHub to find and download the latest version of the package containing the Game.exe, the engine Stockfish.exe and the textures.

### Chess Rules
Chess is played on an 8x8 grid known as a chessboard. Each player starts with 16 pieces: a king, a queen, two rooks, two knights, two bishops, and six pawns. The aim of the game is to checkmate the opponent's king. This happens when the king is attacked and can no longer escape. The game follows the following basic rules:
- **Movement of pieces**: Each type of piece has its own movement rules:
  - Pawns move one square forward (or two squares on their first move) and capture diagonally.
  - Rooks move horizontally or vertically by any number of squares.
  - Knights move in an L-shape: two squares in one direction and then one square perpendicular to it.
  - Bishops move diagonally any number of squares.
  - Queens can move in any direction and any number of squares.
  - Kings move one square in any direction.
- **Check and checkmate**: A king is checkmated when it is threatened to be captured. If a player's king cannot escape capture, it is checkmated, and the game ends.

## Overview of the Implementation
The program uses the SFML library for rendering and user interactions and integrates the Stockfish chess engine for AI capabilities.

### Setup and Initialization
- **Initial setup**: The SFML library is initialized to handle graphics and events to ensure smooth rendering of the chessboard and pieces.
- **Color and texture definitions**: The application defines the colors for the chessboard and loads textures for the pieces from image files to improve visual appeal.
- **Chessboard layout**: The chessboard is created as an 8x8 grid, with each square designated for specific chess pieces at the start of the game.

![ChessBoard](https://github.com/user-attachments/assets/b5ba918a-e2c0-4784-85f0-c338ff040419)

### Drawing the Board and Pieces
- **Rendering**: Functions for drawing the chessboard and pieces are provided. The application renders the living pieces as sprites and updates their positions based on user interactions.

### Game Logic
- **Move verification**: The application checks whether each move is valid according to the rules of chess. It handles special moves such as castling and en passant moves.
- **AI integration**: The Stockfish engine analyzes the current game state and generates the best possible moves for the AI opponent. The application communicates with the engine via the Universal Chess Interface (UCI) protocol.

![ChessPieces](https://github.com/user-attachments/assets/edad4594-ed83-4a31-a5bc-e275019c84ec)

### Code Structure
The project is divided into three main components:

#### 1. Main
The ***main*** module serves as the entry point for the application. It manages the primary game loop, user input and rendering. This component is responsible for initializing the SFML library, setting up the chessboard and managing the entire game flow. Here the application continuously checks the user interactions and updates the game state accordingly.

#### 2. Engine
The ***engine*** module manages the logic of the chess game. It checks the validity of moves, implements the rules of chess and processes special moves such as castling and en passant. This module acts as the brain of the game by ensuring that all interactions comply with the chess rules and updating the game state based on user actions.

#### 3. Stockfish
The ***stockfish*** module interfaces with the Stockfish chess engine. It communicates with Stockfish using the Universal Chess Interface (UCI) protocol, sending the current game state and receiving the AI's calculated moves. This component enables the integration of advanced artificial intelligence into the application, allowing users to play against a formidable opponent.

## Interaction with the User
To play the game, please follow these instructions:
- **Mouse control**: Click and drag the pieces to move them to the desired square on the board.
- **Keyboard control**:
  - **Spacebar**: Pressing the spacebar allows the Stockfish AI to calculate its move in response to the player’s previous action.
  - **Backspace key**: This key undoes the last move and allows the player to correct mistakes.
  - **Reset button**: A reset function can be implemented to clear the board and start a new game.

### Main Loop
The main loop of the application manages the frame rate, checks for user input, updates the game status, and redraws the chessboard and pieces.

## Applications and Extensions
While this system serves as a robust chess application, it has several potential applications and possibilities for future development:

### Future Enhancements
- Some features, such as a pawn promotion system, still need to be finalized to complete the correct functionality of the game engine.
- **Online multiplayer mode**: Implementation of an online functionality that allows users to play against other players over the Internet.
- **Improved AI functions**: Introduce different difficulty levels for the AI opponent to appeal to players with different skill levels.

## Contributions
For more information and to try out, you can visit the project code repository on GitHub. If you find bugs or problems or have suggestions for improvement, feel free to open a post in the repository. Your feedback is valuable for the further development of this project.
