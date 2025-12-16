#pragma once
#include <string>

#include "Utils.h"
#include "Wallet.h"
#include "Income.h"
#include "Expense.h"
#include "RecurringTransaction.h"

class DataManager {
public:
    void loadAll();
    void saveAll();

    void addWalletUI ();
    void editWalletUI();
    void deleteWalletUI();
    void showWallets();

    void addIncomeSourceUI();
    void editIncomeSourceUI();
    void deleteIncomeSourceUI();
    void showIncomeSources();

    void addExpenseCategoryUI();
    void editExpenseCategoryUI();
    void deleteExpenseCategoryUI();
    void showExpenseCategories();

    void addIncomeTransactionUI();
    void addExpenseTransactionUI();

    Wallet* wallets = nullptr;
    int walletCount = 0;

    IncomeSource* incomeSources = nullptr;
    int incomeSourceCount = 0;

    ExpenseCategory* expenseCategories = nullptr;
    int expenseCategoryCount = 0;

    IncomeTransaction* incomeTransactions = nullptr;
    int incomeTransactionCount = 0;

    ExpenseTransaction* expenseTransactions = nullptr;
    int expenseTransactionCount = 0;

    RecurringTransaction* recurringList = nullptr;
    int recurringCount = 0;

    void applyRecurringTransactions();

private:
    void loadWallets();
    void saveWallets();

    void loadIncomeSources();
    void saveIncomeSources();

    void loadExpenseCategories();
    void saveExpenseCategories();

    void loadIncomeTransactions();
    void saveIncomeTransactions();

    void loadExpenseTransactions();
    void saveExpenseTransactions();

    void loadRecurring();
    void saveRecurring();
};
