#ifndef BOOK_HH
#define BOOK_HH
#include "date.hh"
#include <string>

using namespace std;


class Book
{
public:
    Book(const string name,const string author);
    // Destructor
      ~Book();
    void loan(Date& d);
    void print();
    void renew();
    void give_back();

private:
    string name_;
    string author_;
    bool is_available_;
    bool is_loan_;
    Date loan_start_;
    Date loan_end_;
};

#endif // BOOK_HH
