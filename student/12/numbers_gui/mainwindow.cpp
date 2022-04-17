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

    createMenu();
    readInputs();
    createMoveButtons();
    createButtons();

    board->init_empty();

    layout_->setMenuBar(menuBar);
    layout_->insertWidget(1, board->window_);

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

    delete layout_;
}

void MainWindow::createMenu()
{
    menuBar = new QMenuBar;
    fileMenu = new QMenu(tr("&File"));
    exitAction = fileMenu->addAction(tr("E&xit"));
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

    inputs->addWidget(seedLabel, 0, 0);
    inputs->addWidget(seedInput_, 0, 1);

    inputs->addWidget(goalLabel, 1, 0);
    inputs->addWidget(goalInput_, 1, 1);

    layout_->addWidget(window);
}

void MainWindow::createMoveButtons()
{
    QWidget *window = new QWidget;
    QGridLayout *buttons = new QGridLayout(window);

    QPushButton *upButton = new QPushButton(tr("↑"));
    upButton->setFixedSize(QSize(32,32));
    connect(upButton, &QPushButton::clicked, this, [this]{move(UP, goal_);});
    buttons->addWidget(upButton, 1, 2);

    QPushButton *leftButton = new QPushButton(tr("←"));
    buttons->addWidget(leftButton, 2, 1);
    connect(leftButton, &QPushButton::clicked, this, [this]{move(LEFT, goal_);});
    leftButton->setFixedSize(QSize(32,32));

    QPushButton *rightButton = new QPushButton(tr("→"));
    rightButton->setFixedSize(QSize(32,32));
    connect(rightButton, &QPushButton::clicked, this, [this]{move(RIGHT, goal_);});
    buttons->addWidget(rightButton, 2, 3);

    QPushButton *downButton = new QPushButton(tr("↓"));
    downButton->setFixedSize(QSize(32,32));
    connect(downButton, &QPushButton::clicked, this, [this]{move(DOWN, goal_);});
    buttons->addWidget(downButton, 3, 2);


    layout_->addWidget(window);
}

void MainWindow::move(Coords dir, int goal) {
    if(board->move(dir, goal)) {
        board->print();
        //std::cout << "You reached the goal value of " << goal << "!" << std::endl;
        //break;
    }
    else if(board->is_full()) {
        //std::cout << "Can't add new tile, you lost!" << std::endl;
        //break;
    }
    board->new_value(false);
    board->print();
}

void MainWindow::createButtons()
{
    QWidget *window = new QWidget;
    QHBoxLayout *buttons = new QHBoxLayout(window);

    start_ = new QPushButton("Start");
    QPushButton *reset = new QPushButton("Reset");
    QPushButton *exit = new QPushButton("Exit");

    connect(start_, &QPushButton::clicked, this, &MainWindow::onStartClicked);

    buttons->addWidget(start_);
    buttons->addWidget(reset);
    buttons->addWidget(exit);

    layout_->addWidget(window);
}

void MainWindow::onStartClicked() {
    start_->setText("Pause");
    goal_ = (goalInput_->value());
    board->fill(seedInput_->value());
    board->print();

}
