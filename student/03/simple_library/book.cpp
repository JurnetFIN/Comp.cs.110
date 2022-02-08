#include "book.hh"
#include "date.hh"
#include <string>
#include <iostream>

Book::Book():
    autor_(), name_(), loaned_(0)
{
}

Book::Book(std::string autor, std::string name):
    autor_(autor), name_(name)
{
}

void Book::print() const
{
    std::cout << name_ << " : " << name_ << std::endl;
}

void Book::loan(Date())
{
    Date::Date.print();
}
