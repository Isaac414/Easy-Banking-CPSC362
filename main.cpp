#include <iostream>
#include <string>
#include <limits>
#include "AccountStore.h"
#include "Account.h"
#include <fstream>
#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

int main() {
    AccountStore store;
    const string filename = "accounts.csv";

    store.load(filename);

    httplib::Server svr;

    // Create Checking Account
    svr.Post("/create/checking", [&](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);

        string name = body["name"];
        double deposit = body["deposit"];
        double overdraft = body["overdraft"];

        Account* a = store.createChecking(name, deposit, overdraft);

        json response = {
            {"status", "ok"},
            {"id", a->getId()}
        };

        res.set_content(response.dump(), "application/json");
    });

    // Create Savings Account
    svr.Post("/create/savings", [&](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);

        string name = body["name"];
        double deposit = body["deposit"];

        Account* a = store.createSavings(name, deposit);

        json response = {
            {"status", "ok"},
            {"id", a->getId()}
        };

        res.set_content(response.dump(), "application/json");
    });

    // List all accounts
    svr.Get("/accounts", [&](const httplib::Request&, httplib::Response& res) {
        json list = json::array();
        for (auto& a : store.getAll()) {
            list.push_back({
                {"id", a->getId()},
                {"name", a->getHolder()},
                {"type", a->getType()},
                {"balance", a->getBalance()}
            });
        }
        res.set_content(list.dump(), "application/json");
    });

    // Deposit
    svr.Post("/deposit", [&](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);
        int id = body["id"];
        double amt = body["amount"];

        Account* a = store.findById(id);
        if (!a) {
            res.status = 400;
            res.set_content("{\"error\":\"Account not found\"}", "application/json");
            return;
        }

        string err;
        if (!a->deposit(amt, &err)) {
            res.status = 400;
            res.set_content(json({{"error", err}}).dump(), "application/json");
        } else {
            res.set_content(json({{"status","ok"},{"balance",a->getBalance()}}).dump(), "application/json");
        }
    });

    // Withdraw
    svr.Post("/withdraw", [&](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);
        int id = body["id"];
        double amt = body["amount"];

        Account* a = store.findById(id);
        if (!a) {
            res.status = 400;
            res.set_content("{\"error\":\"Account not found\"}", "application/json");
            return;
        }

        string err;
        if (!a->withdraw(amt, &err)) {
            res.status = 400;
            res.set_content(json({{"error", err}}).dump(), "application/json");
        } else {
            res.set_content(json({{"status","ok"},{"balance",a->getBalance()}}).dump(), "application/json");
        }
    });

    // Save
    svr.Post("/save", [&](const httplib::Request&, httplib::Response& res) {
        store.save(filename);
        res.set_content("{\"status\":\"saved\"}", "application/json");
    });

    cout << "Server running at http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);
}
