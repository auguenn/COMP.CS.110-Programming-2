#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::print() const
{
    std::cout << owner_ << " : " << iban_ << " : " << balance_ << " euros" << std::endl;
}

void Account::set_credit_limit(int amount)
{

    if (this->has_credit_==false)
    {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
    }
    else {
        this->credit_balance_=amount;

    }
}

void Account::save_money(int x)
{
    this->balance_=x;
}

void Account::take_money(int amount)
{
    if (this->has_credit_==true) {
        if (this->balance_+credit_balance_-amount<=0) {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;

        }
        this->balance_-=amount;
        std::cout << amount << " euros taken: " << "new balance of " << this->iban_ << " is " << this->balance_ << " euros" << std::endl;
    }
    else {
        this->balance_-=amount;
        if (this->balance_<0) {
            std::cout<< "Cannot take money: balance underflow"<<std::endl;
            this->balance_+=amount;
        }
        else {
            std::cout << amount << " euros taken: " << "new balance of " << this->iban_ << " is " << this->balance_ << " euros" << std::endl;
        }

    }
}

void Account::transfer_to(Account &a1, int amount)
{
    if (this->has_credit_==true) {
        if(this->balance_+credit_balance_-amount<=0){
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
            std::cout << "Transfer from " << this->iban_ << " failed" << std::endl;
        }
        else {
            this->balance_-= amount;
            a1.balance_+= amount;
            std::cout << amount << " euros taken: " << "new balance of " << this->iban_ << " is " << this->balance_ << " euros" << std::endl;
        }
    }
    else {
        if(this->balance_-amount<0) {
            std::cout << "Cannot take money: balance underflow" << std::endl;
            std::cout << "Transfer from " << this->iban_ << " failed" << std::endl;
        }
        else {
            this->balance_-=amount;
            a1.balance_+=amount;
            std::cout << amount << " euros taken: " << "new balance of " << this->iban_ << " is " << this->balance_ << " euros" << std::endl;
        }
    }
}
