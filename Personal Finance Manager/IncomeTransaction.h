#pragma once
#include <iostream>
#include <string>
#include "Utils.h"
#include "IncomeSource.h"

using namespace std;

struct IncomeTransaction {
    Date date;
    int sourceID;
    int walletID;
    double amount;
    string description;
};


void addIncomeTransaction(IncomeTransaction*& trans, int& transCount, Wallet* wallets, int walletCount, IncomeSource* sources, int sourceCount);


void editIncomeSource();


void deleteIncomeSource();


int findIncomeSourceIndexByID(int id);



