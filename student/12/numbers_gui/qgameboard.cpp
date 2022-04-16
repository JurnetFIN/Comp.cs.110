#include "qgameboard.hh"
#include "numbertile.hh"

#include <QLabel>

QGameBoard::QGameBoard()
{
    window_ = new QWidget;
    layout_ = new QGridLayout(window_);
}

QGameBoard::~QGameBoard()
{
    delete window_;
    delete layout_;
}

void QGameBoard::print() {
    for(auto i = 0; i < SIZE; ++i) {
        for(auto j = 0; j < SIZE; ++j)
        {
            NumberTile* tile = get_item(std::make_pair(i,j));

            QLabel *label = new QLabel();
            label->setNum(tile->get_value());

            layout_->addWidget(label, i, j);
        }
    }
}
