#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecounter.hh"
#include "QString"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxN->setMinimum(0);
    ui->spinBoxN->setMaximum(760);

    ui->spinBoxG->setMinimum(0);
    ui->spinBoxG->setMaximum(120);

    ui->spinBoxP->setMinimum(0);
    ui->spinBoxP->setMaximum(250);

    ui->spinBoxE->setMinimum(0);
    ui->spinBoxE->setMaximum(5);

    connect(ui->spinBoxN, &QSpinBox::valueChanged, this, &MainWindow::on_countPushButton_clicked);
    connect(ui->spinBoxG, &QSpinBox::valueChanged, this, &MainWindow::on_countPushButton_clicked);
    connect(ui->spinBoxP, &QSpinBox::valueChanged, this, &MainWindow::on_countPushButton_clicked);
    connect(ui->spinBoxE, &QSpinBox::valueChanged, this, &MainWindow::on_countPushButton_clicked);

    on_countPushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_countPushButton_clicked()
{
    int grade = count_final_grade(ui->spinBoxN->value(),
                                  ui->spinBoxG->value(),
                                  ui->spinBoxP->value(),
                                  ui->spinBoxE->value());

    QString g = QString::number(grade);
    QString text = "Total grade: ";
    text.push_back(g);
    ui->textBrowser->setPlainText(text);
}

