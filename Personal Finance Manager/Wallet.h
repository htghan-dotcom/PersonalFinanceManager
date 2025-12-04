#pragma once
#include <string>
struct Wallet {
	string ID;
	string name;
	double balance;
	
};

int findWalletIndexByID(Wallet* wallets, int walletCount, string id);
void addWallet(Wallet* wallets, int walletCount,Wallet NewWallet);
void editWallet(Wallet* wallets, int walletCount, string edit);
void deleteWallet(Wallet** wallets, int* walletCount);
void updateWalletBalance(Wallet* wallets, int walletCount, int walletID, double amount);