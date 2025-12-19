#include <iostream>
#include <fstream>
#include <ctime>
#include <numeric>

#include "DataManager.h"
#include "Utils.h"
#include "Wallet.h"
#include "Income.h"
#include "Expense.h"
#include "RecurringTransaction.h"
#include "Statistics.h"

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

string DataManager::getWalletName(const string& id) const {
    int index = findWalletIndexByID(wallets, walletCount, id);
    return (index != -1) ? wallets[index].name : id + " (Error)";
}

string DataManager::getIncomeSourceName(const string& id) const {
    int index = findIncomeSourceIndexByID(incomeSources, incomeSourceCount, id);
    return (index != -1) ? incomeSources[index].name : id + " (Error)";
}

string DataManager::getExpenseCategoryName(const string& id) const {
    int index = findExpenseCategoryIndexByID(expenseCategories, expenseCategoryCount, id);
    return (index != -1) ? expenseCategories[index].name : id + " (Error)";
}

void DataManager::addWalletUI() {
    Wallet w;
    ::addWallet(wallets, walletCount, w);
}

void DataManager::editWalletUI() {
    ::editWallet(wallets, walletCount);
}

void DataManager::deleteWalletUI() {
    ::deleteWallet(wallets, walletCount);
}

void DataManager::showWallets() {
    cout << "\n=== WALLETS ===\n";
    double total = 0;
    for (int i = 0; i < walletCount; i++) {
        cout << i + 1 << ". Name: " << wallets[i].name 
                      << " | Balance: " << wallets[i].balance << endl;
        total += wallets[i].balance;
    }
    cout << "--- Total Balance: " << total << " ---\n";
}

void DataManager::addIncomeSourceUI() {
    ::addIncomeSource(incomeSources, incomeSourceCount);
}

void DataManager::editIncomeSourceUI() {
    ::editIncomeSource(incomeSources, incomeSourceCount);
}

void DataManager::deleteIncomeSourceUI() {
    ::deleteIncomeSource(incomeSources, incomeSourceCount);
}

void DataManager::showIncomeSources() {
    cout << "\n=== INCOME SOURCES ===\n";
    for (int i = 0; i < incomeSourceCount; i++) {
        cout << i + 1 << ". Name: "
             << incomeSources[i].name << endl;
    }
}

void DataManager::addExpenseCategoryUI() {
    ::addExpenseCategory(expenseCategories, expenseCategoryCount);
}

void DataManager::editExpenseCategoryUI() {
    ::editExpenseCategory(expenseCategories, expenseCategoryCount);
}

void DataManager::deleteExpenseCategoryUI() {
    ::deleteExpenseCategory(expenseCategories, expenseCategoryCount);
}

void DataManager::showExpenseCategories() {
    cout << "\n=== EXPENSE CATEGORIES ===\n";
    for (int i = 0; i < expenseCategoryCount; i++) {
        cout << i + 1 << ". Name: "
             << expenseCategories[i].name << endl;
    }
}

void DataManager::addIncomeTransactionUI() {
    ::addIncomeTransaction(
        incomeTransactions,
        incomeTransactionCount,
        wallets,
        walletCount,
        incomeSources,
        incomeSourceCount
    );
}

void DataManager::addExpenseTransactionUI() {
    ::addExpenseTransaction(
        expenseTransactions,
        expenseTransactionCount,
        wallets,
        walletCount,
        expenseCategories,
        expenseCategoryCount
    );
}

double DataManager::getTotalBalance() const {
    double total = 0;
    for (int i = 0; i < walletCount; ++i) {
        total += wallets[i].balance;
    }
    return total;
}

int DataManager::getWalletCount() const {
    return walletCount;
}

void DataManager::showWalletBalances() const {
    for (int i = 0; i < walletCount; i++) {
        cout << "* " << wallets[i].name << ": " << wallets[i].balance << endl;
    }
}

void DataManager::applyRecurringTransactions() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int currentMonth = 1 + ltm->tm_mon;
    int currentYear = 1900 + ltm->tm_year;

    ::applyRecurringTransactions(
        recurringList, recurringCount, wallets, walletCount, 
        incomeTransactions, incomeTransactionCount, 
        expenseTransactions, expenseTransactionCount, 
        currentMonth, currentYear
    );
}

void DataManager::addRecurringTransactionUI() {
    cout << "\n=== ADD RECURRING TRANSACTION ===\n";
    
    string type = readLine("Enter transaction type (income/expense): ");
    bool isIncome = (type == "income");
    
    string sourceOrCategoryID;
    string walletID;
    
    if (isIncome) {
        sourceOrCategoryID = readLine("Enter Income Source ID: ");
    } else {
        sourceOrCategoryID = readLine("Enter Expense Category ID: ");
    }
    walletID = readLine("Enter Wallet ID: ");
    string note = readLine("Enter Description: ");

    ::addRecurring(recurringList, recurringCount, sourceOrCategoryID, walletID, isIncome, note);
}

void DataManager::listRecurringTransactionsUI() {
    ::listRecurring(
        recurringList, recurringCount, wallets, walletCount, 
        incomeSources, incomeSourceCount, 
        expenseCategories, expenseCategoryCount
    );
}

void DataManager::deleteRecurringTransactionUI() {
    ::deleteRecurring(recurringList, recurringCount);
}

void DataManager::showTimeBasedStatisticsUI() {
    cout << "\n=== TIME-BASED STATISTICS ===\n";

    Date from, to;
    cout << "Start date:\n";
    readDate(from);

    cout << "End date:\n";
    readDate(to);

    Statistics::timeBased(
        incomeTransactions, incomeTransactionCount,
        expenseTransactions, expenseTransactionCount,
        from, to
    );
}

void DataManager::showWalletBreakdownStatisticsUI() {
    cout << "\n=== WALLET BREAKDOWN STATISTICS ===\n";

    string walletID = readLine("Enter Wallet ID: ");

    if (findWalletIndexByID(wallets, walletCount, walletID) == -1) {
        cout << "Wallet not found.\n";
        return;
    }

    Date from, to;
    cout << "Enter start date:\n";
    readDate(from);

    cout << "Enter end date:\n";
    readDate(to);

    Statistics::walletBreakdown(
        walletID,
        incomeTransactions, incomeTransactionCount,
        expenseTransactions, expenseTransactionCount,
        from, to
    );
}

void DataManager::showAnnualOverviewStatisticsUI() {
    cout << "\n=== ANNUAL OVERVIEW ===\n";

    int yearNumber = readInt("Enter number of years: ");

    int* year = new int[yearNumber];
    for (int i = 0; i < yearNumber; i++) {
        year[i] = readInt("Enter year: ");
    }

    Statistics::annualOverview(
        incomeTransactions, incomeTransactionCount,
        expenseTransactions, expenseTransactionCount,
        year, yearNumber
    );
}

void DataManager::showAnnualBreakdownStatisticsUI() {
    cout << "\n=== ANNUAL BREAKDOWN ===\n";

    int yearNumber = readInt("Enter number of years: ");

    int* year = new int[yearNumber];
    for (int i = 0; i < yearNumber; i++) {
        year[i] = readInt("Enter year: ");
    }

    Statistics::annualSourceCategoryBreakdown(
        incomeSources, incomeSourceCount,
        incomeTransactions, incomeTransactionCount,
        expenseCategories, expenseCategoryCount,
        expenseTransactions, expenseTransactionCount,
        year, yearNumber
    );
}

void DataManager::loadWallets() {
    walletCount = 0;
    wallets = nullptr;
}

void DataManager::saveWallets() {
}

void DataManager::loadIncomeSources() {
    incomeSourceCount = 0;
    incomeSources = nullptr;
}

void DataManager::saveIncomeSources() {
}

void DataManager::loadExpenseCategories() {
    expenseCategoryCount = 0;
    expenseCategories = nullptr;
}

void DataManager::saveExpenseCategories() {
}

void DataManager::loadIncomeTransactions() {
    incomeTransactionCount = 0;
    incomeTransactions = nullptr;
}

void DataManager::saveIncomeTransactions() {
}

void DataManager::loadExpenseTransactions() {
    expenseTransactionCount = 0;
    expenseTransactions = nullptr;
}

void DataManager::saveExpenseTransactions() {
}

void DataManager::loadRecurring() {
    recurringCount = 0;
    recurringList = nullptr;
}

void DataManager::saveRecurring() {
}