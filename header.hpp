//
//  header.hpp
//  TicTacToe
//
//  Created by Zack Ulam on 9/19/17.
//  Copyright � 2017 Zack Ulam. All rights reserved.
//

#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Board {
public:
    void draw();
    char* getMatrix() {return matrix;}
    bool setMatrix(int pos, char mark);
    void resetMatrix();
private:
    char matrix[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    bool spotsTaken[9] = {false, false, false, false, false, false, false, false, false};
};

class Player {
public:
    Player(): marker('X'), cash(0), wins(0), losses(0), ties(0) {}
    char getMarker() {return marker;}
    void setMarker() {if (marker == 'X') marker = 'O'; else marker = 'X';}
    int getWins() {return wins;}
    void setWins() {++wins; cash = wins * 100000;}
    int getCash () {return cash;}
    int getLosses() {return losses;}
    void setLosses() {++losses;}
    int getTies() {return ties;}
    void setTies() {++ties;}
    void clearCash() { cash = 0; wins = 0;}
    
private:
    char marker;
    int cash;
    int wins;
    int losses;
    int ties;
    
};

class Game {
public:
    Game(): singlePlayer(false), player1(), player2(), onARoll(), gameBoard(), validMove(true), playAgain(true), turnNum(1), whoseTurn('X') {}
    char getWhoseTurn() {return whoseTurn;}
    void setWhoseTurn(char arg) {whoseTurn = arg;}
    void setTurnNum() {++turnNum;}
    int getTurnNum() {return turnNum;}
    Board getBoard() {return gameBoard;}
    char win();
    void setP1Wins() {player1.setWins(); player2.setLosses();}
    void setP2Wins() {player2.setWins(); player1.setLosses();}
    void setTie() {player1.setTies(); player2.setTies();}
    bool setBoard(int pos, char mark) {return gameBoard.setMatrix(pos, mark);}
    void draw();
    bool takeTurn();
    void clearBoard() {turnNum = 1; gameBoard.resetMatrix();}
    bool getValidMove() {return validMove;}
    void onARollCheck(Player rollingPlayer) {onARoll = rollingPlayer;}
    char cashoutCheck(Player playerToCheck);
    void setCompPlaying() {singlePlayer = true;}
    bool getCompPlaying() {return singlePlayer;}
    void clearCash(Player thePlayer) {thePlayer.clearCash();}
    bool playAgain;
    Player player1;
    Player player2;
private:
    bool singlePlayer;
    Player onARoll;
    Board gameBoard;
    bool validMove;
    int turnNum;
    char whoseTurn;
};

void Board::resetMatrix() {
    //set no spots taken
    for (int i = 0; i < 9; ++i) {
        spotsTaken[i] = false;
    }
    //reset gameboard
    matrix[0] = '1';
    matrix[1] = '2';
    matrix[2] = '3';
    matrix[3] = '4';
    matrix[4] = '5';
    matrix[5] = '6';
    matrix[6] = '7';
    matrix[7] = '8';
    matrix[8] = '9';
}

bool Board::setMatrix(int pos, char mark) {
    //if user enters one, quit
    if (pos == -1) {
        return false;
    }
    //check for input of 1 through 9
    for (int i = 0; i < 9; ++i) {
        if (pos == i) {
            //if spot taken, not valid input
            if (spotsTaken[pos] == true) {
                return false;
            }
            else {
                //valid move
                matrix[pos] = mark;
                spotsTaken[pos] = true;
                return true;
            }
        }
        
    }
    //input is not 1-9
    return false;
}

void Board::draw() {
    //draw the board
    cout << string(2, '\n');
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

char Game::cashoutCheck(Player playerToCheck) {
    //computer player winning will reset the game
    if (playerToCheck.getMarker() == 'O' && getCompPlaying()==true){
        return 'e';
    }
    char answer = '/';
    int cash = playerToCheck.getCash();
    switch (cash) {
            //player options based on cash
        case 300000: cout << "Cashout at 300000? (Y/N): "; cin >> answer; break;
        case 600000: cout << "Cashout at 600000? (Y/N): "; cin >> answer; break;
        case 900000: cout << "Cashout at 900000? (Y/N): "; cin >> answer; break;
        case 1000000: cout << playerToCheck.getMarker() << " wins!"; answer = 'e'; break;
        default: cout << endl; break;
    };
    switch (answer) {
        case 'Y': cout << "You've won " << playerToCheck.getCash() << "!" << endl; answer = 'e'; break;
        case 'y': cout << "You've won " << playerToCheck.getCash() << "!" << endl; answer = 'e'; break;
        case 'N': cout << "Risky move...we'll see if it pays off..." << endl; break;
        case 'n': cout << "Risky move...we'll see if it pays off..." << endl; break;
        case '/': cout << endl; break;
        case 'e': cout << endl; break;
        default: cout << endl; break;
    };
    return answer;
}

void Game::draw() {
    cout << endl << "P1 cash: " << player1.getCash() << endl;
    cout << "P2 cash: " << player2.getCash() << endl;
    gameBoard.draw();
}

bool Game::takeTurn() {
    //Input
    int input ;
    //check for computer player
    if (getWhoseTurn() == 'O' && getCompPlaying() == true) {
        srand(time(NULL));
        input = (rand() % 9) + 1;
        int actualInput = --input;
        return setBoard(actualInput, getWhoseTurn());
    } else {
        //user's turn
        cout << getWhoseTurn() << ", Press the number of the field (0 to quit): ";
        cin >> input;
        while(cin.fail()){
            cout << "Not a valid input. Try again: " << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> input;
        }
        if (input == 0) {
            playAgain = false;
            return false;
        }
        int actualInput = --input;
        return setBoard(actualInput, getWhoseTurn());
    }
}

char Game::win() {
    //first player
    int turn = getTurnNum();
    
    Board myBoard = getBoard();
    char* myMatrix = myBoard.getMatrix();
    
    //check all win scenarios
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

#endif /* header_hpp */
