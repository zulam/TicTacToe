/**
 Kent State University
 CS 33901 Software Engineering
 Fall 2017
 Project #1
 Simple Tic Tac Toe
 tictactoe-v0.9.cpp
 Source: http://paste4btc.com/enVArEWu
 Author #1: NVitanovic, https://www.youtube.com/user/NVitanovic
 Author #2: Zack Ulam
 */

#include "header.h"

int main() {
    Game myGame;
    char winner;
    int numPlayers;
    cout << "1 or 2 players? (1/2): " << endl;
    cin >> numPlayers;
    if (numPlayers == 1) {
        myGame.setCompPlaying();
    }
    while (myGame.playAgain)
    {
        myGame.draw();
        
        if (myGame.takeTurn() == false) {
            cout << "Not a valid move. Try again: " << endl;
            continue;
        }
        
        else {
            winner = myGame.win();
            myGame.getBoard().draw();
            if (myGame.getWhoseTurn() == 'X') {
                myGame.setWhoseTurn('O');
            }
            else {
                myGame.setWhoseTurn('X');
            }
        }
        
        if (winner == 'X'){
            cout << "X  wins!" << endl;
            myGame.player2.clearCash();
            myGame.onARollCheck(myGame.player1);
            myGame.setP1Wins();
            if (myGame.cashoutCheck(myGame.player1) == 'e') {
                return 0;
            };
            myGame.clearBoard();
            continue;
        }
        else if (winner == 'O') {
            cout <<"O wins!" << endl;
            myGame.player1.clearCash();
            if (myGame.getCompPlaying() == false) {
                myGame.onARollCheck(myGame.player2);
                myGame.setP2Wins();
                if (myGame.cashoutCheck(myGame.player2) == 'e') {
                    return 0;
                };
            }
            myGame.clearBoard();
            continue;
        }
        else if (winner == 'T') {
            cout << "Tie!" << endl;
            myGame.player1.clearCash();
            myGame.player2.clearCash();
            myGame.setTie();
            myGame.clearBoard();
            continue;
        }
    }
    cout << "Game ended. Thanks for playing!" << endl;
}

