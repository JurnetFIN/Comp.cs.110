/*
#############################################################################
# COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures          #
# Project4: 2048                                                            #
# Student: Juliusz Kotelba // 150586775                                     #
# File: qgameboard.hh                                                       #
# Description: Luokka, jossa on tallennettu pelilauta ja sen laatat         #
#############################################################################
*/

#ifndef QGAMEBOARD_HH
#define QGAMEBOARD_HH

#include "gameboard.hh"

#include <QWidget>
#include <QGridLayout>

class QGameBoard: public GameBoard
{
public:
    QGameBoard(QWidget *parent);
    ~QGameBoard();

    // Printing gameboard
    void print();

    // Counting score
    unsigned int get_score();

private:
    QGridLayout *layout_;

};

#endif // QGAMEBOARD_HH
