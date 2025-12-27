#pragma once
#include <iostream>
#include <string>
#include "Utils.h"
#include "Wallet.h"

using namespace std;

struct ExpenseCategory {
	string id;
	string name;
};

struct ExpenseTransaction {
    Date date;
    string sourceID;
    string walletID;
    double amount;
    string note;
};

int findExpenseCategoryIndexByID(ExpenseCategory* cate, int count, string id);
int askAndFindExpenseCategoryIndexByID(ExpenseCategory* cate, int count);
bool isValidExpenseID(const string& id);
void addExpenseCategory(ExpenseCategory*& cate, int& count);
void editExpenseCategory(ExpenseCategory* cate, int count);
void deleteExpenseCategory(ExpenseCategory*& cate, int& count);


void addExpenseTransaction(ExpenseTransaction*& trans, int& transCount, Wallet* wallets, int walletCount, ExpenseCategory* sources, int CategoryCount);
void printExpenseTransaction(ExpenseTransaction t);
void filterExpenseByDateRange(Date from, Date to);
void filterExpenseByWallet(const string& walletID, Date from, Date to);
