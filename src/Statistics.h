#pragma once
#include "Utils.h"
#include "Income.h"
#include "Expense.h"
#include "Wallet.h"

class Statistics {
public:
    static void timeBased(
        IncomeTransaction* incomes, int incomeCount,
        ExpenseTransaction* expenses, int expenseCount,
        Date from, Date to
    );

    static void walletBreakDown(
        Wallet* wallet, int WalletCount,
        IncomeTransaction* incomes, int incomeCount,
        ExpenseTransaction* expenses, int expenseCount,
        Date from, Date to
    );

    static void annualOverview(
        IncomeTransaction* incomes, int incomeCount,
        ExpenseTransaction* expenses, int expenseCount,
        int year
    );


};