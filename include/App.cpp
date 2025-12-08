#include <iostream>
#include <string>
#include <limits>

#include "App.h"

using namespace std;

// Helper function

int readInt (const string &prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        } else {
            cout << "Invalid input. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

double readDouble (const string &prompt) {
    double x;
    while (true) {
        cout << prompt;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        } else {
            cout << "Invalid input. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string readLine(const string &prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

void pauseScreen() {
    cout << "\n(Press Enter to continue...)";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void App::run() {
    while (true) {
        showDashboard();
        handleChoice();
    }
}

void App::showDashboard() {
    cout << "\n====================\n";
    cout << "       PERSONAL FINANCE MANAGER       \n";
    cout << "======================\n\n";

    cout << "Total balance: \n";
    cout << "Wallet balance: \n";

    cout << "1. Add Income\n";
    cout << "2. Add expense\n";
    cout << "3. Manage Wallets\n";
    cout << "4. Manage Categories\n";
    cout << "5. Recurring Transactions\n";
    cout << "6. Statistics\n";
    cout << "0. Exit\n";
}

void App::handleChoice() {
    cout << "\nEnter option: ";
    int choice;
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number." << endl;
        pauseScreen();
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
        case 1: addIncomeMenu(); break;
        case 2: addExpenseMenu(); break;
        case 3: showWalletMenu(); break;
        case 4: manageCategoriesMenu(); break;
        case 5: recurringMenu(); break;
        case 6: statisticsMenu(); break;
        case 0: cout << "Exiting..." << endl; exit(0);
        default:
            cout << "Invalid choice! Try again" << endl;
            pauseScreen();
    }
}

void App::addIncomeMenu() {
    cout << "ADD INCOME" << endl;
    // add later
    pauseScreen();
}

void App::addExpenseMenu() {
    cout << "ADD EXPENSE" << endl;
    // add later
    pauseScreen();
}

void App::showWalletMenu() {
    while (true) {
        cout << "MANAGE WALLETS" << endl;
        cout << "1. Add Wallet\n";
        cout << "2. Rename Wallet\n";
        cout << "3. Delete Wallet\n";
        cout << "4. Show Wallets\n";
        cout << "0. Back\n";
        
        cout << "Choose option: ";
        int c;
        cin >> c;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (c == 0) break;
        switch (c) {
            case 1:
                cout << "Add Wallet\n";
                pauseScreen();
                break;
            case 2:
                cout << "Rename Wallet\n";
                pauseScreen();
                break;
            case 3:
                cout << "Delete Wallet\n";
                pauseScreen();
                break;
            case 4:
                cout << "Show Wallets\n";
                pauseScreen();
                break;
            default:
                cout << "Invalid option\n";
                pauseScreen();
        }
    }
}

void App::manageCategoriesMenu() {
    cout << "\n=== MANAGE CATEGORIES ===\n";
    cout << "1. Add Category\n";
    cout << "2. Edit Category\n";
    cout << "3. Delete Category\n";
    cout << "4. Show Categories\n";
    cout << "0. Back\n";
    pauseScreen();
}

void App::recurringMenu() {
    cout << "\n=== RECURRING TRANSACTIONS ===\n";
    cout << "1. Add Recurring\n";
    cout << "2. Remove Recurring\n";
    cout << "3. List Recurring\n";
    cout << "0. Back\n";
    pauseScreen();
}

void App::statisticsMenu() {
    cout << "\n=== STATISTICS ===\n";
    cout << "1. By Date Range\n";
    cout << "2. By Category\n";
    cout << "3. By Wallet\n";
    cout << "4. Monthly Summary\n";
    cout << "0. Back\n";
    pauseScreen();
}