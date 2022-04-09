#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QString>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Normally this member should be in private part of the
    // class, but due to the automated tests it must be more
    // accessible.
    QTimer* timer;

private slots:
    // Add your slots here

    void on_startButton_clicked();

    void on_resetButton_clicked();

    void showTime();

    void on_stopButton_clicked();

private:
    Ui::MainWindow *ui;
    // Add other necessary members here
    unsigned int seconds_;
    bool timer_exist_;
};

#endif // MAINWINDOW_HH
