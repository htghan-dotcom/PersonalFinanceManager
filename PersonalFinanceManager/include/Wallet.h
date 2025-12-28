#pragma once
#include <string>

using namespace std;

struct Wallet {
	string ID;
	string name;
    long double balance;
};

//prototype
struct IncomeTransaction;
struct ExpenseTransaction;
struct RecurringTransaction;

int findWalletIndexByID(const Wallet* wallets, int walletCount, const string& id);

int askAndFindWalletIndexByID(const Wallet* wallets, int walletCount);

bool isValidWalletID(const string& id);

void addWallet(Wallet* & wallets, int& walletCount, Wallet NewWallet);

void editWallet(Wallet*&wallets, int walletCount, 
				IncomeTransaction* incomes, int incomeCount, 
                ExpenseTransaction* expenses, int expenseCount,
				RecurringTransaction* recurringList, int recurringCount);

void deleteWallet(Wallet*& wallets, int& walletCount);

void updateWalletBalance(Wallet* wallets, int walletCount, string walletID, double amount);
