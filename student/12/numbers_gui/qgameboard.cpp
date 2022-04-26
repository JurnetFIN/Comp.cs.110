#include "qgameboard.hh"
#include "numbertile.hh"

#include <QLabel>
#include <QWidget>

QGameBoard::QGameBoard(QWidget *parent)
{
    layout_ = new QGridLayout(parent);

    for(auto i = 0; i < SIZE; ++i) {
        for(auto j = 0; j < SIZE; ++j)
        {
            QLabel *label = new QLabel();
            layout_->addWidget(label, i, j);
        }
    }
}

QGameBoard::~QGameBoard()
{ 
}

/**
 * Print gameboard
 */
void QGameBoard::print() {
    for(auto i = 0; i < SIZE; ++i) {
        for(auto j = 0; j < SIZE; ++j)
        {
            // Getting tile
            NumberTile* tile = get_item(std::make_pair(i,j));

            // Get pointer to label from layout
            QLayoutItem* item = layout_->itemAtPosition(i,j);
            QWidget* widget = item->widget();
            QLabel* label = dynamic_cast<QLabel*>(widget);
            label->setAlignment(Qt::AlignCenter);

            int tileValue = 0;

            // Sanity check
            if (tile)
                tileValue = tile->get_value();

            // Setting value for label
            if (tileValue > 0)
                label->setNum(tileValue);
            else
                label->setText("");

            // Setting style of label depending on the value
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
        }
    }
}

/**
 * Counting score by adding together values of tiles
 * @return score
 */
unsigned int QGameBoard::get_score() {
    unsigned int score = 0;

    // Counting score
    for(auto i = 0; i < SIZE; ++i) {
        for(auto j = 0; j < SIZE; ++j)
        {
            NumberTile* tile = get_item(std::make_pair(i,j));

            int tileValue = 0;

            if (tile) {
                tileValue = tile->get_value();
            }

            score += tileValue;
        }
    }

    // Subtract starting grid
    if (score < 2*SIZE)
        score  = 0;
    else
        score -= 2*SIZE;

    return score;
}
