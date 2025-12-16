#include <iostream>

#include "DataManager.h"

using namespace std;

void DataManager::loadAll() {
    loadWallets();
    loadIncomeSources();
    loadExpenseCategories();
    loadIncomeTransactions();
    loadExpenseTransactions();
    loadRecurring();
}

void DataManager::saveAll() {
    saveWallets();
    saveIncomeSources();
    saveExpenseCategories();
    saveIncomeTransactions();
    saveExpenseTransactions();
    saveRecurring();
}

void DataManager::addWalletUI() {
    Wallet w;
    cout << "Wallet ID: ";
    cin >> w.ID;
    cout << "Wallet name: ";
    getline(cin, w.name);
    cout << "Initial balance: ";
    cin >> w.balance;

    addWallet(wallets, walletCount, w);
}

void DataManager::editWalletUI() {
    editWallet(wallets, walletCount);
}

void DataManager::deleteWalletUI() {
    deleteWallet(&wallets, &walletCount);
}

void DataManager::showWallets() {
    cout << "\n=== WALLETS ===\n";
    for (int i = 0; i < walletCount; i++) {
        cout << wallets[i].ID << " | "
             << wallets[i].name << " | "
             << wallets[i].balance << endl;
    }
}

void DataManager::addIncomeSourceUI() {
    addIncomeSource(incomeSources, incomeSourceCount);
}

void DataManager::editIncomeSourceUI() {
    editIncomeSource(incomeSources, incomeSourceCount);
}

void DataManager::deleteIncomeSourceUI() {
    deleteIncomeSource(incomeSources, incomeSourceCount);
}

void DataManager::showIncomeSources() {
    cout << "\n=== INCOME SOURCES ===\n";
    for (int i = 0; i < incomeSourceCount; i++) {
        cout << incomeSources[i].ID << " | "
             << incomeSources[i].name << endl;
    }
}

void DataManager::addExpenseCategoryUI() {
    addExpenseCategory(expenseCategories, expenseCategoryCount);
}

void DataManager::editExpenseCategoryUI() {
    editExpenseCategory(expenseCategories, expenseCategoryCount);
}

void DataManager::deleteExpenseCategoryUI() {
    deleteIncomeSource(expenseCategories, expenseCategoryCount);
}

void DataManager::showExpenseCategories() {
    cout << "\n=== EXPENSE CATEGORIES ===\n";
    for (int i = 0; i < expenseCategoryCount; i++) {
        cout << expenseCategories[i].id << " | "
             << expenseCategories[i].name << endl;
    }
}

void DataManager::addIncomeTransactionUI() {
    addIncomeTransaction(
        incomeTransactions,
        incomeTransactionCount,
        wallets,
        walletCount,
        incomeSources,
        incomeSourceCount
    );
}

void DataManager::addExpenseTransactionUI() {
    addExpenseTransaction(
        expenseTransactions,
        expenseTransactionCount,
        wallets,
        walletCount,
        expenseCategories,
        expenseCategoryCount
    );
}

void applyRecurringTransactions() {}

// FILE BINARY / XML

void loadWallets();
void saveWallets();

void loadIncomeSources();
void saveIncomeSources();

void loadExpenseCategories();
void saveExpenseCategories();

void loadIncomeTransactions();
void saveIncomeTransactions();

void loadExpenseTransactions();
void saveExpenseTransactions();

void loadRecurring();
void saveRecurring();

