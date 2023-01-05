
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Board
{
public:
    Board();
    void display();
    void update(int, char);
    bool isFull();
    bool isWinner(char);
private:
    char board[3][3]{};
};

class Player
{
public:
    explicit Player(char);
    [[nodiscard]] char getPiece() const;
    void makeMove(Board&) const;
private:
    char piece;
};

class Computer
{
public:
    explicit Computer(char);
    [[nodiscard]] char getPiece() const;
    void makeMove(Board&) const;
private:
    char piece;
};

class Game
{
public:
    Game(Computer computer, Player player);
    void play();
private:
    Board board;
    Player player;
    Computer computer;
};

int main()
{
    Game game(Computer(0), Player(0));
    game.play();
    return 0;
}

Board::Board()
{
    for (auto & i : board)
        for (char & j : i)
            j = ' ';
}

void Board::display()
{
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "-----------" << endl;
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "-----------" << endl;
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

void Board::update(int position, char piece)
{
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    board[row][col] = piece;
}

bool Board::isFull()
{
    for (auto & i : board)
        for (char j : i)
            if (j == ' ')
                return false;
    return true;
}

bool Board::isWinner(char piece)
{
    for (auto & i : board)
        if (i[0] == piece && i[1] == piece && i[2] == piece)
            return true;
    for (int j = 0; j < 3; j++)
        if (board[0][j] == piece && board[1][j] == piece && board[2][j] == piece)
            return true;
    if (board[0][0] == piece && board[1][1] == piece && board[2][2] == piece)
        return true;
    if (board[0][2] == piece && board[1][1] == piece && board[2][0] == piece)
        return true;
    return false;
}

Player::Player(char piece)
{
    this->piece = piece;
}

char Player::getPiece() const
{
    return piece;
}

void Player::makeMove(Board& board) const
{
    int position;
    cout << "Enter a position (1-9): ";
    cin >> position;
    board.update(position, piece);
}

Computer::Computer(char piece)
{
    this->piece = piece;
}

char Computer::getPiece() const
{
    return piece;
}

void Computer::makeMove(Board& board) const {
    int position;
    do {
        position = rand() % 9 + 1;
    } while (!board.isFull() && !board.isWinner(piece));
    board.update(position, piece);
}
Game::Game(Computer computer, Player player) : computer(computer), player(player) {
    srand(time(nullptr));
}

void Game::play()
{
    board.display();
    while (!board.isFull() && !board.isWinner(player.getPiece()) && !board.isWinner(computer.getPiece()))
    {
        player.makeMove(board);
        board.display();
        if (!board.isFull() && !board.isWinner(player.getPiece()) && !board.isWinner(computer.getPiece()))
        {
            computer.makeMove(board);
            board.display();
        }
    }
    if (board.isWinner(player.getPiece()))
        cout << "You win!" << endl;
    else if (board.isWinner(computer.getPiece()))
        cout << "Computer wins!" << endl;
    else
        cout << "Tie!" << endl;
}
