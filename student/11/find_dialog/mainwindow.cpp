#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "iostream"
#include "QString"
#include "fstream"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::check_file_existance(std::string file) {
    std::ifstream input(file);
    if( not input )
    {
            ui->textBrowser->setPlainText("File not found");
            return true;
    }
    return false;
}

void MainWindow::on_findPushButton_clicked()
{
    bool match_case = ui->matchCheckBox->checkState();
    std::string file = ui->fileLineEdit->text().toStdString();
    std::string key_line_text = ui->keyLineEdit->text().toStdString();

    std::ifstream input(file);
    if( not input ) {
        ui->textBrowser->setPlainText("File not found");
        return;
    }

    if (key_line_text.size() == 0) {
        ui->textBrowser->setPlainText("File found");
        return;
    }

    if(match_case == true) {
        std::string line = "";
        while(getline(input, line))
            if (line.find(key_line_text) != std::string::npos) {
                ui->textBrowser->setPlainText("Word found");
                return;
            }

    } else {
        std::string line = "";
        int correct_letters_in_word = 0;
        int word_size = key_line_text.size();
        while(getline(input, line)) {
            int row_lenght = line.size();
            for(int i=0;i<row_lenght; i++) {
                char ch = toupper(line[i]);
                if(ch == toupper(key_line_text[correct_letters_in_word])) {
                    ++correct_letters_in_word;
                } else {
                    correct_letters_in_word = 0;
                }

                if(word_size == correct_letters_in_word) {
                    ui->textBrowser->setPlainText("Word found");
                    return;
                }
            }
        }
    }

    ui->textBrowser->setPlainText("Word not found");
}
