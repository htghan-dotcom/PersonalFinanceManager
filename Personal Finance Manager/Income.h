#pragma once
#include <iostream>
#include <string>
#include "Utils.h"
#include "Wallet.h"

using namespace std;

struct IncomeSource {
    string id;
    string name;
};

struct IncomeTransaction {
    Date date;
    int sourceID;
    int walletID;
    double amount;
    string description;
};
    

int findIncomeSourceIndexByID(IncomeSource* sources, int count, string id);
void addIncomeSource(IncomeSource*& sources, int& count);
void editIncomeSource(IncomeSource* sources, int count);
void deleteIncomeSource(IncomeSource*& sources, int& count);


void addIncomeTransaction(IncomeTransaction*& trans, int& transCount, Wallet* wallets, int walletCount, IncomeSource* sources, int sourceCount);
void printIncomeTransaction(IncomeTransaction t);
void filterIncomeByDateRange(Date from, Date to);
void filterIncomeByWallet(int walletID, Date from, Date to);
