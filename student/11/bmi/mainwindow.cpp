#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "QString"
#include "math.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_countButton_clicked()
{
    double height = ui->heightLineEdit->text().toInt();
    double weight = ui->weightLineEdit->text().toInt();

    if(height == 0 or weight == 0){
        ui->resultLabel->setText("Cannot count");
        ui->infoTextBrowser->setPlainText("");
        return;
    }

    double bmi = weight/(pow((height/100.0), 2.0));
    QString number = QString::number(bmi);
    ui->resultLabel->setText(number);

    if(bmi < 18.5)
        ui->infoTextBrowser->setPlainText("You are underweight.");
    else if(bmi > 25)
        ui->infoTextBrowser->setPlainText("You are overweight.");
    else
        ui->infoTextBrowser->setPlainText("Your weight is normal.");
}

