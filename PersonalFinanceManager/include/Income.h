#pragma once
#include <iostream>
#include <string>
#include "Utils.h"
#include "Wallet.h"

using namespace std;

struct IncomeSource {
    string ID;
    string name;
};

struct IncomeTransaction {
    Date date;
    string sourceID;
    string walletID;
    double amount;
    string note;
};


int findIncomeSourceIndexByID(IncomeSource* sources, int count, string id);
int askAndFindIncomeSourceIndexByID(IncomeSource* sources, int count);
bool isValidIncomeID(const string& id);

int countTransactionsByIncomeSource(IncomeTransaction* trans, int transCount, const string& sourceID);
void addIncomeSource(IncomeSource*& sources, int& Incomecount);
void editIncomeSource(IncomeSource*& sources, int count, IncomeTransaction*& transactions, int transCount);
void deleteIncomeSource(IncomeSource*& sources, int& count ,IncomeTransaction* transactions,int transcount);

void addIncomeTransaction(IncomeTransaction*& trans, int& transCount, Wallet* wallets, int walletCount, IncomeSource* sources, int sourceCount);
void printIncomeTransaction(IncomeTransaction t);
void filterIncomeByDateRange(IncomeTransaction* incomeTransactions, int incomeTransactionCount, Date from, Date to);
void filterIncomeByWallet(IncomeTransaction* incomeTransactions, int incomeTransactionCount, const string& walletID, Date from, Date to);
