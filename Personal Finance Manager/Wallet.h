#pragma once

struct Wallet {
	string ID;
	string name;
	double balance;
	Wallet* next;
};

void addWallet(Wallet*& arr, int& walletCount,  Wallet& a);
void editWallet(Wallet* arr, int walletCount, int walletID, string newName);
void deleteWallet(Wallet*& arr, int& walletCount, int walletID);
int findWalletIndexByID(Wallet* arr, int walletCount, int id);
void updateWalletBalance(Wallet* arr, int walletCount, int walletID, double amount);