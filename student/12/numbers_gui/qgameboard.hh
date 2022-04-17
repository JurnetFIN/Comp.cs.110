#ifndef QGAMEBOARD_HH
#define QGAMEBOARD_HH

#include "gameboard.hh"

#include <QWidget>
#include <QGridLayout>

class QGameBoard: public GameBoard
{
public:
    QGameBoard();
    ~QGameBoard();

    void print();

    QWidget *window_;

private:

    QGridLayout *layout_;

};

#endif // QGAMEBOARD_HH
