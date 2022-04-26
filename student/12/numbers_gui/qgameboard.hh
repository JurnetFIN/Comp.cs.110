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
