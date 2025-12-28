# PERSONAL FINANCE MANAGER (C++ Console Application)

## 1. Project Overview

**Personal Finance Manager** is a C++ console-based application developed as a course project for *Introduction to Programming*.
The program helps users manage **income**, **expenses**, **wallets**, and **recurring transactions**, while ensuring data consistency and persistence across multiple sessions.

The application focuses on **referential integrity**, meaning that editing IDs of wallets or categories will not break existing transaction records.


## 2. Main Features

### 2.1 Transaction Management

* Record **Income** and **Expense** transactions.
* Each transaction includes:

  * Date
  * Amount
  * Wallet
  * Income Source / Expense Category
  * Description

### 2.2 Master Data Management

* Manage:

  * Wallets
  * Income Sources
  * Expense Categories
* When an ID is edited, all related transactions are **automatically updated** to maintain consistency.

### 2.3 Recurring Transactions

* Support **monthly recurring income or expenses**.
* Recurring transactions are automatically applied **when the application starts**.
* Each recurring transaction has:

  * Start date
  * Optional end date

### 2.4 Statistics & Reports

* **Time-based statistics:** total income, total expense, and net balance within a date range.
* **Wallet-based statistics:** view income/expense details by wallet.
* **Year-based statistics:** yearly income, expense, and breakdown by category or source.

### 2.5 Data Persistence

* All data is stored in **binary (.dat) files**.
* Data is automatically loaded when the application starts and saved when the user exits properly.

---

## 3. Technical Constraints & Implementation

* **Language:** C++
* **Data Structures:** Custom dynamic arrays using `new` / `delete`
* **STL Containers:** *Not used* (`std::vector`, `std::list`, etc.)
* **File Handling:** `<fstream>` with binary serialization
* **Interface:** Console-based (CLI)

---

## 4. Compilation & Execution

### 4.1 Compilation

Compile the program using a C++ compiler (example with g++):

```bash
g++ main.cpp App.cpp DataManager.cpp Wallet.cpp Income.cpp Expense.cpp RecurringTransaction.cpp Statistics.cpp Utils.cpp -o FinanceManager
```

### 4.2 Running the Application

* On Linux/macOS:

```bash
./FinanceManager
```

* On Windows:

```bash
FinanceManager.exe
```

---

## 5. How to Use (Instructions)

1. Launch the application.
2. The **Dashboard** displays:

   * Total balance
   * Individual wallet balances
3. Use numeric menu options (`0–6`) to navigate between features.
4. Follow on-screen instructions to add, edit, or view data.
5. **Always choose `0. Exit` from the menu** to ensure all data is saved correctly before closing the program.

Note: You can run this application like this video: https://www.youtube.com/watch?v=Gm2QKBP6u94&feature=youtu.be
---

## 6. File Structure

```text
PersonalFinanceManager/
├── src/
├── include/
├── wallets.dat
├── expense_transactions.dat
├── expense_categories.dat
├── income_sources.dat
├── expense_transactions.dat
├── recurring.dat
└── README.md
```

## 7. Limitations
* Console-based interface only (no GUI).
* Data is stored locally and does not support multi-user access.
* Recurring transactions are processed only at application startup.
--

## 8. Developers
* 25125042 - Huỳnh Trần Gia Hân
* 25125046 - Đặng Minh Nhật