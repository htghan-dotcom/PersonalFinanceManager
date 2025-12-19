#include <iostream>
#include <string>
#include <limits>

#include "App.h"
#include "Utils.h"
#include "DataManager.h"

using namespace std;

void pauseScreen() {
    cout << "\n(Press Enter to continue...)";
    cin.get();
}

App::App() {
    data.loadAll();
    data.applyRecurringTransactions();
}

void App::run() {
    while (true) {
        showDashboard();
        handleChoice();
    }
}

void App::showDashboard() {
    cout << "\n===========================================\n";
    cout << "       PERSONAL FINANCE MANAGER       \n";
    cout << "===========================================\n\n";

    cout << "Total balance: " << data.getTotalBalance() << "\n";
    cout << "Wallet balance:\n";
    data.showWalletBalances();

    cout << "\n\n--- NAVIGATION MENU ---\n";
    cout << "1. Add Income\n";
    cout << "2. Add expense\n";
    cout << "3. Manage Wallets\n";
    cout << "4. Manage Sources & Categories\n";
    cout << "5. Recurring Transactions\n";
    cout << "6. Statistics\n";
    cout << "0. Exit\n";
}

void App::handleChoice() {
    int choice = readInt("Enter option: ");

    switch (choice) {
        case 1: addIncomeMenu(); break;
        case 2: addExpenseMenu(); break;
        case 3: showWalletMenu(); break;
        case 4: manageCategoriesMenu(); break;
        case 5: recurringMenu(); break;
        case 6: statisticsMenu(); break;

        case 0: {
            cout << "Saving data...\n";
            data.saveAll();
            cout << "Exiting...\n";
            exit(0);
        }
        default:
            cout << "Invalid choice! Try again" << endl;
            pauseScreen();
    }
}

void App::addIncomeMenu() {
    cout << "\n=== ADD INCOME ===\n";
    data.addIncomeTransactionUI(); 
    pauseScreen();
}

void App::addExpenseMenu() {
    cout << "\n=== ADD EXPENSE ===\n" << endl;
    data.addExpenseTransactionUI();
    pauseScreen();
}

void App::showWalletMenu() {
    while (true) {
        cout << "\n=== MANAGE WALLETS ===\n" << endl;
        cout << "1. Add Wallet\n";
        cout << "2. Change Wallet's Information\n";
        cout << "3. Delete Wallet\n";
        cout << "4. Show Wallets\n";
        cout << "0. Back\n";
        
        int c = readInt ("Choose option: ");

        switch (c) {
            case 1: data.addWalletUI(); pauseScreen(); break;
            case 2: data.editWalletUI(); pauseScreen(); break;
            case 3: data.deleteWalletUI(); pauseScreen(); break;
            case 4: data.showWallets(); pauseScreen(); break;
            case 0: cout << "Exiting!"; return;
            default:
                cout << "Invalid option\n";
                pauseScreen();
        }
    }
}

void App::manageCategoriesMenu() {
     while (true) {
        cout << "\n=== MANAGE CATEGORIES & SOURCES ===\n";
        cout << "1. Add Income Source\n";
        cout << "2. Edit Income Source\n";
        cout << "3. Delete Income Source\n";
        cout << "4. Show Income Sources\n";
        cout << "--- --- ---\n";
        cout << "5. Add Expense Category\n";
        cout << "6. Edit Expense Category\n";
        cout << "7. Delete Expense Category\n";
        cout << "8. Show Expense Categories\n";
        cout << "0. Back\n";
        
        int c = readInt ("Choose option: ");

        switch (c) {
            case 1: data.addIncomeSourceUI(); pauseScreen(); break;
            case 2: data.editIncomeSourceUI(); pauseScreen(); break;
            case 3: data.deleteIncomeSourceUI(); pauseScreen(); break;
            case 4: data.showIncomeSources(); pauseScreen(); break;
            case 5: data.addExpenseCategoryUI(); pauseScreen(); break;
            case 6: data.editExpenseCategoryUI(); pauseScreen(); break;
            case 7: data.deleteExpenseCategoryUI(); pauseScreen(); break;
            case 8: data.showExpenseCategories(); pauseScreen(); break;
            case 0: return;
            default:
                cout << "Invalid option\n";
                pauseScreen();
        }
    }
}

void App::recurringMenu() {
    while (true) {
        cout << "\n=== RECURRING TRANSACTIONS ===\n";
        cout << "1. Add Recurring\n";
        cout << "2. Remove Recurring\n";
        cout << "3. List Recurring\n";
        cout << "0. Back\n";
        
        int c = readInt ("Choose option: ");

        switch (c) {
            case 1: data.addRecurringTransactionUI(); pauseScreen(); break;
            case 2: data.deleteRecurringTransactionUI(); pauseScreen(); break;
            case 3: data.listRecurringTransactionsUI(); pauseScreen(); break;
            case 0: return;
            default:
                cout << "Invalid option\n";
                pauseScreen();
        }
    }
}

void App::statisticsMenu() {
    while (true) {
        cout << "\n=== STATISTICS & REPORTING ===\n";
        cout << "1. Time-based Statistics\n";
        cout << "2. Wallet Breakdown\n";
        cout << "3. Annual Overview\n";
        cout << "4. Annual Breakdown (Source / Category)\n";
        cout << "0. Back\n";

        int c = readInt("Choose option: ");

        switch (c) {
            case 1: data.showTimeBasedStatisticsUI(); pauseScreen(); break;
            case 2: data.showWalletBreakdownStatisticsUI(); pauseScreen(); break;
            case 3: data.showAnnualOverviewStatisticsUI(); pauseScreen(); break;
            case 4: data.showAnnualBreakdownStatisticsUI(); pauseScreen(); break;
            case 0: return;
            default:
                cout << "Invalid option.\n";
                pauseScreen();
        }
    }
}
