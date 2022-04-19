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

    void print();

private:
    QWidget *widget_;
    QGridLayout *layout_;

};

#endif // QGAMEBOARD_HH
