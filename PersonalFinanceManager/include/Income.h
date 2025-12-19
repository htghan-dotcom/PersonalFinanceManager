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
void addIncomeSource(IncomeSource*& sources, int& Incomecount);
void editIncomeSource(IncomeSource* sources, int count);
void deleteIncomeSource(IncomeSource*& sources, int& count);


void addIncomeTransaction(IncomeTransaction*& trans, int& transCount, Wallet* wallets, int walletCount, IncomeSource* sources, int sourceCount);
void printIncomeTransaction(IncomeTransaction t);
void filterIncomeByDateRange(Date from, Date to);
void filterIncomeByWallet(int walletID, Date from, Date to);
