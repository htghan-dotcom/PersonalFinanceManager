#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

#include "Expense.h"

using namespace std;

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

int countTransactionsByExpenseCategory(ExpenseTransaction* trans, int transCount, const string& sourceID) {
    int cnt = 0;
    for (int i = 0; i < transCount; ++i) {
        if (trans[i].sourceID == sourceID) ++cnt;
    }
    return cnt;
}

void addExpenseCategory(ExpenseCategory*& cate, int& count) {
    cout << "\n--- ADD EXPENSE CATEGORY ---\n";
    ExpenseCategory newCate;

    cout << "PLEASE ENTER THE DETAILS OF THE NEW EXPENSE CATEGORY\n";

    cout << "Enter ID (format Eabcd with a,b,c,d is a number): ";
    cin >> newCate.id;

    if (!isValidExpenseID(newCate.id)) {
        cout << "ERROR: Invalid ID format.\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (findExpenseCategoryIndexByID(cate, count, newCate.id) != -1) {
        cout << "ERROR: ID already exists.\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Enter category name: ";
    getline(cin >> std::ws, newCate.name);

    ExpenseCategory *newArr = new ExpenseCategory[count + 1];
    for (int i = 0; i < count; ++i)
        newArr[i] = cate[i];
    newArr[count] = newCate;

    delete[] cate;
    cate = newArr;
    ++count;

    cout << "ExpenseCategory added successfully.\n";
}

void editExpenseCategory(ExpenseCategory *cate, int count,
                         ExpenseTransaction *transactions, int transCount)
{
    int idx = askAndFindExpenseSourceIndexByID(cate, count);
    if (idx == -1)
        return;

    cout << "Current name: " << cate[idx].name << "\nEnter new name: ";
    string name;
    getline(cin, name);
    if (!name.empty())
        cate[idx].name = name;

    cout << "ExpenseCategory updated successfully.\n";
}

void deleteExpenseCategory(ExpenseCategory *&cate, int &count, ExpenseTransaction*& transactions,int transcount)
{

   cout << "\n---DELETE EXPENSE CATEGORY---\n";
    string IDToDelete;
    cout << "Enter the ID of the expense category to delete: ";
    cin >> IDToDelete;
    cout << endl;
    int index = -1;
    index = findExpenseCategoryIndexByID(cate, count, IDToDelete);
    if (index == -1) {
        cout << "Expense Category not found for deletion.\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    int related = countTransactionsByExpenseCategory(transactions, transcount, IDToDelete);
    if (related > 0) {
        cout << "Cannot delete: there are " << related
             << " income transactions referencing this source.\n"
             << "Please reassign or delete those transactions first.\n";
        return;
    }

    ExpenseCategory *newArr = new ExpenseCategory[count - 1];
    for (int i = 0, j = 0; i < count; ++i)
    {
        if (i == index)
            continue;
        newArr[j++] = cate[i];
    }
    delete[] cate;
    cate = newArr;
    --count;

    cout << "ExpenseCategory deleted successfully.\n";
}

void addExpenseTransaction(ExpenseTransaction *&trans, int &transCount,
                           Wallet *wallets, int walletCount,
                           ExpenseCategory *sources, int CategoryCount)
{
    ExpenseTransaction t;

    cout << "Enter date (dd mm yyyy): ";
    cin >> t.date.day >> t.date.month >> t.date.year;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (!validDate(t.date))
    {
        cout << "Invalid date. Cancel.\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Enter sourceID (Expense category ID): ";
    getline(cin, t.sourceID);
    if (t.sourceID.empty())
    {
        cout << "Empty sourceID. Cancel.\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (findExpenseCategoryIndexByID(sources, CategoryCount, t.sourceID) == -1)
    {
        cout << "ExpenseCategory ID = " << t.sourceID << " not found. Cancel.\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Enter walletID (string/integer id): ";
    string walletID;
    getline(cin, walletID);
    while (walletID.empty())
    {

        getline(cin, walletID);
    }
    int widx = findWalletIndexByID(wallets, walletCount, walletID);
    if (widx == -1)
    {
        cout << "Wallet ID = " << walletID << " not found. Cancel.\n";
        return;
    }
    t.walletID = walletID;

    cout << "Enter amount (>=0): ";
    cin >> t.amount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (t.amount < 0)
    {
        cout << "Invalid amount. Cancel.\n";
        return;
    }

    if (wallets[widx].balance < t.amount)
    {
        cout << "Insufficient wallet balance. Current balance = "
             << wallets[widx].balance << ", amount = " << t.amount << ". Cancel.\n";
        return;
    }

    cout << "Enter note: ";
    getline(cin, t.note);

    ExpenseTransaction *newArr = new ExpenseTransaction[transCount + 1];
    for (int i = 0; i < transCount; ++i)
        newArr[i] = trans[i];
    newArr[transCount] = t;

    delete[] trans;
    trans = newArr;
    ++transCount;

    wallets[widx].balance -= t.amount;

    cout << "ExpenseTransaction added successfully. Wallet " << wallets[widx].ID
         << " new balance = " << wallets[widx].balance << "\n";
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

void filterExpenseByDateRange(ExpenseTransaction* expenseTransactions, int expenseTransactionsCount,
                              Date from, Date to) {
    if (expenseTransactions == nullptr || expenseTransactionsCount== 0) {
        cout << "No ExpenseTransaction data (gExpTrans is empty).\n";
        return;
    }
    cout << "=== Expenses from "
         << from.day << "/" << from.month << "/" << from.year << " to "
         << to.day << "/" << to.month << "/" << to.year << " ===\n";

    bool found = false;
    for (int i = 0; i < expenseTransactionsCount; ++i) {
        if (isDateInRange(expenseTransactions[i].date, from, to)) {
            printExpenseTransaction(expenseTransactions[i]);
            found = true;
        }
    }
    if (!found) cout << "No transactions found in the given date range.\n";
}

void filterExpenseByWallet(ExpenseTransaction* expenseTransactions, int expenseTransactionsCount,
                           const string& walletID, Date from, Date to) {
    cout << "\n---FILTER EXPENSE TRANSACTIONS BY WALLET---\n";
    if (expenseTransactions == nullptr || expenseTransactionsCount == 0) {
        cout << "No ExpenseTransaction data (gExpTrans is empty).\n";
        return;
    }

    cout << "=== Expenses for walletID=" << walletID << " from "
         << from.day << "/" << from.month << "/" << from.year << " to "
         << to.day << "/" << to.month << "/" << to.year << " ===\n";

    bool found = false;
    for (int i = 0; i < expenseTransactionsCount; ++i) {
        if (expenseTransactions[i].walletID == walletID &&
            isDateInRange(expenseTransactions[i].date, from, to)) {
            printExpenseTransaction(expenseTransactions[i]);
            found = true;
        }
    }
    if (!found) cout << "No matching transactions found.\n";
}

