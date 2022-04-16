#include "QtWidgets"

#include "mainwindow.hh"
#include "qgameboard.hh"

MainWindow::MainWindow(QGameBoard& board, QWidget* parent) :
    QDialog(parent),
    view_(this)
{
    createMenu();
    createButtons();

    //bigEditor = new QTextEdit;
    //bigEditor->setPlainText(tr("This widget takes up all the remaining space "
    //                           "in the top-level layout."));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->setMenuBar(menuBar);

    mainLayout->addWidget(board.window_);
    mainLayout->addWidget(horizontalGroupBox);
    //mainLayout->addWidget(bigEditor);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

void MainWindow::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"));
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);
}

void MainWindow::createButtons()
{
    horizontalGroupBox = new QGroupBox(tr("Horizontal layout"));
    QWidget *window = new QWidget;
    QGridLayout *layout = new QGridLayout(window);

    QPushButton *up_button = new QPushButton(tr("↑"));
    layout->addWidget(up_button, 1, 2);

    QPushButton *left_button = new QPushButton(tr("←"));
    layout->addWidget(left_button, 2, 1);

    QPushButton *right_button = new QPushButton(tr("→"));
    layout->addWidget(right_button, 2, 3);

    QPushButton *down_button = new QPushButton(tr("↓"));
    layout->addWidget(down_button, 3, 2);

    horizontalGroupBox->setLayout(layout);
}
