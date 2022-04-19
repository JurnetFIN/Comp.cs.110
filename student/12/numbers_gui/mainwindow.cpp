#include "QtWidgets"
#include "math.h"

#include "mainwindow.hh"
#include "qgameboard.hh"

const Coords LEFT = {0, -1};
const Coords UP = {-1, 0};
const Coords RIGHT = {0, 1};
const Coords DOWN = {1, 0};

MainWindow::MainWindow()
{    
    layout_ = new QVBoxLayout();

    isPaused_ = true;
    isStarted_ = false;

    createMenu();
    readInputs();

    infoText = new QLabel("");
    infoText->setAlignment(Qt::AlignCenter);
    infoText->setText("Enter seed value and goal value");
    layout_->addWidget(infoText);

    QWidget *w = new QWidget;

    board = new QGameBoard(w);
    board->init_empty();
    board->print();

    layout_->addWidget(w);

    createMoveButtons();
    createButtons();

    setLayout(layout_);
}

MainWindow::~MainWindow() {
    delete board;

    delete start_;
    delete reset_;

    delete fileMenu;
    delete menuBar;

    delete goalInput_;
    delete seedInput_;

    delete infoText;
    delete layout_;
}

void MainWindow::createMenu()
{
    menuBar = new QMenuBar;
    fileMenu = new QMenu(tr("&Game"));
    fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    menuBar->addMenu(fileMenu);
    layout_->setMenuBar(menuBar);
}

void MainWindow::readInputs() {
    QGridLayout *inputs = new QGridLayout();

    QLabel *seedLabel = new QLabel("Seed: ");
    seedInput_ = new QSpinBox();
    seedInput_->setRange(0, INT_MAX);

    QLabel *goalLabel = new QLabel("Goal: ");
    goalInput_ = new QSpinBox();
    goalInput_->setRange(4, 65536);
    goalInput_->setValue(2048);

    //QLabel *sizeLabel = new QLabel("Size: ");
    //sizeInput_ = new QSpinBox();
    //sizeInput_->setMinimum(4);

    inputs->addWidget(seedLabel, 0, 0);
    inputs->addWidget(seedInput_, 0, 1);

    inputs->addWidget(goalLabel, 1, 0);
    inputs->addWidget(goalInput_, 1, 1);

    //inputs->addWidget(sizeLabel, 2, 0);
    //inputs->addWidget(sizeInput_, 2, 1);

    layout_->addLayout(inputs);
}

void MainWindow::createMoveButtons()
{
    QGridLayout *buttons = new QGridLayout();

    upButton_ = new QPushButton(tr("↑"));
    upButton_->setFixedSize(QSize(32,32));
    connect(upButton_, &QPushButton::clicked, this, [this]{move(UP, goal_);});
    buttons->addWidget(upButton_, 1, 2);

    leftButton_ = new QPushButton(tr("←"));
    buttons->addWidget(leftButton_, 2, 1);
    connect(leftButton_, &QPushButton::clicked, this, [this]{move(LEFT, goal_);});
    leftButton_->setFixedSize(QSize(32,32));

    rightButton_ = new QPushButton(tr("→"));
    rightButton_->setFixedSize(QSize(32,32));
    connect(rightButton_, &QPushButton::clicked, this, [this]{move(RIGHT, goal_);});
    buttons->addWidget(rightButton_, 2, 3);

    downButton_ = new QPushButton(tr("↓"));
    downButton_->setFixedSize(QSize(32,32));
    connect(downButton_, &QPushButton::clicked, this, [this]{move(DOWN, goal_);});
    buttons->addWidget(downButton_, 3, 2);

    upButton_->setDisabled(true);
    leftButton_->setDisabled(true);
    rightButton_->setDisabled(true);
    downButton_->setDisabled(true);

    layout_->addLayout(buttons);
}

void MainWindow::move(Coords dir, int goal) {
    if(board->move(dir, goal)) {
        onStartClicked();

        QString text = QString("You reached the goal value of %1, you won!").arg(goal_);
        infoText->setText(text);
        this->setStyleSheet("background-color: rgb(255,215,0);");
        infoText->setStyleSheet("QLabel { background: rgb(255,215,0); "
                                "font: bold;"
                                "border-style: outset;"
                                "border-width: 2px;"
                                "border-radius: 15px; font: 30pt; }");
        board->print();
        return;
    }
    else if(board->is_full()) {
        onStartClicked();
        start_->setDisabled(true);

        infoText->setText("Can't add new tile, you lost!");
        this->setStyleSheet("background-color: rgb(215,0,0);");
        infoText->setStyleSheet("QLabel { background: rgb(219,0,0); "
                                "font: bold; "
                                "border-style: outset;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "font: 30pt; }");
        return;
    }
    board->new_value(false);
    board->print();
}

void MainWindow::createButtons()
{
    QHBoxLayout *buttons = new QHBoxLayout();

    start_ = new QPushButton("Start");
    reset_ = new QPushButton("Reset");
    QPushButton *exit = new QPushButton("Exit");

    connect(start_, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(reset_, &QPushButton::clicked, this, &MainWindow::onResetClicked);
    connect(exit,   &QPushButton::clicked, this, &QWidget::close);

    buttons->addWidget(start_);
    buttons->addWidget(reset_);
    buttons->addWidget(exit);

    reset_->setDisabled(true);

    layout_->addLayout(buttons);
}

void MainWindow::onStartClicked() {
    goal_ = (goalInput_->value());
    if(ceil(log2(goal_)) != floor(log2(goal_))) {
        infoText->setText("Goal isn't power of two, please change value");
        return;
    }

    if (isStarted_ == false) {
        isStarted_ = true;
        isPaused_ = false;

        enableButtons();

        start_->setText("Pause");

        board->fill(seedInput_->value());
        board->print();

    } else {
        isPaused_ = !isPaused_;

        enableButtons();

        if (isPaused_ == true) {
            start_->setText("Continue");
            infoText->setText("Game paused");
        } else {
            start_->setText("Pause");
        }
    }
    reset_->setEnabled(isStarted_); //&& !isPaused_);
}

void MainWindow::onResetClicked() {
    isStarted_ = false;
    isPaused_  = false;

    enableButtons();

    infoText->setText("Enter seed value and goal value");

    start_->setText("Start");
    start_->setEnabled(true);

    board->clear();
    board->print();
}

void MainWindow::enableButtons() {

    infoText->setText("");
    infoText->setStyleSheet("");
    this->setStyleSheet("");

    seedInput_->setDisabled(isStarted_);
    goalInput_->setDisabled(isStarted_);

    upButton_->setEnabled(isStarted_ && !isPaused_);
    leftButton_->setEnabled(isStarted_ && !isPaused_);
    rightButton_->setEnabled(isStarted_ && !isPaused_);
    downButton_->setEnabled(isStarted_ && !isPaused_);
}
