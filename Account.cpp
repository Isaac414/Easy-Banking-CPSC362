#include "Account.h"
#include <ctime>
#include <sstream>
#include <iomanip>

// Timestamp generation
std::string Account::makeTimestamp() {
    time_t now = time(nullptr);
    tm localTime;
    if (localtime_r(&now, &localTime) == nullptr) {
        return {};
    }
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void Account::updateTimestamp() {
    createdAt = makeTimestamp();
}

// Deposit returns bool and sets error if any
bool Account::deposit(double amount, std::string* err) {
    if (amount <= 0) {
        if (err) *err = "Deposit amount must be positive";
        return false;
    }
    balance += amount;
    updateTimestamp();
    if (err) *err = "";
    return true;
}

// Withdraw returns bool and sets error if any
bool Account::withdraw(double amount, std::string* err) {
    if (amount <= 0) {
        if (err) *err = "Withdrawal amount must be positive";
        return false;
    }
    if (amount > balance) {
        if (err) *err = "Insufficient funds";
        return false;
    }
    balance -= amount;
    updateTimestamp();
    if (err) *err = "";
    return true;
}

// CheckingAccount override for withdraw to include overdraft
bool CheckingAccount::withdraw(double amount, std::string* err) {
    if (amount <= 0) {
        if (err) *err = "Withdrawal amount must be positive";
        return false;
    }
    if (amount > balance + overdraftLimit) {
        if (err) *err = "Exceeded overdraft limit";
        return false;
    }
    balance -= amount;
    updateTimestamp();
    if (err) *err = "";
    return true;
}
