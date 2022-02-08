#ifndef BOOK_HH
#define BOOK_HH
#include "date.hh"
#include <string>

class Book
{
public:
    Book();

    Book(std::string autor, std::string name);

    // Destructor
    ~Book();

    void print() const;
    void loan(Date d);
    void renew();
    void give_back();

private:
    std::string autor_;
    std::string name_;
    int loaned_;
    Date loandate_;
    Date returndate_;
};



#endif // BOOK_HH
