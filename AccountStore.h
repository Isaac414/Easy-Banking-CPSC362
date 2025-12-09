#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Account.h"

class AccountStore {
    std::vector<std::unique_ptr<Account>> accounts;
    int nextId = 1;  // To assign unique IDs

public:
    Account* createChecking(const std::string& name, double initial, double overdraft = 200.0);
    Account* createSavings(const std::string& name, double initial);

    Account* findById(int id);
    void listAll() const;

    bool save(const std::string& path) const;
    bool load(const std::string& path);
};
