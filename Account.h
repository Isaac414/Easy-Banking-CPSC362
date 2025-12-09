#pragma once
#include <string>
#include <iostream>

class Account {
protected:
    int id;
    std::string holder;
    double balance;
    std::string createdAt;

public:
    Account(int id_, const std::string& holder_, double initial)
        : id(id_), holder(holder_), balance(initial) {
        createdAt = makeTimestamp();
    }

    virtual ~Account() = default;

    int getId() const { return id; }
    const std::string& getHolder() const { return holder; }
    double getBalance() const { return balance; }
    const std::string& getCreationTime() const { return createdAt; }

    virtual void print(std::ostream& os) const {
        os << "Account ID: " << id << "\n";
        os << "Holder: " << holder << "\n";
        os << "Balance: $" << balance << "\n";
        os << "Created at: " << createdAt << "\n";
    }

    // Updated methods: return bool, error pointer optional
    virtual bool deposit(double amount, std::string* err = nullptr);
    virtual bool withdraw(double amount, std::string* err = nullptr);

protected:
    void updateTimestamp();

    static std::string makeTimestamp();
};

class CheckingAccount : public Account {
    double overdraftLimit;

public:
    CheckingAccount(int id_, const std::string& holder_, double initial, double overdraft = 200.0)
        : Account(id_, holder_, initial), overdraftLimit(overdraft) {}

    bool withdraw(double amount, std::string* err = nullptr) override;

    void print(std::ostream& os) const override {
        os << "Checking Account\n";
        Account::print(os);
        os << "Overdraft limit: $" << overdraftLimit << "\n";
    }
};

class SavingsAccount : public Account {
public:
    SavingsAccount(int id_, const std::string& holder_, double initial)
        : Account(id_, holder_, initial) {}

    void print(std::ostream& os) const override {
        os << "Savings Account\n";
        Account::print(os);
    }
};
