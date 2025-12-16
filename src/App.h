#pragma once

#include "DataManager.h"
#include "RecurringTransaction.h"

class App {
    public:
        App();
        void run();
    
    private:
        DataManager data;

        void showDashboard();
        void handleChoice();

        void addIncomeMenu();
        void addExpenseMenu();
        void showWalletMenu();
        void manageCategoriesMenu();
        void recurringMenu();
        void statisticsMenu();
};