#include "book.hh"
#include <iostream>
#include "date.hh"


Book::Book(const std::string author, const std::string title):
    author_(author), name_(title), is_available_(true), loan_start_(Date()), loan_end_(Date()) {
}

Book::~Book() {}

void Book::print() {
    std::cout << author_ << " : " << name_ << std::endl;
    if (is_available_) {
        std::cout << "- available" << std::endl;
    } else {
        std::cout << "- loaned: ";
        loan_start_.print();
        std::cout << "- to be returned: ";
        loan_end_.print();
    }
}

void Book::loan(Date& day) {
    if (is_available_) {
        is_available_ = false;
        loan_start_ = day;
        loan_end_ = loan_start_;
        loan_end_.advance(28);
    } else {
        std::cout << "Already loaned: cannot be loaned" << std::endl;;
    }
}

void Book::renew() {
    if (!is_available_) {
        loan_end_.advance(28);
    } else {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
    }
}

void Book::give_back() {
    is_available_ = true;
}
