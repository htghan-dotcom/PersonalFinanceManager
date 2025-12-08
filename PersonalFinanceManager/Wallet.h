#pragma once
#include <string>

struct Wallet {
	string ID;
	string name;
	double balance;

};

int findWalletIndexByID(const Wallet* wallets, int walletCount, const string& id);
int askAndFindWalletIndexByID(const Wallet* wallets, int walletCount);
void addWallet(Wallet* wallets, int walletCount, Wallet NewWallet);
void editWallet(Wallet* wallets, int walletCount);
void deleteWallet(Wallet** wallets, int* walletCount);
void updateWalletBalance(Wallet* wallets, int walletCount, int walletID, double amount);