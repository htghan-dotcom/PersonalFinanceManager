#include <iostream>
#include <string>

#include "Utils.h"
#include "RecurringTransaction.h"
#include "Wallet.h"
#include "Income.h"
#include "Expense.h"

using namespace std;

string findWalletNameByID_Recur(Wallet* wallets, int walletCount, const string& id) {
    int index = findWalletIndexByID(wallets, walletCount, id);
    return (index != -1) ? wallets[index].name : id + " (Not Found)";
}

string findSourceNameByID_Recur(IncomeSource* sources, int count, const string& id) {
    int index = findIncomeSourceIndexByID(sources, count, id);
    return (index != -1) ? sources[index].name : id + " (Not Found)";
}

string findCategoryNameByID_Recur(ExpenseCategory* categories, int count, const string& id) {
    int index = findExpenseCategoryIndexByID(categories, count, id);
    return (index != -1) ? categories[index].name : id + " (Not Found)";
}

bool shouldApply(const RecurringTransaction& r, int currentMonth, int currentYear) {
    Date nextApplyDate = {r.startDate.day, currentMonth, currentYear};

    if (r.lastAppliedYear == currentYear && r.lastAppliedMonth == currentMonth) {
        return false; 
    }

    if (compareDate(nextApplyDate, r.endDate) == -1) {
        return false;
    }

    if (currentYear < r.startDate.year || (currentYear == r.startDate.year && currentMonth < r.startDate.month)) {
        return false;
    }
    
    return true;
}

void addRecurring(RecurringTransaction*& list, int& count, 
                  const std::string& sourceOrCategoryID, 
                  const std::string& walletID, 
                  bool isIncome, 
                  const std::string& note)
{
    RecurringTransaction r;
    r.isIncome = isIncome;
    r.sourceOrCategoryID = sourceOrCategoryID;
    r.walletID = walletID;
    r.note = note;

    r.amount = readDouble("Amount: ");

    cout << "Start date:\n";
    readDate(r.startDate);

    int hasEnd = readInt("Has end date? (1 = yes, 0 = no): ");

    if (hasEnd) {
        cout << "End date:\n";
        readDate(r.endDate);
    } else {
        r.endDate = {31, 12, 9999};
    }
    
    if (r.startDate.month == 1) {
        r.lastAppliedMonth = 12;
        r.lastAppliedYear = r.startDate.year - 1;
    } else {
        r.lastAppliedMonth = r.startDate.month - 1;
        r.lastAppliedYear = r.startDate.year;
    }

    RecurringTransaction* newList = new RecurringTransaction[count + 1];
    for (int i = 0; i < count; i++) newList[i] = list[i];
    newList[count] = r;

    delete[] list;
    list = newList;
    count++;

    cout << "Recurring transaction added!\n";
}

void printRecurring(const RecurringTransaction& r, 
                    Wallet* wallets, int walletCount,
                    IncomeSource* sources, int sourceCount,
                    ExpenseCategory* categories, int categoryCount)
{
    string walletName = findWalletNameByID_Recur(wallets, walletCount, r.walletID);
    cout << (r.isIncome ? "[Income] " : "[Expense] ");
    cout << "Amount: " << r.amount << " | ";
    cout << (r.isIncome ? "Source: " : "Category: ");
    if (r.isIncome) {
        cout << "[" << r.sourceOrCategoryID << "] "
             << findSourceNameByID_Recur(sources, sourceCount, r.sourceOrCategoryID);
    } else {
        cout << "[" << r.sourceOrCategoryID << "] "
             << findCategoryNameByID_Recur(categories, categoryCount, r.sourceOrCategoryID);
    }

    cout << " | Wallet: [" << r.walletID << "] " << walletName << " | ";
    cout << "From ";
    printDate(r.startDate);
    cout << " to ";
    printDate(r.endDate);
    cout << " (Last Applied: " << r.lastAppliedMonth << "/" << r.lastAppliedYear << ")";
    cout << endl;
}

void listRecurring(RecurringTransaction* list, int count, 
                   Wallet* wallets, int walletCount,
                   IncomeSource* sources, int sourceCount,
                   ExpenseCategory* categories, int categoryCount)
{
    if (count == 0) {
        cout << "No recurring transactions yet.\n";
        return;
    }

    cout << "\n=== RECURRING TRANSACTIONS (" << count << ") ===\n";
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". ";
        printRecurring(list[i], wallets, walletCount, sources, sourceCount, categories, categoryCount);
    }
}

void deleteRecurring(RecurringTransaction*& list, int& count) {
    if (count == 0) return;

    int index = readInt("Enter recurring index (1 to " + to_string(count) + "): ") -1;

    if (index < 0 || index >= count) {
        cout << "Invalid index.\n";
        return;
    }

    RecurringTransaction* newList = new RecurringTransaction[count - 1];

    for (int i = 0, j = 0; i < count; i++) {
        if (i != index) {
            newList[j++] = list[i];
        }
    }

    delete[] list;
    list = newList;
    count--;
    cout << "Recurring transaction deleted successfully.\n";
}

void applyRecurringTransactions(
    RecurringTransaction*& list,
    int& recurringCount,
    Wallet* wallets,
    int walletCount,
    IncomeTransaction*& incomes,
    int& incomeCount,
    ExpenseTransaction*& expenses,
    int& expenseCount,
    int currentMonth,
    int currentYear
) {
    for (int i = 0; i < recurringCount; i++) {
        RecurringTransaction& r = list[i];
        if (!shouldApply(r, currentMonth, currentYear)) continue;

        if (r.isIncome) {
            IncomeTransaction t;
            t.sourceID = r.sourceOrCategoryID;
            t.walletID = r.walletID;
            t.amount = r.amount;
            t.note = r.note;
            t.date = {1, currentMonth, currentYear};

            addIncomeTransactionDirect(incomes, incomeCount, wallets, walletCount, t);
        } else {
            ExpenseTransaction t;
            t.sourceID = r.sourceOrCategoryID;
            t.walletID = r.walletID;
            t.amount = r.amount;
            t.note = r.note;

            t.date = {1, currentMonth, currentYear};

            addExpenseTransactionDirect(expenses, expenseCount, wallets, walletCount, t);
        }

        r.lastAppliedMonth = currentMonth;
        r.lastAppliedYear = currentYear;
    }
}

void addIncomeTransactionDirect(
    IncomeTransaction*& list, 
    int& count,
    Wallet* wallets,
    int walletCount,
    const IncomeTransaction& t
) {
    IncomeTransaction* newList = new IncomeTransaction[count + 1];
    for (int i = 0; i < count; i++) newList[i] = list[i];
    newList[count] = t;

    int wIndex = findWalletIndexByID(wallets, walletCount, t.walletID);
    if (wIndex != -1) {
        wallets[wIndex].balance += t.amount;
    }

    delete[] list;
    list = newList;
    count++;
}

void addExpenseTransactionDirect(
    ExpenseTransaction*& list, 
    int& count,
    Wallet* wallets,
    int walletCount,
    const ExpenseTransaction& t
) {
    ExpenseTransaction* newList = new ExpenseTransaction[count + 1];
    for (int i = 0; i < count; i++) newList[i] = list[i];
    newList[count] = t;

    int wIndex = findWalletIndexByID(wallets, walletCount, t.walletID);
    if (wIndex != -1) {
        wallets[wIndex].balance += t.amount;
    }

    delete[] list;
    list = newList;
    count++;
}