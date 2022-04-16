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
QT_END_NAMESPACE

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QGameBoard& board, QWidget* parent = nullptr);

private:
    void createMenu();
    void createButtons();
    //void createGridGroupBox();
    //void createFormGroupBox();

    enum { NumGridRows = 3, NumButtons = 4 };

    QMenuBar *menuBar;
    QGroupBox *horizontalGroupBox;
    QGroupBox *gridGroupBox;
    QGroupBox *formGroupBox;
    QTextEdit *smallEditor;
    QTextEdit *bigEditor;
    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;

    QMenu *fileMenu;
    QAction *exitAction;

    QGraphicsView view_;
};


#endif // MAINWINDOW_HH
