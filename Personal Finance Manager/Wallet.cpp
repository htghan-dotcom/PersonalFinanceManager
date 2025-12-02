#include <iostream>
#include "Wallet.h"

using namespace std;
Wallet* wallets = nullptr;
int walletCount = 0;

void addWallet(Wallet*& arr, int& walletCount,  Wallet& a) {
	
	walletCount++;
	arr-> = a;
	wallets[walletCount - 1] = a;
	cout << "Enter a new wallet(ID,name,balance):" << endl;
	cin >> a.ID;
	cin >> a.name;
	cin >> a.balance;
	
}

void editWallet(Wallet* arr, int walletCount, int walletID, const char* newName);
void deleteWallet(Wallet*& arr, int& walletCount, int walletID);
int findWalletIndexByID(Wallet* arr, int walletCount, int id);
void updateWalletBalance(Wallet* arr, int walletCount, int walletID, double amount);