#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QDialog>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

#include <qgameboard.hh>

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
class QSpinBox;
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:

    QGameBoard *board;

    QVBoxLayout *layout_;

    void createMenu();
    void readInputs();
    void createButtons();
    void createMoveButtons();

    void onStartClicked();
    void onResetClicked();

    void move(Coords dir, int goal);

    //void createGridGroupBox();
    //void createFormGroupBox();

    enum { NumGridRows = 3, NumButtons = 4 };

    QMenuBar *menuBar;

    QMenu *fileMenu;
    QAction *exitAction;

    QSpinBox *seedInput_;
    QSpinBox *goalInput_;
    QSpinBox *sizeInput_;

    QPushButton *start_;
    QPushButton *reset_;

    QPushButton *upButton_;
    QPushButton *leftButton_;
    QPushButton *rightButton_;
    QPushButton *downButton_;

    bool isPaused_ = false;
    bool isStarted_ = false;

    int goal_;
};


#endif // MAINWINDOW_HH
