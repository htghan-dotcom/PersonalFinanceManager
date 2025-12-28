#include <iostream>
#include <fstream>
#include <ctime>
#include <numeric>
#include <iomanip>

#include "DataManager.h"
#include "Utils.h"
#include "Wallet.h"
#include "Income.h"
#include "Expense.h"
#include "RecurringTransaction.h"
#include "Statistics.h"
#include "IncomeGlobals.h"
#include "ExpenseGlobals.h"

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
    ::editWallet(wallets, walletCount, 
                 incomeTransactions, incomeTransactionCount, 
                 expenseTransactions, expenseTransactionCount,
                 recurringList, recurringCount);
}


void DataManager::deleteWalletUI() {
    ::deleteWallet(wallets,
                   walletCount,
                   incomeTransactions,
                   incomeTransactionCount,
                   expenseTransactions,
                   expenseTransactionCount);
}


void DataManager::showWallets() {
    cout << "\n=== WALLETS ===\n";
    long double total = 0;
    for (int i = 0; i < walletCount; i++) {
        cout << i + 1 << ". ID: " << wallets[i].ID
             << " | Name: " << wallets[i].name
             << " | Balance: " << wallets[i].balance << endl;
        total += wallets[i].balance;
    }
    cout << "--- Total Balance: " << total << " ---\n";
}

void DataManager::addIncomeSourceUI() {
    ::addIncomeSource(incomeSources, incomeSourceCount);
}

void DataManager::editIncomeSourceUI() {
    ::editIncomeSource(incomeSources, incomeSourceCount, incomeTransactions, incomeTransactionCount);
}

void DataManager::deleteIncomeSourceUI() {
    :: deleteIncomeSource( incomeSources, incomeSourceCount , incomeTransactions, incomeTransactionCount);
}

void DataManager::showIncomeSources() {
    cout << "\n=== INCOME SOURCES ===\n";
    for (int i = 0; i < incomeSourceCount; i++) {
        cout << i + 1 << ". ID: " << incomeSources[i].ID
            << " | Name: " << incomeSources[i].name << endl;
    }
}

void DataManager::addExpenseCategoryUI() {
    ::addExpenseCategory(expenseCategories, expenseCategoryCount);
}

void DataManager::editExpenseCategoryUI() {
    ::editExpenseCategory(expenseCategories, expenseCategoryCount, expenseTransactions, expenseTransactionCount);
}

void DataManager::deleteExpenseCategoryUI() {
    :: deleteExpenseCategory(expenseCategories, expenseCategoryCount,expenseTransactions,expenseTransactionCount);
}

void DataManager::showExpenseCategories() {
    cout << "\n=== EXPENSE CATEGORIES ===\n";
    for (int i = 0; i < expenseCategoryCount; i++) {
        cout << i + 1 <<  ". ID: " << expenseCategories[i].id
            << " | Name: " << expenseCategories[i].name << endl;
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

void DataManager::showIncomeHistoryUI() {
    cout << "\n=== INCOME HISTORY ===\n";
    if (incomeTransactionCount == 0) cout << "No transactions yet.\n";
    
    for (int i = 0; i < incomeTransactionCount; i++) {
        cout << i + 1 << ". ";
        string sourceName = getIncomeSourceName(incomeTransactions[i].sourceID);
        string wallName = getWalletName(incomeTransactions[i].walletID);
        
        cout << "[" << incomeTransactions[i].date.day << "/" 
             << incomeTransactions[i].date.month << "/" 
             << incomeTransactions[i].date.year << "] "
             << left << setw(15) << sourceName 
             << " | Amount: " << setw(10) << incomeTransactions[i].amount
             << " | Wallet: " << wallName << "\n";
    }
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

void DataManager::showExpenseHistoryUI() {
    cout << "\n=== EXPENSE HISTORY ===\n";
    if (expenseTransactionCount == 0) 
        cout << "No transactions yet.\n";
    
    for (int i = 0; i < expenseTransactionCount; i++) {
        cout << i + 1 << ". ";
        string catName = getExpenseCategoryName(expenseTransactions[i].sourceID);
        string wallName = getWalletName(expenseTransactions[i].walletID);
        
        cout << "[" << expenseTransactions[i].date.day << "/" 
             << expenseTransactions[i].date.month << "/"
             << expenseTransactions[i].date.year << "] "
             << left << setw(15) << catName 
             << " | Amount: " << setw(10) << expenseTransactions[i].amount
             << " | Wallet: " << wallName << "\n";
    }
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
    if (walletCount == 0) {
        cout << "No wallet yet.\n";
    }
    for (int i = 0; i < walletCount; i++) {
            cout << " * " 
                << left << setw(6)  << ("[" + wallets[i].ID + "]")
                << left << setw(15) << wallets[i].name           
                << ": " 
                << right << setw(12) << fixed << setprecision(2) << wallets[i].balance << "\n";
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
    
    while (true) {
        if (isIncome) {
            sourceOrCategoryID = readLine("Enter Income Source ID: ");
            if (findIncomeSourceIndexByID(incomeSources, incomeSourceCount, sourceOrCategoryID) != -1) break;
            cout << "Error: Income Source ID not found!\n";
        } else {
            sourceOrCategoryID = readLine("Enter Expense Category ID: ");
            if (findExpenseCategoryIndexByID(expenseCategories, expenseCategoryCount, sourceOrCategoryID) != -1) break;
            cout << "Error: Expense Category ID not found!\n";
        }
        if (readLine("Try again? (y/n): ") == "n") return;
    }

    while (true) {
            walletID = readLine("Enter Wallet ID: ");
            if (findWalletIndexByID(wallets, walletCount, walletID) != -1) break;
            
            cout << "Error: Wallet ID not found!\n";
            if (readLine("Try again? (y/n): ") == "n") return;
        }

        string note = readLine("Enter Description (Optional): ");
        if (note.empty()) note = "No description";
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
    cout << "\n--- DETAILED INCOME ---" << endl;
    filterIncomeByDateRange(from, to);

    cout << "\n--- DETAILED EXPENSE ---" << endl;
    filterExpenseByDateRange(from, to);
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

// Hai hàm đọc và ghi string vào file binary để dùng cho các hàm sau

string readString(ifstream& in) {
    int len;
    in.read((char*)&len, sizeof(int));

    string s(len, '\0');
    in.read(&s[0], len);
    return s;
}

void writeString(ofstream& out, const string& s) {
    int len = s.size();
    out.write((char*)&len, sizeof(int));
    out.write(s.c_str(), len);
}

void DataManager::loadWallets() {
    ifstream in("wallets.dat", ios::binary);

    if (!in.is_open()) {
        walletCount = 0;
        wallets = nullptr;
        return;
    }

    in.read((char*)&walletCount, sizeof(int));
    wallets = new Wallet[walletCount];

    for (int i = 0; i < walletCount; i++) {
        wallets[i].ID = readString(in);
        wallets[i].name = readString(in);
        in.read((char*)&wallets[i].balance, sizeof(long double));
    }

    in.close();
}

void DataManager::saveWallets() {
    ofstream out("wallets.dat", ios::binary);
    if (!out.is_open()) return;

    out.write((char*)&walletCount, sizeof(int));

    for (int i = 0; i < walletCount; i++) {
        writeString(out, wallets[i].ID);
        writeString(out, wallets[i].name);
        out.write((char*)&wallets[i].balance, sizeof(long double));
    }

    out.close();
}

void DataManager::loadIncomeSources() {
    ifstream in("income_sources.dat", ios::binary);

    if (!in.is_open()) {
        incomeSourceCount = 0;
        incomeSources = nullptr;
        return;
    }

    in.read((char*)&incomeSourceCount, sizeof(int));
    incomeSources = new IncomeSource[incomeSourceCount];

    for (int i = 0; i < incomeSourceCount; i++) {
        incomeSources[i].ID = readString(in);
        incomeSources[i].name = readString(in);
    }

    in.close();
}

void DataManager::saveIncomeSources() {
    ofstream out("income_sources.dat", ios::binary);
    if (!out.is_open()) return;

    out.write((char*)&incomeSourceCount, sizeof(int));

    for (int i = 0; i < incomeSourceCount; i++) {
        writeString(out, incomeSources[i].ID);
        writeString(out, incomeSources[i].name);
    }

    out.close();
}

void DataManager::loadExpenseCategories() {
    ifstream in("expense_categories.dat", ios::binary);

    if (!in.is_open()) {
        expenseCategoryCount = 0;
        expenseCategories = nullptr;
        return;
    }

    in.read((char*)&expenseCategoryCount, sizeof(int));
    expenseCategories = new ExpenseCategory[expenseCategoryCount];

    for (int i = 0; i < expenseCategoryCount; i++) {
        expenseCategories[i].id = readString(in);
        expenseCategories[i].name = readString(in);
    }

    in.close();
}

void DataManager::saveExpenseCategories() {
    ofstream out("expense_categories.dat", ios::binary);
    if (!out.is_open()) return;

    out.write((char*)&expenseCategoryCount, sizeof(int));

    for (int i = 0; i < expenseCategoryCount; i++) {
        writeString(out, expenseCategories[i].id);
        writeString(out, expenseCategories[i].name);
    }

    out.close();
}

void DataManager::loadIncomeTransactions() {
    ifstream in("income_transactions.dat", ios::binary);
    if (!in.is_open()) {
        incomeTransactionCount = 0;
        incomeTransactions = nullptr;
        return;
    }

    in.read((char*)&incomeTransactionCount, sizeof(int));
    incomeTransactions = new IncomeTransaction[incomeTransactionCount];

    for (int i = 0; i < incomeTransactionCount; i++) {
        in.read((char*)&incomeTransactions[i].date, sizeof(Date));
        incomeTransactions[i].sourceID = readString(in);
        incomeTransactions[i].walletID = readString(in);
        in.read((char*)&incomeTransactions[i].amount, sizeof(double));
        incomeTransactions[i].note = readString(in);
    }

    in.close();
}

void DataManager::saveIncomeTransactions() {
    ofstream out("income_transactions.dat", ios::binary);
    if (!out.is_open()) return;

    out.write((char*)&incomeTransactionCount, sizeof(int));

    for (int i = 0; i < incomeTransactionCount; i++) {
        out.write((char*)&incomeTransactions[i].date, sizeof(Date));
        writeString(out, incomeTransactions[i].sourceID);
        writeString(out, incomeTransactions[i].walletID);
        out.write((char*)&incomeTransactions[i].amount, sizeof(double));
        writeString(out, incomeTransactions[i].note);
    }

    out.close();
}

void DataManager::loadExpenseTransactions() {
    std::ifstream in("expense_transactions.dat", std::ios::binary);
    if (!in.is_open()) {
        expenseTransactionCount = 0;
        expenseTransactions = nullptr;
        return;
    }

    in.read((char*)&expenseTransactionCount, sizeof(int));
    expenseTransactions = new ExpenseTransaction[expenseTransactionCount];

    for (int i = 0; i < expenseTransactionCount; i++) {
        in.read((char*)&expenseTransactions[i].date, sizeof(Date));
        expenseTransactions[i].sourceID = readString(in);
        expenseTransactions[i].walletID = readString(in);
        in.read((char*)&expenseTransactions[i].amount, sizeof(double));
        expenseTransactions[i].note = readString(in);
    }

    in.close();
}

void DataManager::saveExpenseTransactions() {
    std::ofstream out("expense_transactions.dat", std::ios::binary);
    if (!out.is_open()) return;

    out.write((char*)&expenseTransactionCount, sizeof(int));

    for (int i = 0; i < expenseTransactionCount; i++) {
        out.write((char*)&expenseTransactions[i].date, sizeof(Date));
        writeString(out, expenseTransactions[i].sourceID);
        writeString(out, expenseTransactions[i].walletID);
        out.write((char*)&expenseTransactions[i].amount, sizeof(double));
        writeString(out, expenseTransactions[i].note);
    }

    out.close();
}

void DataManager::loadRecurring() {
    ifstream in("recurring.dat", ios::binary);
    if (!in.is_open()) {
        recurringCount = 0;
        recurringList = nullptr;
        return;
    }

    in.read((char*)&recurringCount, sizeof(int));
    recurringList = new RecurringTransaction[recurringCount];

    for (int i = 0; i < recurringCount; i++) {
        in.read((char*)&recurringList[i].isIncome, sizeof(bool));
        recurringList[i].sourceOrCategoryID = readString(in);
        recurringList[i].walletID = readString(in);
        in.read((char*)&recurringList[i].amount, sizeof(double));
        recurringList[i].note = readString(in);

        in.read((char*)&recurringList[i].startDate, sizeof(Date));
        in.read((char*)&recurringList[i].endDate, sizeof(Date));
        in.read((char*)&recurringList[i].lastAppliedMonth, sizeof(int));
        in.read((char*)&recurringList[i].lastAppliedYear, sizeof(int));
    }

    in.close();
}

void DataManager::saveRecurring() {
    ofstream out("recurring.dat", ios::binary);
    if (!out.is_open()) return;

    out.write((char*)&recurringCount, sizeof(int));

    for (int i = 0; i < recurringCount; i++) {
        out.write((char*)&recurringList[i].isIncome, sizeof(bool));
        writeString(out, recurringList[i].sourceOrCategoryID);
        writeString(out, recurringList[i].walletID);
        out.write((char*)&recurringList[i].amount, sizeof(double));
        writeString(out, recurringList[i].note);

        out.write((char*)&recurringList[i].startDate, sizeof(Date));
        out.write((char*)&recurringList[i].endDate, sizeof(Date));
        out.write((char*)&recurringList[i].lastAppliedMonth, sizeof(int));
        out.write((char*)&recurringList[i].lastAppliedYear, sizeof(int));
    }

    out.close();
}