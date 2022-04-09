#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "iostream"
#include "QTimer"
#include "QString"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    seconds_ = 0;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::showTime);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    if (timer->isActive() == false)
        timer->start(1000);
}


void MainWindow::on_resetButton_clicked()
{
    seconds_ = 0;
    ui->lcdNumberSec->display(QString::number(0));
    ui->lcdNumberMin->display(QString::number(0));
}

void MainWindow::on_stopButton_clicked()
{
    if (timer->isActive() == true)
        timer->stop();
}

void MainWindow::showTime()
{
    seconds_++;
    ui->lcdNumberSec->display(QString::number(seconds_ % 60));
    ui->lcdNumberMin->display(QString::number(seconds_ / 60));
}
