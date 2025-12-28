#include <iostream>
#include <iomanip>

#include "Statistics.h"
#include "Utils.h"

using namespace std;

void Statistics::timeBased(
    IncomeTransaction* incomes, int incomeCount,
    ExpenseTransaction* expenses, int expenseCount,
    Date from, Date to
) {
    double totalIncome = 0;
    double totalExpense = 0;

    for (int i = 0; i < incomeCount; i++) {
        if (isDateInRange(incomes[i].date, from, to)) {
            totalIncome += incomes[i].amount;
        }
    }

    for (int i = 0; i < expenseCount; i++) {
        if (isDateInRange(expenses[i].date, from, to)) {
            totalExpense += expenses[i].amount;
        }
    }

    cout << "\n=== STATISTICS: " << from.day << "/" << from.month << "/" << from.year 
        << " TO " << to.day << "/" << to.month << "/" << to.year << " ===\n";
    cout << "\nTotal Income: " << totalIncome << endl;
    cout << "Total Expense: " << totalExpense << endl;
    cout << "Net Balance: " << totalIncome - totalExpense << endl;
}

void Statistics::walletBreakdown(
    const std::string& walletID,
    IncomeTransaction* incomes, int incomeCount,
    ExpenseTransaction* expenses, int expenseCount,
    Date from, Date to    
) {
    double totalIncome = 0;
    double totalExpense = 0;

    for (int i = 0; i < incomeCount; ++i) {
        if (incomes[i].walletID == walletID && 
            isDateInRange(incomes[i].date, from, to)) {
            totalIncome += incomes[i].amount;
        }
    }

    for (int i = 0; i < expenseCount; ++i) {
        if (expenses[i].walletID == walletID && 
            isDateInRange(expenses[i].date, from, to)) {
            totalExpense += expenses[i].amount;
        }
    }

    cout << "\n===========================================";
    cout << "\n   OVERVIEW FOR WALLET: " << walletID;
    cout << "\n   Period: " << from.day << "/" << from.month << " to " << to.day << "/" << to.month;
    cout << "\n===========================================";
    cout << "\nTotal Income: " << totalIncome;
    cout << "\nTotal Expense: " << totalExpense; 
    cout << "\nNet Impact: " << totalIncome - totalExpense;
    cout << "\n-------------------------------------------" << endl;

    cout << "\nDETAILED TRANSACTION HISTORY:" << endl;
    
    cout << left << setw(10) << "Date" << setw(18) << "Category/Source" << setw(12) << "Amount" << "Note" << endl;
    cout << string(55, '-') << endl;

    filterIncomeByWallet(walletID, from, to);
    filterExpenseByWallet(walletID, from, to);
}

void Statistics::annualOverview(
    IncomeTransaction* incomes, int incomeCount,
    ExpenseTransaction* expenses, int expenseCount,
    int* year, int yearNumber
) {
    for (int y = 0; y < yearNumber; y++) {
        double totalIncome = 0;
        double totalExpense = 0;

        for (int i = 0; i < incomeCount; i++) {
            if (incomes[i].date.year == year[y]) {
                totalIncome += incomes[i].amount;
            }
        }

        for (int i = 0; i < expenseCount; i++) {
            if (expenses[i].date.year == year[y]) {
                totalExpense += expenses[i].amount;
            }
        }
        cout << "\n=== ANNUAL OVERVIEW " << year[y] << " ===\n";
        cout << "Income: " << totalIncome << endl;
        cout << "Expense: " << totalExpense << endl;
        cout << "Net Balance: " << totalIncome - totalExpense << endl;
    } 
}

void Statistics::annualSourceCategoryBreakdown(
    IncomeSource* incomeSources, int incomeSourceCount,
    IncomeTransaction* incomeTransactions, int incomeTransactionCount,
    ExpenseCategory* expenseCategories, int expenseCategoryCount,
    ExpenseTransaction* expenseTransactions, int expenseTransactionCount,
    int* year, int yearNumber
) {
    for (int y = 0; y < yearNumber; y++) {
        cout << "\n=== ANNUAL BREAKDOWN " << year[y] << " ===\n";

        cout << "\n-- Income Breakdown --\n";
        double totalIncome = 0;
        double* incomeTotals = new double[incomeSourceCount]();

        for (int i = 0; i < incomeTransactionCount; i++) {
            if (incomeTransactions[i].date.year == year[y]) {
                int sourceIndex = findIncomeSourceIndexByID(incomeSources, incomeSourceCount, incomeTransactions[i].sourceID);
                if (sourceIndex != -1) {
                    incomeTotals[sourceIndex] += incomeTransactions[i].amount;
                    totalIncome += incomeTransactions[i].amount;
                }
            }
        }

        cout << "Total Income: " << totalIncome << endl; 
        for (int i = 0; i < incomeSourceCount; i++) {
            cout << "* " << incomeSources[i].name << ": " << incomeTotals[i] << endl;
        }
        delete[] incomeTotals;

        cout << "\n-- Expense Breakdown --\n";
        double totalExpense = 0;
        double* expenseTotals = new double[expenseCategoryCount]();
        
        for (int i = 0; i < expenseTransactionCount; i++) {
            if (expenseTransactions[i].date.year == year[y]) {
                int categoryIndex = findExpenseCategoryIndexByID(expenseCategories, expenseCategoryCount, expenseTransactions[i].sourceID); 
                if (categoryIndex != -1) {
                    expenseTotals[categoryIndex] += expenseTransactions[i].amount;
                    totalExpense += expenseTransactions[i].amount;
                }
            }
        }

        cout << "Total Expense: " << totalExpense << endl; 
        for (int i = 0; i < expenseCategoryCount; i++) {
            cout << "* " << expenseCategories[i].name << ": " << expenseTotals[i] << endl;
        }
        delete[] expenseTotals;
    } 
}