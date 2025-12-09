# Easy-Banking-CPSC362


## 🏦 Banking Console Application

This is a simple command-line interface (CLI) banking application written in **C++**. It allows users to create **Checking** and **Savings** accounts, perform deposits and withdrawals, list all accounts, and save/load account data to a CSV file.

### ⚙️ Prerequisites

To compile and run this application, you will need:

* A C++ compiler (e.g., GCC, Clang).
* Standard C++ library (using `<iostream>`, `<string>`, `<fstream>`, `<limits>`).
* The header and implementation files for `AccountStore` and `Account` classes, which are referenced in `main.cpp`.

### 🚀 How to Run

1.  **Compile the Code:** You will need to compile `main.cpp` along with the implementation files for `AccountStore.h` and `Account.h` (and any associated derived class files like `CheckingAccount.h`, `SavingsAccount.h`).

    A typical compilation command using GCC might look like this (assuming all source files are present):

    ```bash
    g++ main.cpp Account.cpp AccountStore.cpp -o banking_app
    ```

2.  **Execute the Application:** Run the generated executable file.

    ```bash
    ./banking_app
    ```

### 📋 Features

The application presents a menu with the following options:

| Option | Description | Details |
| :---: | :--- | :--- |
| **1** | **Create Checking Account** | Requires name, initial deposit, and an overdraft limit. |
| **2** | **Create Savings Account** | Requires name and initial deposit. |
| **3** | **List All Accounts** | Displays the ID, holder name, type, balance, and other relevant details for all active accounts. |
| **4** | **Deposit to Account** | Asks for Account ID and deposit amount. |
| **5** | **Withdraw from Account** | Asks for Account ID and withdrawal amount. Handles overdraft rules for Checking accounts. |
| **6** | **Save & Exit** | Saves the current state of all accounts to the **`accounts.csv`** file and terminates the program. |

### 📂 Persistence

The application uses a simple CSV file, named **`accounts.csv`**, to store and load account data between sessions.

* **Loading:** When the application starts, it attempts to load existing accounts from `accounts.csv` via the `store.load(filename)` call.
* **Saving:** Option `6` uses `store.save(filename)` to write the current data back to the file.

### ⚠️ Important Notes

* **Error Handling:** The current implementation uses basic input validation and error messages (e.g., "Account not found," "Error: Insufficient funds") but may benefit from more robust input handling (especially for non-numeric input for amounts/IDs).
* **Dependencies:** The core functionality relies on the correct implementation of the **`AccountStore.h`** and **`Account.h`** header files, as well as the derived class implementations for checking and savings accounts.
