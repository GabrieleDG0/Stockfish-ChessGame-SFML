# Chess Game Engine using Stockfish and C++ SFML 

## Introduction 
This software is a modern chess application that combines the thrill of chess with the power of artificial intelligence. Utilising the Simple and Fast Multimedia Library (SFML) for graphics and the renowned Stockfish chess engine for intelligent gameplay, this application allows users to engage in challenging chess games against a computer opponent or another human player.
Users can create an initial configuration of chess pieces and watch the game unfold by making strategic decisions based on their understanding of chess.

## Chess Rules
Chess is played on an 8x8 grid known as a chessboard. Each player starts with 16 pieces: a king, a queen, two rooks, two knights, two bishops and six pawns. The aim of the game is to checkmate the opponent's king. This happens when the king is attacked and can no longer escape. The game follows the following basic rules:
- Movement of pieces: each type of piece has its own movement rules:
  - Pawns move one square forward (or two squares on their first move) and capture diagonally.
  - Towers move horizontally or vertically by any number of squares.
  - Knights move in an L-shape: two squares in one direction and then one square perpendicular to it.
  - Bishops move diagonally any number of squares.
  - Queens can move in any direction and any number of squares.
  - Kings move one square in any direction.
- Check and checkmate: A king is checkmated when it threatens to capture. If a player's king cannot be captured, it is checkmated and the game ends.

### Overview of the implementation
The program uses the SFML library for rendering and user interactions and integrates the Stockfish chess engine for AI capabilities.

### Setup and initialization
- Initial setup: The SFML library is initialized to handle graphics and events to ensure smooth rendering of the chessboard and pieces.
- Color and texture definitions: The application defines the colors for the chessboard and loads textures for the pieces from image files to improve visual appeal.
- Chessboard layout: The chessboard is created as an 8x8 grid, with each square designated for specific chess pieces at the start of the game.

### Drawing the board and pieces
- Rendering: Functions for drawing the chessboard and pieces are provided. The application renders the living pieces as sprites and updates their positions based on user interactions.
Game logic
- Move verification: The application checks whether each move is valid according to the rules of chess. It handles special moves such as castling and en passant moves.
- AI integration: The Stockfish engine analyzes the current game state and generates the best possible moves for the AI opponent. The application communicates with the engine via the Universal Chess Interface (UCI) protocol.

## Interaction with the user
To play the game, please follow these instructions:
- Mouse control: click and drag the pieces to move them to the desired square on the board.
- Keyboard control:
  - Spacebar: Pressing the spacebar allows the Stockfish AI to calculate its move in response to the player’s previous action.
  - Backspace key: This key undoes the last move and allows the player to correct mistakes.
  - Reset button: A reset function can be implemented to clear the board and start a new game.

### Main loop
The main loop of the application manages the frame rate, checks for user input, updates the game status and redraws the chessboard and pieces.

## Applications and extensions
While this system serves as a robust chess application, it has several potential applications and possibilities for future development:

### Applications
- Educational tool: This application can be used as a teaching tool to help new players learn the rules and strategies of chess in an interactive way.
- AI training: Advanced players can use Stockfish as a sparring partner to practice and improve their skills against one of the strongest chess engines.

### Future enhancements
- Some features, to complete the correct functionality of the game engine, still need to be finalised, such as a pawn promoting system.
- Online multiplayer mode: Implementation of an online functionality that allows users to play against other players over the Internet.
- Improved AI functions: Introduce different difficulty levels for the AI opponent to appeal to players with different skill levels.
- Gesture control: Integrate gesture recognition for moving tiles to improve the interactive experience.
- Augmented reality integration: Explore the potential for augmented reality features that allow players to visualize and interact with the chessboard in a virtual environment.

## Contributions
For more information and to try out, you can visit the project code repository on GitHub. If you find bugs or problems or have suggestions for improvement, feel free to open a post in the repository. Your feedback is valuable for the further development of this project. 
