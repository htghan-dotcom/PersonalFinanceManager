
#include <iostream>
#include <string>
#include "Wallet.h"

using namespace std;

int findWalletIndexByID(const Wallet* wallets, int walletCount, const string& id) {
    for (int i = 0; i < walletCount; ++i) {
        if (wallets[i].ID == id) {
            return i;
        }
    }
    return -1;
}

int askAndFindWalletIndexByID(const Wallet* wallets, int walletCount) {
    cout << "\n---FIND WALLET BY ID---\n";
    cout << "Please enter the wallet ID: ";
    string id;
    cin >> id;
    cout << endl;
    return findWalletIndexByID(wallets, walletCount, id);
}

bool isValidWalletID(const string& id) {
    if (id.size() != 5) return false;
    if (id[0] != 'W') return false;
    for (int i = 1; i < 5; ++i) {
        if (!isdigit((id[i]))) return false;
    }
    return true;
}


void addWallet(Wallet*& wallets, int& walletCount) {
    cout << "\n---ADD WALLET---\n";
    Wallet newWallet;

    cout << "Please enter the new wallet information:\n";

    cout << "Enter ID(the format should be Iabcd with a,b,c,d is a number): ";
    cin >> newWallet.ID;
    if (!isValidWalletID(newWallet.ID)) {
        cout << "ERROR: Invalid ID format. Required: 'W' followed by 4 digits (e.g., W0001). Please try again.\n";
        return;
    }

    cout << "Enter wallet name: ";
    getline(cin >> std::ws, newWallet.name);

    cout << "Enter wallet balance: ";
    cin >> newWallet.balance;

    if (findWalletIndexByID(wallets, walletCount, newWallet.ID) != -1) {
        cout << "ERROR: ID already exists. Cannot add.\n";
        return;
    }

    Wallet* newArr = new Wallet[walletCount + 1];

    for (int i = 0; i < walletCount; ++i) {
        newArr[i] = wallets[i];
    }

    newArr[walletCount] = newWallet;

    delete[] wallets;
    wallets = newArr;
    ++walletCount;

    cout << "Wallet added successfully!\n";
}

void editWallet(Wallet* wallets, int walletCount) {
    cout << "\n---EDIT WALLET---\n";
    cout << "Please enter the wallet ID to edit: ";
    string idToEdit;
    cin >> idToEdit;

    int index = findWalletIndexByID(wallets, walletCount, idToEdit);
    if (index == -1) {
        cout << "Wallet not found for editing!\n";
        return;
    }

    cout << "Please enter the field to edit (ID/name/balance): ";
    string field;
    cin >> field;

    if (field == "ID") {
        cout << "Enter new ID: ";
        string newID;
        cin >> newID;

        if (findWalletIndexByID(wallets, walletCount, newID) != -1) {
            cout << "ERROR: New ID already exists. Cannot update.\n";
            return;
        }
        wallets[index].ID = newID;
    }
    else if (field == "name") {
        cout << "Enter new wallet name: ";
        getline(cin, wallets[index].name);
    }
    else if (field == "balance") {
        cout << "Enter new balance: ";
        double newBalance;
        cin >> newBalance;
        wallets[index].balance = newBalance;
    }
    else {
        cout << "Invalid field! Supported: ID / name / balance\n";
        return;
    }

    cout << "\n---UPDATE SUCCESSFUL!---\n";
}

void deleteWallet(Wallet*& wallets, int& walletCount) {
    cout << "\n---DELETE WALLET---\n";
    cout << "Please enter the wallet ID to delete: ";
    string idToDelete;
    cin >> idToDelete;

    int index = findWalletIndexByID(wallets, walletCount, idToDelete);
    if (index == -1) {
        cout << "Wallet not found for deletion!\n";
        return;
    }

    if (walletCount - 1 == 0) {
        delete[] wallets;
        wallets = nullptr;
        walletCount = 0;
        cout << "Deleted wallet ID[" << idToDelete << "] successfully.\n";
        return;
    }

    Wallet* newArr = new Wallet[walletCount - 1];

    for (int i = 0, j = 0; i < walletCount; ++i) {
        if (i == index) continue;
        newArr[j++] = wallets[i];
    }

    delete[] wallets;
    wallets = newArr;
    --walletCount;

    cout << "Deleted wallet ID[" << idToDelete << "] successfully.\n";
}

void updateWalletBalance(Wallet* wallets, int walletCount, string walletID, double amount) {
    int index = findWalletIndexByID(wallets, walletCount, walletID);

    if (index != -1) {
        wallets[index].balance += amount;
        cout << "Updated balance for wallet ID[" << walletID << "]. New balance: " << wallets[index].balance << "\n";
    }
    else {
        cout << "ERROR: Wallet ID " << walletID << " not found.\n";
    }}