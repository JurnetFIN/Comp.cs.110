#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), credential_(has_credit), amount_(0) {
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::set_credit_limit(int amount) {
    if (credential_ == true) {
        creditlimit_ = amount;
    }
    else {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
    }
}

void Account::print() const {
    std::cout << owner_ << " : " << iban_ << " : " << amount_ << " euros" << std::endl;
}

void Account::save_money(int amount) {
    amount_ += amount;
}

bool Account::take_money(int amount) {
    if (credential_ == false) {
        if (amount <= amount_) {
            amount_ -= amount;
            std::cout << amount << " euros taken: new balance of " << iban_ << " is " << amount_ << " euros" << std::endl;
            return true;

        } else {
            std::cout << "Cannot take money: balance underflow" << std::endl;
            return false;
        }

    } else {
        if (amount <= (amount_ + creditlimit_)) {
            amount_ -= amount;
            std::cout << amount << " euros taken: new balance of " << iban_ << " is " << amount_ << " euros" << std::endl;
            return true;

        } else {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
            return false;
        }
    }
}

int Account::transfer_to(Account& to, int amount) {
    if (Account::take_money(amount) == true) {
        to.save_money(amount);
        return true;

    } else {
        std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        return false;
    }
}

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
