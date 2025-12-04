#pragma once

class App {
    public:
        void run();
    
    private:
        void showDashboard();
        void handleChoice();

        void addIncomeMenu();
        void addExpenseMenu();
        void showWalletMenu();
        void manageCategoriesMenu();
        void recurringMenu();
        void statisticsMenu();
};