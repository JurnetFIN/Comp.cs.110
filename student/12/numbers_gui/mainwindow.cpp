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
    // Create mainlayout
    layout_ = new QVBoxLayout();

    // Set values for parametres
    isPaused_ = true;
    isStarted_ = false;

    // Create menubar and input widget
    createMenu();
    readInputs();

    // Adding infotextbar
    infoText = new QLabel("");
    infoText->setAlignment(Qt::AlignCenter);
    // Setting first value
    infoText->setText("Enter seed value and goal value");
    layout_->addWidget(infoText);

    // Creating mainwidget
    QWidget *w = new QWidget;

    // Creating gameboard widget
    board = new QGameBoard(w);
    board->init_empty();
    board->print();
    layout_->addWidget(w);

    // Create rest pushbuttons
    createMoveButtons();
    createButtons();

    // Setting up layout
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

/**
 * Creating menubar
 */
void MainWindow::createMenu()
{
    menuBar = new QMenuBar;
    fileMenu = new QMenu(tr("&Game"));
    fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    menuBar->addMenu(fileMenu);
    layout_->setMenuBar(menuBar);
}

/**
 * Creating labels and spinboxes for input receiving
 */
void MainWindow::readInputs() {
    // Creating inputlayout
    QGridLayout *inputs = new QGridLayout();

    // Creating seed input
    QLabel *seedLabel = new QLabel("Seed: ");
    seedInput_ = new QSpinBox();
    seedInput_->setRange(0, INT_MAX);

    // Creating goal input and setting range
    QLabel *goalLabel = new QLabel("Goal: ");
    goalInput_ = new QSpinBox();
    goalInput_->setRange(4, pow(2, SIZE*SIZE));
    goalInput_->setValue(DEFAULT_GOAL);

    // Adding widgets to inputlayout
    inputs->addWidget(seedLabel, 0, 0);
    inputs->addWidget(seedInput_, 0, 1);
    inputs->addWidget(goalLabel, 1, 0);
    inputs->addWidget(goalInput_, 1, 1);

    // Adding inputlayout to mainlayout
    layout_->addLayout(inputs);
}

/**
 * Creating four buttons for moving inputs
 * Up, left, right and down buttons
 */
void MainWindow::createMoveButtons()
{
    // Creating button layout
    QGridLayout *buttons = new QGridLayout();

    // Creating button up
    upButton_ = new QPushButton(tr("↑"));
    upButton_->setFixedSize(QSize(32,32));
    connect(upButton_, &QPushButton::clicked, this, [this]{move(UP, goal_);});
    buttons->addWidget(upButton_, 1, 2);

    // Creating button left
    leftButton_ = new QPushButton(tr("←"));
    buttons->addWidget(leftButton_, 2, 1);
    connect(leftButton_, &QPushButton::clicked, this, [this]{move(LEFT, goal_);});
    leftButton_->setFixedSize(QSize(32,32));

    // Creating button right
    rightButton_ = new QPushButton(tr("→"));
    rightButton_->setFixedSize(QSize(32,32));
    connect(rightButton_, &QPushButton::clicked, this, [this]{move(RIGHT, goal_);});
    buttons->addWidget(rightButton_, 2, 3);

    // Creating button down
    downButton_ = new QPushButton(tr("↓"));
    downButton_->setFixedSize(QSize(32,32));
    connect(downButton_, &QPushButton::clicked, this, [this]{move(DOWN, goal_);});
    buttons->addWidget(downButton_, 3, 2);

    // Disabling buttons
    upButton_->setDisabled(true);
    leftButton_->setDisabled(true);
    rightButton_->setDisabled(true);
    downButton_->setDisabled(true);

    // Adding buttonlayout to mainlayout
    layout_->addLayout(buttons);
}
/**
 * @brief Moves the number tiles in the gameboard
 * @param dir, pair<int, int>, direction where to move
 * @param goal, int
 */
void MainWindow::move(Coords dir, int goal) {
    unsigned int score = 0;

    // Moving numbers
    // If player reached goal function return true
    if(board->move(dir, goal)) {
        // Pausing game
        onStartClicked();

        // Congratulations for player
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

    // Checking has the player lost
    else if(board->is_full()) {
        // Pausing game
        onStartClicked();
        start_->setDisabled(true);

        // Informing player that he has lost
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

    // Printing gameboard situation
    board->new_value(false);
    board->print();

    // Displaying score
    score = board->get_score();
    QString text = QString("Your current score: %1").arg(score);
    infoText->setText(text);
}

/**
 * Function thats creates "main" buttons start, reset and exit
 */
void MainWindow::createButtons()
{
    // Creating layout for buttons
    QHBoxLayout *buttons = new QHBoxLayout();

    // Creating buttons
    start_ = new QPushButton("Start");
    reset_ = new QPushButton("Reset");
    QPushButton *exit = new QPushButton("Exit");

    // Adding functions for them
    connect(start_, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(reset_, &QPushButton::clicked, this, &MainWindow::onResetClicked);
    connect(exit,   &QPushButton::clicked, this, &QWidget::close);

    // Adding buttons to layout
    buttons->addWidget(start_);
    buttons->addWidget(reset_);
    buttons->addWidget(exit);

    // Disabling reset button
    reset_->setDisabled(true);

    // Adding buttons to mainlayout
    layout_->addLayout(buttons);
}

/**
 * On clicking start button, game starts. Then button is transformed to
 * pause/continue button. When pushing "pause" game stop receiving inputs
 * When pushing "continue" game starts again receiving inputs.
 */
void MainWindow::onStartClicked() {
    unsigned int score = 0;

    // Receiving goal input
    goal_ = (goalInput_->value());

    // Checking if input is a power of two
    if(ceil(log2(goal_)) != floor(log2(goal_))) {
        // Suggest nearest power of two
        double t = pow(2,round(log2(goal_)));
        QString text = QString("Goal isn't power of two, please change goal value to, for example, %1").arg(t);
        infoText->setText(text);
        return;
    }

    // Starting game
    if (isStarted_ == false) {
        // Updating bools
        isStarted_ = true;
        isPaused_ = false;

        // Enabling moving buttons and disabling inputs
        enableButtons();

        // Changing button to pause/continue button
        start_->setText("Pause");

        // Starting game
        board->fill(seedInput_->value());
        board->print();

    // Else button is pause/continue button
    } else {
        // Changing status
        isPaused_ = !isPaused_;

        // Changing buttons status
        enableButtons();

        // Changing infotext and name of the button
        if (isPaused_ == true) {
            start_->setText("Continue");
            infoText->setText("Game paused");
        } else {
            start_->setText("Pause");
        }
    }

    // Enabling reset button if game has started
    reset_->setEnabled(isStarted_);

    // Displaying score
    if (isPaused_ == false) {
        score = board->get_score();
        QString text = QString("Your current score: %1").arg(score);
        infoText->setText(text);
    }
}

/**
 * Reseting game
 */
void MainWindow::onResetClicked() {
    // Stopping game
    isStarted_ = false;
    isPaused_  = false;

    // Disabling buttons and enabling inputs
    enableButtons();
    reset_->setDisabled(true);

    infoText->setText("Enter seed value and goal value");

    // Changing pause/continue button to start button
    start_->setText("Start");
    start_->setEnabled(true);

    // Clearing gameboard
    board->clear();
    board->print();
}

/**
 * General function to enable or disable buttons and clearing infolabel
 */
void MainWindow::enableButtons() {
    // Clearing infoText
    infoText->setText("");
    infoText->setStyleSheet("");
    this->setStyleSheet("");

    // Enabling inputs if game is going to reset
    seedInput_->setDisabled(isStarted_);
    goalInput_->setDisabled(isStarted_);

    // Enabling or disabling moveButtons
    upButton_->setEnabled(isStarted_ && !isPaused_);
    leftButton_->setEnabled(isStarted_ && !isPaused_);
    rightButton_->setEnabled(isStarted_ && !isPaused_);
    downButton_->setEnabled(isStarted_ && !isPaused_);
}
