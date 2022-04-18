#include "QtWidgets"

#include "mainwindow.hh"
#include "qgameboard.hh"

const Coords LEFT = {0, -1};
const Coords UP = {-1, 0};
const Coords RIGHT = {0, 1};
const Coords DOWN = {1, 0};

MainWindow::MainWindow()
    : board(new QGameBoard)
{
    layout_ = new QVBoxLayout;
    wonText = new QLabel;

    isPaused_ = true;
    isStarted_ = false;

    createMenu();
    readInputs();
    createMoveButtons();
    createButtons();

    board->init_empty();

    wonText->setAlignment(Qt::AlignCenter);
    layout_->insertWidget(1,wonText);

    layout_->insertWidget(1, board->window_);
    layout_->setMenuBar(menuBar);

    setLayout(layout_);
}

MainWindow::~MainWindow() {
    delete board;

    delete start_;
    delete exitAction;
    delete fileMenu;
    delete menuBar;

    delete goalInput_;
    delete seedInput_;
    delete sizeInput_;

    delete layout_;
}

void MainWindow::createMenu()
{
    menuBar = new QMenuBar;
    fileMenu = new QMenu(tr("&Game"));
    exitAction = fileMenu->addAction(tr("E&xit"), &QCoreApplication::quit);
    menuBar->addMenu(fileMenu);
}

void MainWindow::readInputs() {
    QWidget *window = new QWidget;
    QGridLayout *inputs = new QGridLayout(window);

    QLabel *seedLabel = new QLabel("Enter seed: ");
    seedInput_ = new QSpinBox();

    QLabel *goalLabel = new QLabel("Enter goal: ");
    goalInput_ = new QSpinBox();
    goalInput_->setMaximum(65536);
    goalInput_->setValue(2048);

    //QLabel *sizeLabel = new QLabel("Enter size: ");
    //sizeInput_ = new QSpinBox();
    //sizeInput_->setMinimum(4);

    inputs->addWidget(seedLabel, 0, 0);
    inputs->addWidget(seedInput_, 0, 1);

    inputs->addWidget(goalLabel, 1, 0);
    inputs->addWidget(goalInput_, 1, 1);

    //inputs->addWidget(sizeLabel, 2, 0);
    //inputs->addWidget(sizeInput_, 2, 1);

    layout_->addWidget(window);
}

void MainWindow::createMoveButtons()
{
    QWidget *window = new QWidget;
    QGridLayout *buttons = new QGridLayout(window);

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

    layout_->addWidget(window);
}

void MainWindow::move(Coords dir, int goal) {
    if(board->move(dir, goal)) {
        onStartClicked();
        QString text = QString("You reached the goal value of %1, you won!").arg(goal_);
        wonText->setText(text);
        wonText->setStyleSheet("QLabel { background: rgb(255,215,0); font: bold; border-radius: 10px; font: 30pt; }");
        board->print();
        return;
    }
    else if(board->is_full()) {
        onStartClicked();
        start_->setDisabled(true);
        wonText->setText("Can't add new tile, you lost!");
        wonText->setStyleSheet("QLabel { background: rgb(219,0,0); font: bold; border-radius: 10px; font: 30pt; }");
        return;
    }
    board->new_value(false);
    board->print();
}

void MainWindow::createButtons()
{
    QWidget *window = new QWidget;
    QHBoxLayout *buttons = new QHBoxLayout(window);

    start_ = new QPushButton("Start");
    reset_ = new QPushButton("Reset");
    QPushButton *exit = new QPushButton("Exit");

    connect(start_, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(reset_, &QPushButton::clicked, this, &MainWindow::onResetClicked);
    connect(exit, &QPushButton::clicked, this, &QCoreApplication::quit);

    buttons->addWidget(start_);
    buttons->addWidget(reset_);
    buttons->addWidget(exit);

    reset_->setDisabled(true);

    layout_->addWidget(window);
}

void MainWindow::onStartClicked() {
    if (isStarted_ == false) {
        isStarted_ = true;
        goal_ = (goalInput_->value());

        board->fill(seedInput_->value());
        board->print();

        reset_->setEnabled(true);
    }

    if (isPaused_ == false)
        start_->setText("Continue");
    else
        start_->setText("Pause");

    wonText->setStyleSheet("");
    wonText->setText("");

    isPaused_ = !isPaused_;

    upButton_->setDisabled(isPaused_);
    leftButton_->setDisabled(isPaused_);
    rightButton_->setDisabled(isPaused_);
    downButton_->setDisabled(isPaused_);
}

void MainWindow::onResetClicked() {
    start_->setEnabled(true);

    if (isPaused_ == true)
        onStartClicked();

    goal_ = (goalInput_->value());
    board->fill(seedInput_->value());
    board->print();
}
