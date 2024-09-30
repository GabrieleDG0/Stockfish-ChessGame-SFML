#include <SFML/Graphics.hpp>
#include <time.h>
#include "engine.hpp"

using namespace sf;

const int TILE_SIZE = 100;
const int NUM_PIECES = 32;
const int ANIMATION_STEPS = 50;
Vector2f boardOffset(0, 0);

Sprite piecesSprites[NUM_PIECES];
std::string currentPosition = "";

int chessBoard[8][8] = 
{
    -1, -2, -3, -4, -5, -3, -2, -1,
    -6, -6, -6, -6, -6, -6, -6, -6,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     6,  6,  6,  6,  6,  6,  6,  6,
     1,  2,  3,  4,  5,  3,  2,  1
};

// Convert board coordinates to chess notation (e.g., "e2", "e4")
std::string toChessNotation(Vector2f pos) {
    std::string notation = "";
    notation += char(pos.x / TILE_SIZE + 97);
    notation += char(7 - pos.y / TILE_SIZE + 49);
    return notation;
}

// Convert chess notation to board coordinates
Vector2f toBoardCoords(char file, char rank) {
    int x = int(file) - 97;
    int y = 7 - int(rank) + 49;
    return Vector2f(x * TILE_SIZE, y * TILE_SIZE);
}

// Move a piece based on a string (e.g., "e2e4")
void movePiece(std::string moveStr) {
    Vector2f oldPos = toBoardCoords(moveStr[0], moveStr[1]);
    Vector2f newPos = toBoardCoords(moveStr[2], moveStr[3]);

    // Capture opponent's piece if it is on the destination square
    for (int i = 0; i < NUM_PIECES; i++)
        if (piecesSprites[i].getPosition() == newPos)
            piecesSprites[i].setPosition(-100, -100); // Move captured piece off the board
        
    // Move the selected piece to the new position
    for (int i = 0; i < NUM_PIECES; i++)
        if (piecesSprites[i].getPosition() == oldPos)
            piecesSprites[i].setPosition(newPos);

    // Handle castling moves
    if (moveStr == "e1g1" && currentPosition.find("e1") == std::string::npos) movePiece("h1f1");
    if (moveStr == "e8g8" && currentPosition.find("e8") == std::string::npos) movePiece("h8f8");
    if (moveStr == "e1c1" && currentPosition.find("e1") == std::string::npos) movePiece("a1d1");
    if (moveStr == "e8c8" && currentPosition.find("e8") == std::string::npos) movePiece("a8d8");
}

// Load the initial position of the chess pieces
void loadInitialPosition() {
    int pieceIndex = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int piece = chessBoard[i][j];
            if (!piece) continue; // Skip empty squares

            int pieceType = abs(piece) - 1; // Determine piece type
            int pieceColor = piece > 0 ? 1 : 0; // Determine color: 0 for black, 1 for white

            piecesSprites[pieceIndex].setTextureRect(IntRect(TILE_SIZE * pieceType, TILE_SIZE * pieceColor, TILE_SIZE, TILE_SIZE));
            piecesSprites[pieceIndex].setPosition(TILE_SIZE * j, TILE_SIZE * i);
            pieceIndex++;
        }
    }

    // Apply all moves in the position string
    for (int i = 0; i < currentPosition.length(); i += 5)
        movePiece(currentPosition.substr(i, 4));
}

int main() {
    RenderWindow window(VideoMode(800, 800), "Chess");

    ConnectToEngine("Stockfish.exe");

    Texture pieceTexture, boardTexture;
    pieceTexture.loadFromFile("PNGs/ChessPieces.png");
    boardTexture.loadFromFile("PNGs/ChessBoard.png");

    for (int i = 0; i < NUM_PIECES; i++) piecesSprites[i].setTexture(pieceTexture);
    Sprite chessBoardSprite(boardTexture);

    loadInitialPosition();

    bool isPieceSelected = false;
    float dx = 0, dy = 0;
    Vector2f oldPosition, newPosition;
    std::string moveStr;
    int selectedPieceIndex = 0;

    while (window.isOpen()) {
        Vector2i mousePos = Mouse::getPosition(window) - Vector2i(boardOffset);

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            // Undo the last move if backspace is pressed
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::BackSpace) {
                if (currentPosition.length() > 6)
                    currentPosition.erase(currentPosition.length() - 6, 5);
                loadInitialPosition();
            }

            // Handle drag and drop of pieces
            if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) {
                for (int i = 0; i < NUM_PIECES; i++)
                    if (piecesSprites[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        isPieceSelected = true;
                        selectedPieceIndex = i;
                        dx = mousePos.x - piecesSprites[i].getPosition().x;
                        dy = mousePos.y - piecesSprites[i].getPosition().y;
                        oldPosition = piecesSprites[i].getPosition();
                    }
            }

            if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left) {
                isPieceSelected = false;
                Vector2f piecePos = piecesSprites[selectedPieceIndex].getPosition() + Vector2f(TILE_SIZE / 2, TILE_SIZE / 2);
                newPosition = Vector2f(TILE_SIZE * int(piecePos.x / TILE_SIZE), TILE_SIZE * int(piecePos.y / TILE_SIZE));
                moveStr = toChessNotation(oldPosition) + toChessNotation(newPosition);
                movePiece(moveStr);
                if (oldPosition != newPosition) currentPosition += moveStr + " ";
                piecesSprites[selectedPieceIndex].setPosition(newPosition);
            }
        }

        // Trigger Stockfish move when space is pressed
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            moveStr = getNextMove(currentPosition);
            oldPosition = toBoardCoords(moveStr[0], moveStr[1]);
            newPosition = toBoardCoords(moveStr[2], moveStr[3]);

            for (int i = 0; i < NUM_PIECES; i++) if (piecesSprites[i].getPosition() == oldPosition) selectedPieceIndex = i;

            // Animate the move
            for (int k = 0; k < ANIMATION_STEPS; k++) {
                Vector2f step = newPosition - oldPosition;
                piecesSprites[selectedPieceIndex].move(step.x / ANIMATION_STEPS, step.y / ANIMATION_STEPS); 

                window.clear();
                window.draw(chessBoardSprite);
                for (int i = 0; i < NUM_PIECES; i++) piecesSprites[i].move(boardOffset);
                for (int i = 0; i < NUM_PIECES; i++) window.draw(piecesSprites[i]); 
                window.draw(piecesSprites[selectedPieceIndex]);
                window.display();
            }

            movePiece(moveStr);
            currentPosition += moveStr + " ";
            piecesSprites[selectedPieceIndex].setPosition(newPosition);
        }

        if (isPieceSelected) piecesSprites[selectedPieceIndex].setPosition(mousePos.x - dx, mousePos.y - dy);

        // Draw the board and pieces
        window.clear();
        window.draw(chessBoardSprite);
        for (int i = 0; i < NUM_PIECES; i++) piecesSprites[i].move(boardOffset);
        for (int i = 0; i < NUM_PIECES; i++) window.draw(piecesSprites[i]);
        window.display();
    }

    CloseConnection();
    return 0;
}
