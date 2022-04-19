#include "qgameboard.hh"
#include "numbertile.hh"

#include <QLabel>
#include <QWidget>

QGameBoard::QGameBoard(QWidget *parent)
{
    widget_ = parent;
    layout_ = nullptr;
}

QGameBoard::~QGameBoard()
{
    delete layout_;
    delete widget_;
}

void QGameBoard::print() {
    delete layout_;

    layout_ = new QGridLayout(widget_);
    for(auto i = 0; i < SIZE; ++i) {
        for(auto j = 0; j < SIZE; ++j)
        {
            NumberTile* tile = get_item(std::make_pair(i,j));

            QLabel *label = new QLabel();

            int tileValue = 0;

            if (tile) {
                tileValue = tile->get_value();
            }

            if (tileValue > 0)
                label->setNum(tileValue);
            else
                label->setText("");

            label->setAlignment(Qt::AlignCenter);

            switch (tileValue) {
            case 2: {
                label->setStyleSheet("QLabel { background: rgb(238,228,218); color: rgb(119,110,101); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 4: {
                label->setStyleSheet("QLabel { background: rgb(237,224,200); color: rgb(119,110,101); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 8: {
                label->setStyleSheet("QLabel { background: rgb(242,177,121); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 16: {
                label->setStyleSheet("QLabel { background: rgb(245,150,100); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 32: {
                label->setStyleSheet("QLabel { background: rgb(245,125,95); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 64: {
                label->setStyleSheet("QLabel { background: rgb(245,95,60); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 128: {
                label->setStyleSheet("QLabel { background: rgb(237,207,114); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 256: {
                label->setStyleSheet("QLabel { background: rgb(237,204,97); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 512: {
                label->setStyleSheet("QLabel { background: rgb(237,204,97); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 1024: {
                label->setStyleSheet("QLabel { background: rgb(237,204,97); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 2048: {
                label->setStyleSheet("QLabel { background: rgb(237,204,97); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            default: {
                label->setStyleSheet("QLabel { background: rgb(238,228,218); color: rgb(119,110,101); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            }
            layout_->addWidget(label, i, j);
        }
    }
}
