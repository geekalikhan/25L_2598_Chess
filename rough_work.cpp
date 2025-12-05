//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <cmath>
//#include <vector>
//#include <string>
//
//using namespace sf;
//using namespace std;
//
//int getIndex(int row, int col, int boardSize)
//{
//    return row * boardSize + col;
//}
//
//bool isValidPosition(int row, int col, int boardSize)
//{
//    return row >= 0 && row < boardSize && col >= 0 && col < boardSize;
//}
//
//int getPieceColor(int piece)
//{
//    if (piece >= 1 && piece <= 6) return 1;
//    if (piece >= 7 && piece <= 12) return 2;
//    return 0;
//}
//
//bool isPathClear(int board[], int boardSize, int sx, int sy, int ex, int ey)
//{
//    int rowDir = 0;
//    if (ex > sx)
//    {
//        rowDir = 1;
//    }
//    else if (ex < sx)
//    {
//        rowDir = -1;
//    }
//    int colDir = 0;
//    if (ey > sy)
//    {
//        colDir = 1;
//    }
//    else if (ey < sy)
//    {
//        colDir = -1;
//    }
//    int r = sx + rowDir;
//    int c = sy + colDir;
//    while (r != ex || c != ey)
//    {
//        if (board[getIndex(r, c, boardSize)] != 0)
//        {
//            return 0;
//        }
//        r += rowDir;
//        c += colDir;
//    }
//    return 1;
//}
//
//bool isValidMove(int board[], int boardSize, int sx, int sy, int ex, int ey, int currentPlayer)
//{
//    if (board[getIndex(sx, sy, boardSize)] == 0)
//    {
//        return 0;
//    }
//
//    int piece = board[getIndex(sx, sy, boardSize)];
//    int pieceColor = getPieceColor(piece);
//
//    if (pieceColor != currentPlayer)
//    {
//        return 0;
//    }
//
//    int destPiece = board[getIndex(ex, ey, boardSize)];
//    if (destPiece != 0)
//    {
//        int destColor = getPieceColor(destPiece);
//        if (destColor == pieceColor)
//        {
//            return 0;
//        }
//    }
//
//    int pieceType = ((piece - 1) % 6) + 1;
//    int rowDiff = ex - sx;
//    int colDiff = ey - sy;
//
//    switch (pieceType)
//    {
//    case 6: // Pawn
//    {
//        int direction;
//        int startRow;
//        if (pieceColor == 1)
//        {
//            direction = -1;
//            startRow = 6;
//        }
//        else
//        {
//            direction = 1;
//            startRow = 1;
//        }
//        if (colDiff == 0 && rowDiff == direction && destPiece == 0)
//        {
//            return 1;
//        }
//        if (colDiff == 0 && rowDiff == 2 * direction && sx == startRow && destPiece == 0)
//        {
//            if (board[getIndex(sx + direction, sy, boardSize)] == 0)
//            {
//                return 1;
//            }
//        }
//        if (abs(colDiff) == 1 && rowDiff == direction && destPiece != 0)
//        {
//            return 1;
//        }
//        return 0;
//    }
//    case 3: // Rook
//    {
//        if (rowDiff != 0 && colDiff != 0)
//        {
//            return 0;
//        }
//        return isPathClear(board, boardSize, sx, sy, ex, ey);
//    }
//    case 5: // Knight
//    {
//        if ((abs(rowDiff) == 2 && abs(colDiff) == 1) || (abs(rowDiff) == 1 && abs(colDiff) == 2))
//        {
//            return 1;
//        }
//        return 0;
//    }
//    case 4: // Bishop
//    {
//        if (abs(rowDiff) != abs(colDiff))
//        {
//            return 0;
//        }
//        return isPathClear(board, boardSize, sx, sy, ex, ey);
//    }
//    case 2: // Queen
//    {
//        if (rowDiff != 0 && colDiff != 0 && abs(rowDiff) != abs(colDiff))
//        {
//            return 0;
//        }
//        return isPathClear(board, boardSize, sx, sy, ex, ey);
//    }
//    case 1: // King
//    {
//        if (abs(rowDiff) <= 1 && abs(colDiff) <= 1)
//        {
//            return 1;
//        }
//        return 0;
//    }
//    default:
//    {
//        return 0;
//    }
//    }
//}
//
//int getPossibleMoves(int board[], int boardSize, int row, int col, int currentPlayer, int movesRow[], int movesCol[])
//{
//    int moveCount = 0;
//
//    for (int r = 0; r < boardSize; r++)
//    {
//        for (int c = 0; c < boardSize; c++)
//        {
//            if (isValidMove(board, boardSize, row, col, r, c, currentPlayer))
//            {
//                movesRow[moveCount] = r;
//                movesCol[moveCount] = c;
//                moveCount++;
//            }
//        }
//    }
//
//    return moveCount;
//}
//
//bool isValidMoveInList(int movesRow[], int movesCol[], int moveCount, int toRow, int toCol)
//{
//    for (int i = 0; i < moveCount; ++i)
//    {
//        if (movesRow[i] == toRow && movesCol[i] == toCol)
//        {
//            return true;
//        }
//    }
//    return false;
//}
//
////checkmate
//
//bool isSquareAttacked(int board[], int boardSize, int row, int col, int opponentColor)
//{
//    for (int r = 0; r < boardSize; r++)
//    {
//        for (int c = 0; c < boardSize; c++)
//        {
//            int index = getIndex(r, c, boardSize);
//            int piece = board[index];
//
//            if (piece == 0) continue;
//            if (getPieceColor(piece) != opponentColor) continue;
//
//            int pieceType = ((piece - 1) % 6) + 1;
//
//            if (pieceType == 6)
//            {
//                int direction;
//                if (opponentColor == 1) {
//                    direction = -1;
//                }
//                else {
//                    direction = 1;
//                }
//
//                if (r + direction == row && (c + 1 == col || c - 1 == col))
//                {
//                    return true;
//                }
//            }
//            else
//            {
//                if (isValidMove(board, boardSize, r, c, row, col, opponentColor))
//                {
//                    return true;
//                }
//            }
//        }
//    }
//    return false;
//}
//
//bool isKingInCheck(int board[], int boardSize, int currentPlayer)
//{
//    int kingPiece;
//    if (currentPlayer == 1) {
//        kingPiece = 1;
//    }
//    else {
//        kingPiece = 7;
//    }
//
//    int kingRow = -1, kingCol = -1;
//
//    for (int r = 0; r < boardSize; r++)
//    {
//        for (int c = 0; c < boardSize; c++)
//        {
//            if (board[getIndex(r, c, boardSize)] == kingPiece)
//            {
//                kingRow = r;
//                kingCol = c;
//                break;
//            }
//        }
//        if (kingRow != -1) break;
//    }
//
//    if (kingRow == -1) return false;
//
//    int opponentColor;
//    if (currentPlayer == 1) {
//        opponentColor = 2;
//    }
//    else {
//        opponentColor = 1;
//    }
//
//    return isSquareAttacked(board, boardSize, kingRow, kingCol, opponentColor);
//}
//
//bool isCheckmate(int board[], int boardSize, int currentPlayer)
//{
//    if (!isKingInCheck(board, boardSize, currentPlayer))
//    {
//        return false;
//    }
//
//    for (int r = 0; r < boardSize; r++)
//    {
//        for (int c = 0; c < boardSize; c++)
//        {
//            int index = getIndex(r, c, boardSize);
//            int piece = board[index];
//
//            if (piece != 0 && getPieceColor(piece) == currentPlayer)
//            {
//                int movesR[64], movesC[64];
//                int count = getPossibleMoves(board, boardSize, r, c, currentPlayer, movesR, movesC);
//
//                for (int i = 0; i < count; i++)
//                {
//                    int targetR = movesR[i];
//                    int targetC = movesC[i];
//                    int targetIndex = getIndex(targetR, targetC, boardSize);
//
//                    int originalSource = board[index];
//                    int originalDest = board[targetIndex];
//
//                    board[targetIndex] = originalSource;
//                    board[index] = 0;
//
//                    bool stillInCheck = isKingInCheck(board, boardSize, currentPlayer);
//
//                    board[index] = originalSource;
//                    board[targetIndex] = originalDest;
//
//                    if (!stillInCheck)
//                    {
//                        return false;
//                    }
//                }
//            }
//        }
//    }
//
//    return true;
//}
//
////board drawing
//
//void drawBoard(RenderWindow& window, int boardSize, float squareSize, const Color& lightColor, const Color& darkColor, Font& font)
//{
//    RectangleShape square(Vector2f(squareSize, squareSize));
//    Text text;
//    text.setFont(font);
//    text.setCharacterSize(20);
//
//    for (int i = 0; i < boardSize; ++i)
//    {
//        for (int j = 0; j < boardSize; ++j)
//        {
//            if ((i + j) % 2 == 0)
//            {
//                square.setFillColor(lightColor);
//                text.setFillColor(darkColor);
//            }
//            else
//            {
//                square.setFillColor(darkColor);
//                text.setFillColor(lightColor);
//            }
//
//            square.setPosition(j * squareSize, i * squareSize);
//            window.draw(square);
//
//            if (j == boardSize - 1)
//            {
//                text.setString(to_string(8 - i));
//                text.setPosition(j * squareSize + squareSize - 20, i * squareSize + 5);
//                window.draw(text);
//            }
//
//            if (i == boardSize - 1)
//            {
//                string s = "";
//                s += (char)('a' + j);
//                text.setString(s);
//                text.setPosition(j * squareSize + 5, i * squareSize + squareSize - 25);
//                window.draw(text);
//            }
//        }
//    }
//}
//
//void drawHighlightedSquares(RenderWindow& window, const int positionsRow[], const int positionsCol[], int count, float squareSize)
//{
//    CircleShape highlight(squareSize / 6);
//    highlight.setFillColor(Color(100, 200, 100, 150));
//    highlight.setOrigin(squareSize / 6, squareSize / 6);
//
//    for (int i = 0; i < count; ++i)
//    {
//        highlight.setPosition(positionsCol[i] * squareSize + squareSize / 2, positionsRow[i] * squareSize + squareSize / 2);
//        window.draw(highlight);
//    }
//}
//
//void drawPieces(RenderWindow& window, const Texture textures[], int board[], int boardSize, float squareSize)
//{
//    for (int i = 0; i < boardSize; ++i)
//    {
//        for (int j = 0; j < boardSize; ++j)
//        {
//            int index = getIndex(i, j, boardSize);
//            int piece = board[index];
//            if (piece != 0)
//            {
//                Sprite pieceSprite;
//                pieceSprite.setTexture(textures[piece - 1]);
//                float scaleX = squareSize / textures[piece - 1].getSize().x;
//                float scaleY = squareSize / textures[piece - 1].getSize().y;
//                pieceSprite.setScale(scaleX, scaleY);
//                pieceSprite.setPosition(j * squareSize, i * squareSize);
//                window.draw(pieceSprite);
//            }
//        }
//    }
//}
//
//void drawDraggedPiece(RenderWindow& window, const Texture textures[], int draggedPiece, float squareSize)
//{
//    Vector2i mousePos = Mouse::getPosition(window);
//    Sprite draggedSprite;
//    draggedSprite.setTexture(textures[draggedPiece - 1]);
//    float scaleX = squareSize / textures[draggedPiece - 1].getSize().x;
//    float scaleY = squareSize / textures[draggedPiece - 1].getSize().y;
//    draggedSprite.setScale(scaleX, scaleY);
//    draggedSprite.setPosition(mousePos.x - squareSize / 2, mousePos.y - squareSize / 2);
//    draggedSprite.setColor(Color(255, 255, 255, 200));
//    window.draw(draggedSprite);
//}
//
//int main()
//{
//    
//    const int board_size = 8;
//    const float square_size = 80.f;
//    const int window_size = board_size * square_size;
//    const Color light_square_color(240, 217, 181);
//    const Color dark_square_color(181, 136, 99);
//
//    RenderWindow window(VideoMode(window_size, window_size), "SFML Chess Board");
//
//    Font font;
//    
//    
//        if (!font.loadFromFile("arial.ttf")) {
//            cout << "Error loading font! Coordinates will not appear." << endl;
//        }
//    
//
//    Texture textures[12];
//    string piece_names[12] = { "white-king", "white-queen", "white-rook", "white-bishop", "white-knight", "white-pawn", "black-king", "black-queen", "black-rook", "black-bishop", "black-knight", "black-pawn" };
//    string base_path = "chess pieces/";
//
//    for (int i = 0; i < 12; ++i)
//    {
//        if (!textures[i].loadFromFile(base_path + piece_names[i] + ".png"))
//        {
//            cout << "Failed to load: " << piece_names[i] << endl;
//        }
//    }
//
//    int board[64] =
//    {
//        9, 11, 10, 8, 7, 10, 11, 9,
//        12, 12, 12, 12, 12, 12, 12, 12,
//        0, 0, 0, 0, 0, 0, 0, 0,
//        0, 0, 0, 0, 0, 0, 0, 0,
//        0, 0, 0, 0, 0, 0, 0, 0,
//        0, 0, 0, 0, 0, 0, 0, 0,
//        6, 6, 6, 6, 6, 6, 6, 6,
//        3, 5, 4, 2, 1, 4, 5, 3
//    };
//
//    bool is_dragging = false;
//    int dragged_piece = 0;
//    int drag_start_row = -1, drag_start_col = -1;
//    int possible_moves_row[64];
//    int possible_moves_col[64];
//    int move_count = 0;
//    int current_player = 1;
//
//    while (window.isOpen())
//    {
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == Event::Closed) window.close();
//
//            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
//            {
//                Vector2i mouse_pos = Mouse::getPosition(window);
//                int col = mouse_pos.x / square_size;
//                int row = mouse_pos.y / square_size;
//                if (row >= 0 && row < board_size && col >= 0 && col < board_size)
//                {
//                    int index = getIndex(row, col, board_size);
//                    if (board[index] != 0 && getPieceColor(board[index]) == current_player)
//                    {
//                        is_dragging = true;
//                        dragged_piece = board[index];
//                        drag_start_row = row;
//                        drag_start_col = col;
//                        move_count = getPossibleMoves(board, board_size, row, col, current_player, possible_moves_row, possible_moves_col);
//                        board[index] = 0;
//                    }
//                }
//            }
//            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
//            {
//                if (is_dragging)
//                {
//                    Vector2i mouse_pos = Mouse::getPosition(window);
//                    int col = mouse_pos.x / square_size;
//                    int row = mouse_pos.y / square_size;
//
//                    int drop_row;
//                    if (row >= 0 && row < board_size) {
//                        drop_row = row;
//                    }
//                    else {
//                        drop_row = drag_start_row;
//                    }
//
//                    int drop_col;
//                    if (col >= 0 && col < board_size) {
//                        drop_col = col;
//                    }
//                    else {
//                        drop_col = drag_start_col;
//                    }
//
//                    if (isValidMoveInList(possible_moves_row, possible_moves_col, move_count, drop_row, drop_col))
//                    {
//                        int index = getIndex(drop_row, drop_col, board_size);
//                        board[index] = dragged_piece;
//
//                        int piece_type = ((dragged_piece - 1) % 6) + 1;
//                        if (piece_type == 6) // Pawn
//                        {
//                            if ((getPieceColor(dragged_piece) == 1 && drop_row == 0) ||
//                                (getPieceColor(dragged_piece) == 2 && drop_row == 7))
//                            {
//                                window.clear();
//                                drawBoard(window, board_size, square_size, light_square_color, dark_square_color, font);
//                                drawPieces(window, textures, board, board_size, square_size);
//                                window.display();
//
//                                cout << "\n--- Pawn Promotion ---\n\n";
//                                cout << "Q-Queen\nR-Rook\nB-Bishop\nK-Knight\n" << endl;
//                                cout << "--- Make Choice ---\n\n";
//                                char choice;
//                                cin >> choice;
//                                cout << "\n--- Pawn Promoted ---\n";
//
//                                int offset;
//                                if (getPieceColor(dragged_piece) == 1) {
//                                    offset = 0;
//                                }
//                                else {
//                                    offset = 6;
//                                }
//
//                                int new_piece_id = 2;
//                                if (choice == 'r' || choice == 'R') new_piece_id = 3;
//                                else if (choice == 'b' || choice == 'B') new_piece_id = 4;
//                                else if (choice == 'k' || choice == 'K') new_piece_id = 5;
//
//                                board[index] = new_piece_id + offset;
//                            }
//                        }
//
//                        if (current_player == 1) {
//                            current_player = 2;
//                        }
//                        else {
//                            current_player = 1;
//                        }
//
//                        if (isCheckmate(board, board_size, current_player))
//                        {
//                            window.clear();
//                            drawBoard(window, board_size, square_size, light_square_color, dark_square_color, font);
//                            drawPieces(window, textures, board, board_size, square_size);
//                            window.display();
//
//                            cout << "CHECKMATE! ";
//                            if (current_player == 1)
//                            {
//                                cout << "Black";
//                            }
//                            else
//                            {
//                                cout << "White";
//                            }
//                            cout << " Won" << endl;
//
//                            window.close();
//                        }
//                    }
//                    else
//                    {
//                        int index = getIndex(drag_start_row, drag_start_col, board_size);
//                        board[index] = dragged_piece;
//                    }
//
//                    is_dragging = false;
//                    dragged_piece = 0;
//                    move_count = 0;
//                }
//            }
//        }
//
//        if (window.isOpen())
//        {
//            window.clear();
//            drawBoard(window, board_size, square_size, light_square_color, dark_square_color, font);
//
//            if (is_dragging)
//            {
//                drawHighlightedSquares(window, possible_moves_row, possible_moves_col, move_count, square_size);
//            }
//            drawPieces(window, textures, board, board_size, square_size);
//            if (is_dragging)
//            {
//                drawDraggedPiece(window, textures, dragged_piece, square_size);
//            }
//            window.display();
//        }
//    }
//    return 0;
//}