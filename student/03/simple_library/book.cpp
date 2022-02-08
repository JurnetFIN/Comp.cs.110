#include "book.hh"
#include "date.hh"
#include <string>
#include <iostream>

Book::Book():
    autor_(""), name_(""), loaned_(0)
{
}

Book::Book(std::string autor, std::string name):
    autor_(autor), name_(name), loaned_(0)
{
}

Book::~Book()
{
}


void Book::print() const
{
    std::cout << autor_ << " : " << name_ << std::endl;
    if (loaned_ == 1) {
        std::cout << "- loaned: ";
        loandate_.print();
        std::cout << "- to be returned: ";
        returndate_.print();
    } else {
        std::cout << "- available" << std::endl;
    }
}

void Book::loan(Date d)
{
    if (loaned_ == 1) {
        std::cout << "Already loaned: cannot be loaned" << std::endl;
    } else {
        loaned_ = 1;
        loandate_ = d;

        returndate_ = d;
        returndate_.advance(28);
    }
}

void Book::renew()
{
    if (loaned_ == 1) {
        returndate_.advance(28);
    } else {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
    }
}

void Book::give_back()
{
    loaned_ = 0;
}
