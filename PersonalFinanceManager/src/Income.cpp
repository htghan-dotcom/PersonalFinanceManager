#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

#include "Income.h"

using namespace std;

static IncomeTransaction* g_incomeTrans = nullptr;
static int g_incomeTransCount = 0;

int findIncomeSourceIndexByID(IncomeSource* sources, int IncomeCount, string id) {
    for (int i = 0; i < IncomeCount; i++) {
        if (sources[i].ID == id) {
            return i;
        }
    }
    return -1;
}

int askAndFindIncomeSourceIndexByID(IncomeSource* sources, int IncomeCount) {
    cout << "\n---FIND INCOME SOURCE BY ID---\n";
    cout << "Please enter the ID of the income source: ";
    string id;
    cin >> id;
    cout << endl;
    return findIncomeSourceIndexByID(sources, IncomeCount, id);
}


bool isValidIncomeID(const string& id) {
    if (id.size() != 5) return false;
    if (id[0] != 'I') return false;
    for (int i = 1; i < 5; ++i) {
        if (!isdigit((id[i]))) return false;
    }
    return true;
}


void addIncomeSource(IncomeSource*& sources, int& IncomeCount) {
    cout << "\n---ADD INCOME SOURCE---\n";
    IncomeSource newSource;

    cout << "PLEASE ENTER THE DETAILS OF THE NEW INCOME SOURCE\n";

    cout << "Enter ID (format Iabcd with a,b,c,d is a number): ";
    cin >> newSource.ID;

    if (!isValidIncomeID(newSource.ID)) {
        cout << "ERROR: Invalid ID format.\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (findIncomeSourceIndexByID(sources, IncomeCount, newSource.ID) != -1) {
        cout << "ERROR: ID already exists.\n";
        return;
    }

    cout << "Enter name: ";
    getline(cin >> ws, newSource.name);  

    IncomeSource* newArr = new IncomeSource[IncomeCount + 1];

    for (int i = 0; i < IncomeCount; ++i) {
        newArr[i] = sources[i];
    }

    newArr[IncomeCount] = newSource;

    delete[] sources;
    sources = newArr;
    ++IncomeCount;

    cout << "Income source added successfully!\n";
}

void editIncomeSource(IncomeSource* sources, int count) {
    cout << "\n---EDIT INCOME SOURCE---\n";
    string ID;
    cout << "Enter the ID of the income source to edit: ";
    cin >> ID;
    int index = -1;
    index = findIncomeSourceIndexByID(sources, count, ID);
    if (index == -1) {
        cout << "Cannot find the income source to edit.\n";
        return;
    }
    string field;
    cout << "Please enter the field to edit (ID or name): ";
    cin >> field;
    if (field == "ID") {
        cout << "Enter new ID: ";
        string newID;
        cin >> newID;

        if (findIncomeSourceIndexByID(sources, count, newID) != -1) {
            cout << "ERROR: New ID already exists. Cannot update.\n";
            return;
        }
        sources[index].ID = newID;
    }
    else if (field == "name") {
        cout << "Enter new name: ";
        getline(cin, sources[index].name);
    }
    else {
        cout << "Invalid field.\n";
        return;
    }
    cout << "\n---UPDATE SUCCESSFUL---\n";
}

void deleteIncomeSource(IncomeSource*& sources, int& count) {
    cout << "\n---DELETE INCOME SOURCE---\n";
    string IDToDelete;
    cout << "Enter the ID of the income source to delete: ";
    cin >> IDToDelete;
    cout << endl;

    int index = -1;
    index = findIncomeSourceIndexByID(sources, count, IDToDelete);
    if (index == -1) {
        cout << "Income source not found for deletion.\n";
        return;
    }
    if (count == 1) {
        delete sources;
        sources = nullptr;
        count = 0;
        cout << "Deleted income source with ID(" << IDToDelete << ") successfully.\n";
        return;
    }
    IncomeSource* newArr = new IncomeSource[count - 1];

    for (int i = 0, j = 0; i < count; ++i) {
        if (i == index) continue;
        newArr[j++] = sources[i];
    }

    delete[] sources;
    sources = newArr;
    --count;

    cout << "Deleted income source with ID[" << IDToDelete << "] successfully.\n";
}

void addIncomeTransaction(IncomeTransaction*& trans, int& transCount, Wallet* wallets, int walletCount, IncomeSource* sources, int sourceCount) {
    cout << "\n---ADD INCOME TRANSACTION---\n";
    IncomeTransaction t;

    readDate(t.date);

    cout << "Enter amount (+): ";
    cin >> t.amount;
    if (t.amount <= 0) {
        cout << "ERROR: Amount must be > 0.\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;  
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Wallet ID: ";
    getline(cin, t.walletID);
    int wIdx = findWalletIndexByID(wallets, walletCount, t.walletID);
    if (wIdx == -1) {
        cout << "ERROR: Wallet ID[" << t.walletID << "] not found.\n";
        return;
    }

    cout << "Enter Income Source ID: ";
    getline(cin, t.sourceID);
    int sIdx = findIncomeSourceIndexByID(sources, sourceCount, t.sourceID);
    if (sIdx == -1) {
        cout << "ERROR: Income Source ID[" << t.sourceID << "] not found.\n";
        return;
    }

    cout << "Enter note (optional): ";
    getline(cin, t.note);

    IncomeTransaction* newArr = new IncomeTransaction[transCount + 1];
    for (int i = 0; i < transCount; ++i) newArr[i] = trans[i];
    newArr[transCount] = t;

    delete[] trans;
    trans = newArr;
    ++transCount;

    wallets[wIdx].balance += t.amount;

    g_incomeTrans = trans;
    g_incomeTransCount = transCount;

    cout << "Income transaction added and wallet [" << wallets[wIdx].ID << "] balance updated successfully.\n";
}

void printIncomeTransaction(IncomeTransaction t) {
    cout << "----------------------------------------\n";
    cout << "Date           : "; printDate(t.date); cout << "\n";
    cout << fixed << setprecision(2);
    cout << "Amount         : +" << t.amount << "\n";
    cout << "Wallet         : " << t.walletID << "\n";
    cout << "Source         : " << t.sourceID << "\n";
    if (!t.note.empty()) cout << "Note           : " << t.note << "\n";
    cout << "----------------------------------------\n";
}

void filterIncomeByDateRange(Date from, Date to) {
    cout << "\n---FILTER INCOME TRANSACTIONS BY DATE RANGE---\n";
    if (g_incomeTrans == nullptr || g_incomeTransCount == 0) {
        cout << "No transactions to filter.\n";
        return;
    }

    if (compareDate(from, to) > 0) std::swap(from, to);

    int found = 0;
    for (int i = 0; i < g_incomeTransCount; ++i) {
        if (isDateInRange(g_incomeTrans[i].date, from, to)) {
            printIncomeTransaction(g_incomeTrans[i]);
            ++found;
        }
    }

    if (found == 0) {
        cout << "No transactions found in the specified date range.\n";
    }
}

void filterIncomeByWallet(string walletID, Date from, Date to) {
    cout << "\n---FILTER INCOME TRANSACTIONS BY WALLET---\n";
    if (g_incomeTrans == nullptr || g_incomeTransCount == 0) {
        cout << "No transactions to filter.\n";
        return;
    }

    if (compareDate(from, to) > 0) std::swap(from, to);

    int found = 0;
    for (int i = 0; i < g_incomeTransCount; ++i) {
        if (g_incomeTrans[i].walletID == walletID &&
            isDateInRange(g_incomeTrans[i].date, from, to)) {
            printIncomeTransaction(g_incomeTrans[i]);
            ++found;
        }
    }

    if (found == 0) {
        cout << "No transactions for Wallet ID[" << walletID << "] in the specified date range.\n";
    }
}
