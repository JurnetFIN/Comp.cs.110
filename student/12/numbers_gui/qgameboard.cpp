#include "qgameboard.hh"
#include "numbertile.hh"

#include <QLabel>
#include <QWidget>

QGameBoard::QGameBoard()
{
    window_ = new QWidget();
    layout_ = new QGridLayout(window_);
}

QGameBoard::~QGameBoard()
{
    delete layout_;
    delete window_;
}

void QGameBoard::print() {
    for(auto i = 0; i < SIZE; ++i) {
        for(auto j = 0; j < SIZE; ++j)
        {
            NumberTile* tile = get_item(std::make_pair(i,j));

            QLabel *label = new QLabel();

            if(tile->get_value() != 0)
                label->setNum(tile->get_value());
            else
                label->setText("");

            //label->setFixedWidth(200);
            label->setAlignment(Qt::AlignCenter);

            switch (tile->get_value()) {
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
