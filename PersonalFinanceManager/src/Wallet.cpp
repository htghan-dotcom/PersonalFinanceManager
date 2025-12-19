
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


void addWallet(Wallet*& wallets, int& walletCount, Wallet newWallet) {
    cout << "\n---ADD WALLET---\n";

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



void editWallet(Wallet*& wallets, int walletCount) {
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
    for (char& c : field) c = static_cast<char>(tolower(c));

    if (field == "id") {
        while (true) {
            cout << "Enter new ID (or type CANCEL to abort): ";
            string newID;
            cin >> newID;

            if (newID == "CANCEL") {
                cout << "Update canceled.\n";
                return;
            }
            if (newID.empty()) {
                cout << "ERROR: ID cannot be empty.\n";
                continue;
            }
            if (findWalletIndexByID(wallets, walletCount, newID) != -1) {
                cout << "ERROR: New ID already exists. Try another.\n";
                continue;
            }

            wallets[index].ID = newID;
            cout << "\n---UPDATE SUCCESSFUL!---\n";
            return;
        }
    }
    else if (field == "name") {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while (true) {
            cout << "Enter new wallet name (press ENTER to cancel): ";
            string newName;

    
            getline(cin >> std::ws, newName);

       
            if (newName.empty()) {
                cout << "Update canceled.\n";
                return;
            }

        
            bool allSpaces = true;
            for (unsigned char ch : newName) {
                if (!isspace(ch)) { allSpaces = false; break; }
            }
            if (allSpaces) {
                cout << "ERROR: Name cannot be only spaces. Please re-enter.\n";
                continue;
            }

            wallets[index].name = newName;
            cout << "\n---UPDATE SUCCESSFUL!---\n";
            return;
        }
    }
    else if (field == "balance") {
       
        while (true) {
            cout << "Enter new balance (or type - to cancel): ";
            string token;
            cin >> token;

            if (token == "-") {
                cout << "Update canceled.\n";
                return;
            }

          
            try {
                size_t pos = 0;
                double value = stod(token, &pos);
                if (pos != token.size()) {
                    cout << "ERROR: Invalid number format.\n";
                    continue;
                }
                if (value < 0) {
                    cout << "ERROR: Balance cannot be negative.\n";
                    continue;
                }

                wallets[index].balance = value;
                cout << "\n---UPDATE SUCCESSFUL!---\n";
                return;
            } catch (...) {
                cout << "ERROR: Invalid number format.\n";
                continue;
            }
        }
    }
    else {
        cout << "Invalid field! Supported: ID / name / balance\n";
        return;
    }
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