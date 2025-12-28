#pragma once
#include <iostream>
#include <string>
#include "Utils.h"
#include "Wallet.h"

using namespace std;

struct ExpenseCategory
{
    string id;
    string name;
};

struct ExpenseTransaction
{
    Date date;
    string sourceID;
    string walletID;
    double amount;
    string note;
};

int findExpenseCategoryIndexByID(ExpenseCategory *cate, int count, string id);
int askAndFindExpenseCategoryIndexByID(ExpenseCategory *cate, int count);
bool isValidExpenseID(const string &id);

int countTransactionsByExpenseCategory(ExpenseTransaction *trans, int transCount, const string &sourceID);

void addExpenseCategory(ExpenseCategory *&cate, int &count);
void editExpenseCategory(ExpenseCategory *cate, int count,
                         ExpenseTransaction *transactions, int transCount);
void deleteExpenseCategory(ExpenseCategory *&cate, int &count,ExpenseTransaction*& transactions,int transcount);

void addExpenseTransaction(ExpenseTransaction *&trans, int &transCount, Wallet *wallets, int walletCount, ExpenseCategory *sources, int CategoryCount);
void printExpenseTransaction(ExpenseTransaction t);
void filterExpenseByDateRange(ExpenseTransaction* expenseTransactions, int expenseTransactionsCount, Date from, Date to);
void filterExpenseByWallet(ExpenseTransaction* expenseTransactions, int expenseTransactionsCount, const string &walletID, Date from, Date to);
