
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>    
#include "Expense.h"

using namespace std;

ExpenseTransaction* gExpTrans = nullptr;
int gExpTransCount = 0;

int findExpenseCategoryIndexByID(ExpenseCategory* cate, int count, string id) {
    for (int i = 0; i < count; ++i) {
        if (cate[i].id == id) return i;
    }
    return -1;
}

int askAndFindExpenseSourceIndexByID(ExpenseCategory* cate, int count) {
    cout << "Enter ExpenseCategory ID: ";
    string id;
    getline(cin, id);
    if (id.empty()) getline(cin, id);
    int idx = findExpenseCategoryIndexByID(cate, count, id);
    if (idx == -1) {
        cout << "ExpenseCategory with ID = " << id << " not found.\n";
    }
    return idx;
}

bool isValidExpenseID(const string& id) {
    if (id.size() != 5) return false;
    if (id[0] != 'E') return false;
    for (int i = 1; i < 5; ++i) {
        if (!isdigit((id[i]))) return false;
    }
    return true;
}

void addExpenseCategory(ExpenseCategory*& cate, int& count) {
    ExpenseCategory c;

    cout << "Enter ID(the format should be Eabcd with a,b,c,d is a number): ";
    cin >> c.id;
    if (!isValidExpenseID(c.id)) {
        cout << "ERROR: Invalid ID format. Required: 'E' followed by 4 digits (e.g., E0001). Please try again.\n";
        return;
    }

    if (findExpenseCategoryIndexByID(cate, count, c.id) != -1) {
        cout << "ID already exists! Cannot add.\n";
        return;
    }

    cout << "Enter category name: ";
    getline(cin >> std::ws, c.name);

    ExpenseCategory* newArr = new ExpenseCategory[count + 1];
    for (int i = 0; i < count; ++i) newArr[i] = cate[i];
    newArr[count] = c;

    delete[] cate;
    cate = newArr;
    ++count;

    cout << "ExpenseCategory added successfully.\n";
}

void editExpenseCategory(ExpenseCategory* cate, int count) {
    int idx = askAndFindExpenseSourceIndexByID(cate, count);
    if (idx == -1) return;

    cout << "Current name: " << cate[idx].name << "\nEnter new name: ";
    string name;
    getline(cin, name);
    if (!name.empty()) cate[idx].name = name;

    cout << "ExpenseCategory updated successfully.\n";
}

void deleteExpenseCategory(ExpenseCategory*& cate, int& count) {
    int idx = askAndFindExpenseSourceIndexByID(cate, count);
    if (idx == -1) return;

    ExpenseCategory* newArr = new ExpenseCategory[count - 1];
    for (int i = 0, j = 0; i < count; ++i) {
        if (i == idx) continue;
        newArr[j++] = cate[i];
    }
    delete[] cate;
    cate = newArr;
    --count;

    cout << "ExpenseCategory deleted successfully.\n";
}

void addExpenseTransaction(ExpenseTransaction*& trans, int& transCount,
    Wallet* wallets, int walletCount,
    ExpenseCategory* sources, int CategoryCount)
{
    ExpenseTransaction t;

    cout << "Enter date (dd mm yyyy): ";
    cin >> t.date.day >> t.date.month >> t.date.year;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter sourceID (Expense category ID): ";
    getline(cin, t.sourceID);
    if (findExpenseCategoryIndexByID(sources, CategoryCount, t.sourceID) == -1) {
        cout << "ExpenseCategory ID = " << t.sourceID << " not found. Cancel.\n";
        return;
    }

    cout << "Enter walletID (integer): ";
    string walletID;
    getline(cin, walletID);
    if (walletID.empty()) getline(cin, walletID);

    int widx = findWalletIndexByID(wallets, walletCount, walletID);
    if (widx == -1) {
        cout << "Wallet ID = " << walletID << " not found. Cancel.\n";
        return;
    }
    t.walletID = walletID;

    cout << "Enter amount (>=0): ";
    cin >> t.amount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (t.amount < 0) {
        cout << "Invalid amount. Cancel.\n";
        return;
    }

    cout << "Enter note: ";
    getline(cin, t.note);

    ExpenseTransaction* newArr = new ExpenseTransaction[transCount + 1];
    for (int i = 0; i < transCount; ++i) newArr[i] = trans[i];
    newArr[transCount] = t;

    delete[] trans;
    trans = newArr;
    ++transCount;

    gExpTrans = trans;
    gExpTransCount = transCount;

    cout << "ExpenseTransaction added successfully.\n";
}

void printExpenseTransaction(ExpenseTransaction t) {
    cout << "ExpenseTransaction {"
        << ", date=";
        printDate(t.date);
        cout << ", sourceID=" << t.sourceID
        << ", walletID=" << t.walletID
        << ", amount=" << fixed << setprecision(2) << t.amount
        << ", note=" << t.note
        << " }\n";
}

void filterExpenseByDateRange(Date from, Date to) {
    if (gExpTrans == nullptr || gExpTransCount == 0) {
        cout << "No ExpenseTransaction data (gExpTrans is empty).\n";
        return;
    }
    cout << "=== Expenses from "
        << from.day << "/" << from.month << "/" << from.year << " to "
        << to.day << "/" << to.month << "/" << to.year << " ===\n";

    bool found = false;
    for (int i = 0; i < gExpTransCount; ++i) {
        if (isDateInRange(gExpTrans[i].date, from, to)) {
            printExpenseTransaction(gExpTrans[i]);
            found = true;
        }
    }
    if (!found) cout << "No transactions found in the given date range.\n";
}

void filterExpenseByWallet(int walletID, Date from, Date to) {
    if (gExpTrans == nullptr || gExpTransCount == 0) {
        cout << "No ExpenseTransaction data (gExpTrans is empty).\n";
        return;
    }
    string walletIDStr = to_string(walletID);

    cout << "=== Expenses for walletID=" << walletID << " from "
        << from.day << "/" << from.month << "/" << from.year << " to "
        << to.day << "/" << to.month << "/" << to.year << " ===\n";

    bool found = false;
    for (int i = 0; i < gExpTransCount; ++i) {
        if (gExpTrans[i].walletID == walletIDStr &&
            isDateInRange(gExpTrans[i].date, from, to)) {
            printExpenseTransaction(gExpTrans[i]);
            found = true;
        }
    }
    if (!found) cout << "No matching transactions found.\n";
}

