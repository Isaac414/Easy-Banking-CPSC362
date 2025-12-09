#include "AccountStore.h"
#include <fstream>
#include <sstream>
#include <iostream>

Account* AccountStore::createChecking(const std::string& name, double initial, double overdraft) {
    accounts.push_back(std::make_unique<CheckingAccount>(nextId++, name, initial, overdraft));
    return accounts.back().get();
}

Account* AccountStore::createSavings(const std::string& name, double initial) {
    accounts.push_back(std::make_unique<SavingsAccount>(nextId++, name, initial));
    return accounts.back().get();
}

Account* AccountStore::findById(int id) {
    for (auto& acc : accounts) {
        if (acc->getId() == id) return acc.get();
    }
    return nullptr;
}

void AccountStore::listAll() const {
    if (accounts.empty()) {
        std::cout << "No accounts yet.\n";
        return;
    }
    for (const auto& acc : accounts) {
        acc->print(std::cout);
        std::cout << "\n";
    }
}

bool AccountStore::save(const std::string& path) const {
    std::ofstream f(path);
    if (!f) return false;

    for (const auto& acc : accounts) {
        std::stringstream line;
        if (dynamic_cast<const CheckingAccount*>(acc.get())) {
            line << "Checking";
        }
        else if (dynamic_cast<const SavingsAccount*>(acc.get())) {
            line << "Savings";
        }
        else {
            line << "Account";
        }
        line << "," << acc->getId() << ",\"" << acc->getHolder() << "\"," << acc->getBalance();
        f << line.str() << "\n";
    }
    return true;
}

bool AccountStore::load(const std::string& path) {
    std::ifstream f(path);
    if (!f) return false;

    accounts.clear();
    nextId = 1;

    std::string line;
    while (std::getline(f, line)) {
        std::stringstream ss(line);
        std::string type, idStr, holder, balanceStr;

        std::getline(ss, type, ',');
        std::getline(ss, idStr, ',');
        std::getline(ss, holder, ',');
        std::getline(ss, balanceStr);

        // Remove quotes from holder if any
        if (!holder.empty() && holder.front() == '"') holder.erase(0, 1);
        if (!holder.empty() && holder.back() == '"') holder.pop_back();

        int id = std::stoi(idStr);
        double balance = std::stod(balanceStr);

        if (type == "Checking") {
            accounts.push_back(std::make_unique<CheckingAccount>(id, holder, balance));
        } else if (type == "Savings") {
            accounts.push_back(std::make_unique<SavingsAccount>(id, holder, balance));
        } else {
            accounts.push_back(std::make_unique<Account>(id, holder, balance));
        }

        if (id >= nextId) nextId = id + 1;
    }
    return true;
}
