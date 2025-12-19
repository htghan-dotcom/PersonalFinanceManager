#pragma once
#include <string>


using namespace std;

struct Wallet {
	string ID;
	string name;
    long double balance;
};

int findWalletIndexByID(const Wallet* wallets, int walletCount, const string& id);
int askAndFindWalletIndexByID(const Wallet* wallets, int walletCount);
bool isValidWalletID(const string& id);
void addWallet(Wallet* & wallets, int& walletCount, Wallet NewWallet);
void editWallet(Wallet*&wallets, int walletCount);
void deleteWallet(Wallet*& wallets, int& walletCount);
void updateWalletBalance(Wallet* wallets, int walletCount, string walletID, double amount);
