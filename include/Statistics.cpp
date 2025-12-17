#include <iostream>
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

    cout << "\nTotal Income: " << totalIncome << endl;
    cout << "Total Expense: " << totalExpense << endl;
    cout << "Net Balance: " << totalIncome - totalExpense << endl;
}

void Statistics::annualOverview(
    IncomeTransaction* incomes, int incomeCount,
    ExpenseTransaction* expenses, int expenseCount,
    int year
) {
    double totalIncome = 0;
    double totalExpense = 0;

    for (int i = 0; i < incomeCount; i++) {
        if (incomes[i].date.year == year) {
            totalIncome += incomes[i].amount;
        }
    }

    for (int i = 0; i < expenseCount; i++) {
        if (expenses[i].date.year == year) {
            totalExpense += expenses[i].amount;
        }
    }

    cout << "\n=== " << year << " ===\n";
    cout << "Income: " << totalIncome << endl;
    cout << "Expense: " << totalExpense << endl;
    cout << "Net: " << totalIncome - totalExpense << endl;
}
