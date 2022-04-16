#include <numbertile.hh>
#include <gameboard.hh>
#include <mainwindow.hh>
#include <qgameboard.hh>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGameBoard board;
    MainWindow w(board);

    int seed = 100;
    board.init_empty();
    board.fill(seed);
    //int goal = 2048;

    board.print();

    w.show();

    return a.exec();
}
