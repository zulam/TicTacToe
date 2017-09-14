/**
    Kent State University
    CS 33901 Software Engineering 
    Fall 2017
    Project #1
    Simple Tic Tac Toe
    tictactoe-v0.9.cpp
    Source: http://paste4btc.com/enVArEWu
    Author #1: NVitanovic, https://www.youtube.com/user/NVitanovic
    Author #2: 
*/


#include <iostream>
using namespace std;

class Board {
public:
    void draw();
    char* getMatrix();
    void setMatrix(int pos, char mark);
private:
    char matrix[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
};

class Player {
public:
    Player(): marker('X'), wins(0), losses(0), ties(0) {}
    char getMarker() {return marker;}
    void setMarker();
    int getWins() {return wins;}
    void setWins() {++wins;}
    int getLosses() {return losses;}
    void setLosses() {++losses;}
    int getTies() {return ties;}
    void setTies() {++ties;}

private:
    char marker;
    int wins;
    int losses;
    int ties;
    
};

class Game {
public:
    Game(): player1(), player2(), gameBoard(), turnNum(1), whoseTurn(1) {}
    Player getPlayer1();
    Player getPlayer2();
    int getWhoseTurn() {return whoseTurn;}
    Board getBoard() {return gameBoard;}
    int getTurnNum();
    char win();
    void setP1Wins() {player1.setWins(); player2.setLosses();}
    void setP2Wins() {player2.setWins(); player1.setLosses();}
    void setTie() {player1.setTies(); player2.setTies();}
    void setBoard(int pos, char mark) {gameBoard.setMatrix(pos, mark);}
    void draw() {gameBoard.draw();}
    void takeTurn();
private:
    Player player1;
    Player player2;
    Board gameBoard;
    int turnNum;
    char whoseTurn;
};

void Board::setMatrix(int pos, char mark) {
    matrix[pos] = mark;
}

void Game::takeTurn() {
    //Input
    int input;
    cout << "Press the number of the field: ";
    cin >> input;
    int actualInput = input-1;
    setBoard(actualInput, getWhoseTurn());
    getBoard().draw();
    
    //TogglePlayer
    if (whoseTurn == 1) {
        whoseTurn = 2;
    }
    else {
        whoseTurn = 1;
    }
}

char Game::win() {
    //first player
    int turn = getTurnNum();
    if (turn == 9) {
        return 'T';
    }
    
    Board myBoard = getBoard();
    char* myMatrix = myBoard.getMatrix();
    
    if (myMatrix[0] == 'X' && myMatrix[1] == 'X' && myMatrix[2] == 'X')
        return 'X';
    if (myMatrix[3] == 'X' && myMatrix[4] == 'X' && myMatrix[5] == 'X')
        return 'X';
    if (myMatrix[6] == 'X' && myMatrix[7] == 'X' && myMatrix[8] == 'X')
        return 'X';

    if (myMatrix[0] == 'X' && myMatrix[3] == 'X' && myMatrix[6] == 'X')
        return 'X';
    if (myMatrix[1] == 'X' && myMatrix[4] == 'X' && myMatrix[7] == 'X')
        return 'X';
    if (myMatrix[2] == 'X' && myMatrix[5] == 'X' && myMatrix[8] == 'X')
        return 'X';
 
    if (myMatrix[0] == 'X' && myMatrix[4] == 'X' && myMatrix[8] == 'X')
        return 'X';
    if (myMatrix[2] == 'X' && myMatrix[4] == 'X' && myMatrix[6] == 'X')
        return 'X';
 
    //second player
    if (myMatrix[0] == 'O' && myMatrix[1] == 'O' && myMatrix[2] == 'O')
        return 'O';
    if (myMatrix[3] == 'O' && myMatrix[4] == 'O' && myMatrix[5] == 'O')
        return 'O';
    if (myMatrix[6] == 'O' && myMatrix[7] == 'O' && myMatrix[8] == 'O')
        return 'O';
    
    if (myMatrix[0] == 'O' && myMatrix[3] == 'O' && myMatrix[6] == 'O')
        return 'O';
    if (myMatrix[1] == 'O' && myMatrix[4] == 'O' && myMatrix[7] == 'O')
        return 'O';
    if (myMatrix[2] == 'O' && myMatrix[5] == 'O' && myMatrix[8] == 'O')
        return 'O';
    
    if (myMatrix[0] == 'O' && myMatrix[4] == 'O' && myMatrix[8] == 'O')
        return 'O';
    if (myMatrix[2] == 'O' && myMatrix[4] == 'O' && myMatrix[6] == 'O')
        return 'O';
 
    return '/';
}

void Board::draw() {
    cout << string( 100, '\n' );
    cout << "TicTacToe v0.9" << endl;
    for (int i = 0; i < 9; i++)
    {
        cout << matrix[i] << " ";
        if (i==2 || i==5) {
            cout << endl;
        }
    }
    cout << endl;
}

char* Board::getMatrix() {
    return matrix;
}

Player Game::getPlayer1() {
    return player1;
}

void Player::setMarker() {
    if (marker == 'X')
        marker = 'O';
    else
        marker = 'X';
}

Player Game::getPlayer2() {
    return player2;
}

int Game::getTurnNum() {
    return turnNum;
}

char player = 'X';

int main() {
    char winner;
    Game myGame;
    while (1)
    {
        myGame.draw();
        myGame.takeTurn();
        winner = myGame.win();
        if (winner == 'X'){
            cout << "X  wins!" << endl;
            myGame.setP1Wins();
        }
        else if (winner == 'O') {
            cout <<"O wins!" << endl;
            myGame.setP2Wins();
        }
        else if (winner == 'T') {
            cout << "Tie!" << endl;
            myGame.setTie();
        }
    }
}
