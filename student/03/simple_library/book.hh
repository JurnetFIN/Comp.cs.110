#ifndef BOOK_HH
#define BOOK_HH
#include <string>

class Book
{
public:
    Book();

    Book(std::string autor, std::string name);

    // Destructor
    ~Book();

    void print() const;
    void loan(class Date);

private:
    std::string autor_;
    std::string name_;
    int loaned_;

};



#endif // BOOK_HH
