#pragma once
#include <string>

#include "Utils.h"
#include "Wallet.h"
#include "Income.h"
#include "Expense.h"

struct RecurringTransaction {
    bool isIncome;
    std::string sourceOrCategoryID;
    std::string walletID;
    double amount;
    std::string note;

    Date startDate;
    Date endDate;

    int lastAppliedMonth;
    int lastAppliedYear;
};

void addRecurring(RecurringTransaction*& list, int& count, 
                  const std::string& sourceOrCategoryID, 
                  const std::string& walletID, 
                  bool isIncome, 
                  const std::string& note);

void printRecurring(const RecurringTransaction& r, 
                    Wallet* wallets, int walletCount,
                    IncomeSource* sources, int sourceCount,
                    ExpenseCategory* categories, int categoryCount);

void listRecurring(RecurringTransaction* list, int count,
                   Wallet* wallets, int walletCount,
                   IncomeSource* sources, int sourceCount,
                   ExpenseCategory* categories, int categoryCount);

void deleteRecurring(RecurringTransaction*& list, int& count);

bool shouldApply(const RecurringTransaction& r, int currentMonth, int currentYear);

void applyRecurringTransactions(
    RecurringTransaction*& list,
    int& recurringCount,
    Wallet* wallets,
    int walletCount,
    IncomeTransaction*& incomes,
    int& incomeCount,
    ExpenseTransaction*& expenses,
    int& expenseCount,
    int currentMonth,
    int currentYear
);