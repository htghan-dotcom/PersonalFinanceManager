
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>    
#include "Expense.h"

using namespace std;

ExpenseTransaction* gExpTrans = nullptr;
int gExpTransCount = 0;


int findExpenseCategoryIndexByID(ExpenseCategory* cate, int count, string id) {
    for (int i = 0; i < count; ++i) {
        if (cate[i].id == id) return i;
    }
    return -1;
}

int askAndFindExpenseSourceIndexByID(ExpenseCategory* cate, int count) {
    cout << "Nhap ID ExpenseCategory: ";
    string id;
    getline(cin, id);
    if (id.empty()) getline(cin, id); 
    int idx = findExpenseCategoryIndexByID(cate, count, id);
    if (idx == -1) {
        cout << "Khong tim thay ExpenseCategory co ID = " << id << "\n";
    }
    return idx;
}

void addExpenseCategory(ExpenseCategory*& cate, int& count) {
    ExpenseCategory c;

    cout << "Nhap ID category : ";
    getline(cin, c.id);
    if (c.id.empty()) getline(cin, c.id);

    if (findExpenseCategoryIndexByID(cate, count, c.id) != -1) {
        cout << "ID da ton tai! Khong the them.\n";
        return;
    }

    cout << "Nhap ten category: ";
    getline(cin, c.name);

    ExpenseCategory* newArr = new ExpenseCategory[count + 1];
    for (int i = 0; i < count; ++i) newArr[i] = cate[i];
    newArr[count] = c;

    delete[] cate;
    cate = newArr;
    ++count;

    cout << "Da them ExpenseCategory.\n";
}

void editExpenseCategory(ExpenseCategory* cate, int count) {
    int idx = askAndFindExpenseSourceIndexByID(cate, count);
    if (idx == -1) return;

    cout << "Ten hien tai: " << cate[idx].name << "\nNhap Ten moi : ";
    string name;
    getline(cin, name);
    if (!name.empty()) cate[idx].name = name;

    cout << "Da cap nhat ExpenseCategory.\n";
}

void deleteExpenseSource(ExpenseCategory*& cate, int& count) {
    int idx = askAndFindExpenseSourceIndexByID(cate, count);
    if (idx == -1) return;

    ExpenseCategory* newArr = new ExpenseCategory[count - 1];
    for (int i = 0, j = 0; i < count; ++i) {
        if (i == idx) continue;
        newArr[j++] = cate[i];
    }
    delete[] cate;
    cate = newArr;
    --count;

    cout << "Da xoa ExpenseCategory.\n";
}

void addExpenseTransaction(ExpenseTransaction*& trans, int& transCount,
    Wallet* wallets, int walletCount,
    ExpenseCategory* sources, int CategoryCount)
{
    ExpenseTransaction t;

 
    cout << "Nhap ID giao dich (bo trong se tu sinh): ";
    getline(cin, t.ID);


    cout << "Nhap ngay (dd mm yyyy): ";
    cin >> t.date.day >> t.date.month >> t.date.year;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

 
    cout << "Nhap sourceID (ID danh muc chi): ";
    getline(cin, t.sourceID);
    if (findExpenseCategoryIndexByID(sources, CategoryCount, t.sourceID) == -1) {
        cout << "Khong tim thay ExpenseCategory ID = " << t.sourceID << ". Huy.\n";
        return;
    }

    cout << "Nhap walletID (so nguyen): ";
    string walletID;
    getline(cin, walletID);
    if (walletID.empty()) getline(cin, walletID);


    int widx = findWalletIndexByID(wallets, walletCount, walletID); 
    if (widx == -1) {
        cout << "Khong tim thay Wallet ID = " << walletID << ". Huy.\n";
        return;
    }
    t.walletID = walletID; 

   
    cout << "Nhap so tien (>=0): ";
    cin >> t.amount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (t.amount < 0) {
        cout << "So tien khong hop le. Huy.\n";
        return;
    }

  
    cout << "Nhap ghi chu: ";
    getline(cin, t.note);


    ExpenseTransaction* newArr = new ExpenseTransaction[transCount + 1];
    for (int i = 0; i < transCount; ++i) newArr[i] = trans[i];
    newArr[transCount] = t;

    delete[] trans;
    trans = newArr;
    ++transCount;


    gExpTrans = trans;
    gExpTransCount = transCount;

    cout << "Da them ExpenseTransaction.\n";
}

void printExpenseTransaction(ExpenseTransaction t) {
    cout << "ExpenseTransaction {"
        << " ID=" << t.ID
        << ", date=" << t.date.day << "/" << t.date.month << "/" << t.date.year
        << ", sourceID=" << t.sourceID
        << ", walletID=" << t.walletID
        << ", amount=" << fixed << setprecision(2) << t.amount
        << ", note=" << t.note
        << " }\n";
}

void filterExpenseByDateRange(Date from, Date to) {
    if (gExpTrans == nullptr || gExpTransCount == 0) {
        cout << "Khong co du lieu ExpenseTransaction (gExpTrans rong).\n";
        return;
    }
    cout << "=== Expense trong khoang "
        << from.day << "/" << from.month << "/" << from.year << " - "
        << to.day << "/" << to.month << "/" << to.year << " ===\n";

    bool found = false;
    for (int i = 0; i < gExpTransCount; ++i) {
        if (isDateInRange(gExpTrans[i].date, from, to)) {
            printExpenseTransaction(gExpTrans[i]);
            found = true;
        }
    }
    if (!found) cout << "Khong co giao dich nao trong khoang thoi gian.\n";
}

void filterExpenseByWallet(int walletID, Date from, Date to) {
    if (gExpTrans == nullptr || gExpTransCount == 0) {
        cout << "Khong co du lieu ExpenseTransaction (gExpTrans rong).\n";
        return;
    }
    string walletIDStr = to_string(walletID); // vì transaction lưu walletID dạng string

    cout << "=== Expense walletID=" << walletID << " trong khoang "
        << from.day << "/" << from.month << "/" << from.year << " - "
        << to.day << "/" << to.month << "/" << to.year << " ===\n";

    bool found = false;
    for (int i = 0; i < gExpTransCount; ++i) {
        if (gExpTrans[i].walletID == walletIDStr &&
            isDateInRange(gExpTrans[i].date, from, to)) {
            printExpenseTransaction(gExpTrans[i]);
            found = true;
        }
    }
    if (!found) cout << "Khong co giao dich nao phu hop.\n";
}
