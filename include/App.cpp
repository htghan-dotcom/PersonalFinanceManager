#include <iostream>
#include <string>

#include "App.h"

using namespace std;

void pauseScreen() {
    cout << "\n(Press Enter to continue...)";
    cin.ignore();
    cin.get();
}

void run() {
    while (true) {
        showDashboard();
        handleChoice();
    }
}

void showDashboard() {
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

void handleChoice() {
    cout << "\nEnter option: ";
    int choice;
    cin >> choice;

    if (!cin) {
        cin.clear();
        cin.ignore();
        cout << "Invalid input! Please enter a number." << endl;
        return;
    }

    cin.ignore();

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

void addIncomeMenu() {
    cout << "ADD INCOME" << endl;
    // add later
    pauseScreen();
}

void addExpenseMenu() {
    cout << "ADD EXPENSE" << endl;
    // add later
    pauseScreen();
}

void showWalletMenu() {
    cout << "MANAGE WALLETS" << endl;
    cout << "1. Add Wallet\n";
    cout << "2. Rename Wallet\n";
    cout << "3. Delete Wallet\n";
    cout << "4. Show Wallets\n";
    cout << "0. Back\n";
    pauseScreen();
}

void manageCategoriesMenu() {
    cout << "\n=== MANAGE CATEGORIES ===\n";
    cout << "1. Add Category\n";
    cout << "2. Edit Category\n";
    cout << "3. Delete Category\n";
    cout << "4. Show Categories\n";
    cout << "0. Back\n";
    pauseScreen();
}

void recurringMenu() {
    cout << "\n=== RECURRING TRANSACTIONS ===\n";
    cout << "1. Add Recurring\n";
    cout << "2. Remove Recurring\n";
    cout << "3. List Recurring\n";
    cout << "0. Back\n";
    pauseScreen();
}

void statisticsMenu() {
    cout << "\n=== STATISTICS ===\n";
    cout << "1. By Date Range\n";
    cout << "2. By Category\n";
    cout << "3. By Wallet\n";
    cout << "4. Monthly Summary\n";
    cout << "0. Back\n";
    pauseScreen();
}