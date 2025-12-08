#include <iostream>
#include <string>
#include <iomanip>
#include "Income.h"

using namespace std;

static IncomeTransaction* g_incomeTrans = nullptr;
static int g_incomeTransCount = 0;

int findIncomeSourceIndexByID(IncomeSource* sources, int IncomeCount, string id) {
	int index = -1;
	for (int i = 0; i < IncomeCount; i++) {
		if (sources[i].ID == id) {
			return i;
		}
	}
	return -1;
}
int askAndFindIncomeSourceIndexByID(IncomeSource* sources, int IncomeCount) {
	cout << "\n---TIM NGUON THU THEO ID---\n";
	cout << "Vui long nhap ID cua nguon thu can tim: ";
	string id;
	cin >> id;
	cout << endl;
	return findIncomeSourceIndexByID(sources, IncomeCount, id);
}
void addIncomeSource(IncomeSource*& sources, int& IncomeCount) {
	cout << "\n---THEM NGUON THU---\n";
	IncomeSource newSource;
	cout << "Vui long nhap thong tin nguon thu moi:\n";

	cout << "Nhap ID: ";
	cin >> newSource.ID;

	cout << "Nhap ten vi: ";
	getline(cin, newSource.name);

	if (findIncomeSourceIndexByID(sources, IncomeCount, newSource.ID) != -1) {
		cout << "LOI: ID da ton tai. Khong them.\n";
		return;
	}


	IncomeSource* newArr = new IncomeSource[IncomeCount + 1];


	for (int i = 0; i < IncomeCount; ++i) {
		newArr[i] = sources[i];
	}

	newArr[IncomeCount] = newSource;

	delete[] sources;
	sources = newArr;
	++IncomeCount;

	cout << "Da cap nhat xong vi!\n";
}


void editIncomeSource(IncomeSource* sources, int count) {
	cout << "\n---CHINH SUA NGUON THU---\n";
	string ID;
	cout << "Nhap ID cua nguon thu can thay doi: ";
	cin >> ID;
	int index = -1;
	index = findIncomeSourceIndexByID(sources, count, ID);
	if (index == -1) {
		cout << "Khong the tim thay vi de chinh sua.\n";
		return;
	}
	string field;
	cout << "Vui long nhap thong tin can chinh sua cua nguon thu: ";
	cin >> field;
	if (field == "ID") {
		cout << "Vui long nhap ID moi: ";
		string newID;
		cin >> newID;

		if (findIncomeSourceIndexByID(sources, count, newID) != -1) {
			cout << "LOI: ID moi da ton tai. Khong cap nhat.\n";
			return;
		}
		sources[index].ID = newID;
	}
	else if (field == "name") {
		cout << "Vui long nhap ten vi moi: ";
		getline(cin, sources[index].name);
	}
	else {
		cout << "Truong hop khong hop le. \n";
		return;
	}
	cout << "\n---DA CAP NHAT THANH CONG---\n";
}
void deleteIncomeSource(IncomeSource*& sources, int& count) {
	cout << "\n---XOA NGUON THU---\n";
	string IDToDelete;
	cout << "Nhap ID cua nguon thu can xoa: ";
	cin >> IDToDelete;
	cout << endl;

	int index = -1;
	index = findIncomeSourceIndexByID(sources, count, IDToDelete);
	if (index != -1) {
		cout << "Khong tim thay nguon thu de xoa.\n";
		return;
	}
	if (count == 1) {
		delete sources;
		sources = nullptr;
		count = 0;
		cout << "Da xoa vi ID( " << IDToDelete << ") " << "thanh cong.\n";
		return;
	}
	IncomeSource* newArr = new IncomeSource[count - 1];

	for (int i = 0, j = 0; i < count; ++i) {
		if (i == index) continue;
		newArr[j++] = sources[i];
	}

	delete[] sources;
	sources = newArr;
	--count;

	cout << "Da xoa Vi ID[" << IDToDelete << "] thanh cong.\n";
}


void addIncomeTransaction(IncomeTransaction*& trans, int& transCount,Wallet* wallets, int walletCount,IncomeSource* sources, int sourceCount) {
    cout << "\n---THEM GIAO DICH THU---\n";
    IncomeTransaction t;
    cout << "Nhap ID giao dich: ";
    getline(cin, t.ID);

   
    cout << "Nhap ngay (dd mm yyyy): ";
    cin >> t.date.day >> t.date.month >> t.date.year;

  
    cout << "Nhap so tien (+): ";
    cin >> t.amount;
    if (t.amount <= 0) {
        cout << "LOI: so tien phai > 0.\n";
      
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

 
    cout << "Nhap ID Vi nhan tien: ";
    getline(cin, t.walletID);
    int wIdx = findWalletIndexByID(wallets, walletCount, t.walletID);
    if (wIdx == -1) {
        cout << "LOI: Khong tim thay Vi ID[" << t.walletID << "].\n";
        return;
    }

    cout << "Nhap ID Nguon Thu: ";
    getline(cin, t.sourceID);
    int sIdx = findIncomeSourceIndexByID(sources, sourceCount, t.sourceID);
    if (sIdx == -1) {
        cout << "LOI: Khong tim thay Nguon Thu ID[" << t.sourceID << "].\n";
        return;
    }


    cout << "Nhap ghi chu (co the de trong): ";
    getline(cin, t.note);

    
    IncomeTransaction* newArr = new IncomeTransaction[transCount + 1];
    for (int i = 0; i < transCount; ++i) newArr[i] = trans[i];
    newArr[transCount] = t;

   
    delete[] trans;            
    trans = newArr;
    ++transCount;

   
    wallets[wIdx].balance += t.amount;

   
    g_incomeTrans = trans;
    g_incomeTransCount = transCount;

    cout << "Da them giao dich thu va cap nhat so du Vi ["
        << wallets[wIdx].ID << "] thanh cong.\n";
}

void printIncomeTransaction(IncomeTransaction t) {
    cout << "----------------------------------------\n";
    cout << "ID GD : " << t.ID << "\n";
    cout << "Ngay  : "; printDate(t.date); cout << "\n";
    cout << fixed << setprecision(2);
    cout << "So tien: +" << t.amount << "\n";
    cout << "Vi     : " << t.walletID << "\n";
    cout << "Nguon  : " << t.sourceID << "\n";
    if (!t.note.empty()) cout << "Ghi chu: " << t.note << "\n";
    cout << "----------------------------------------\n";
}

void filterIncomeByDateRange(Date from, Date to) {
    cout << "\n---LOC GIAO DICH THU THEO KHOANG NGAY---\n";
    if (g_incomeTrans == nullptr || g_incomeTransCount == 0) {
        cout << "Khong co giao dich de loc.\n";
        return;
    }

    if (compareDate(from, to) > 0) std::swap(from, to);

    int found = 0;
    for (int i = 0; i < g_incomeTransCount; ++i) {
        if (isDateInRange(g_incomeTrans[i].date, from, to)) {
            printIncomeTransaction(g_incomeTrans[i]);
            ++found;
        }
    }

    if (found == 0) {
        cout << "Khong co giao dich trong khoang ngay yeu cau.\n";
    }
}

void filterIncomeByWallet(int walletID, Date from, Date to) {
    cout << "\n---LOC GIAO DICH THU THEO VI---\n";
    if (g_incomeTrans == nullptr || g_incomeTransCount == 0) {
        cout << "Khong co giao dich de loc.\n";
        return;

    string walletIDStr = to_string(walletID);

    if (compareDate(from, to) > 0) std::swap(from, to);

    int found = 0;
    for (int i = 0; i < g_incomeTransCount; ++i) {
        if (g_incomeTrans[i].walletID == walletIDStr &&
            isDateInRange(g_incomeTrans[i].date, from, to)) {
            printIncomeTransaction(g_incomeTrans[i]);
            ++found;
        }
    }

    if (found == 0) {
        cout << "Khong co giao dich cho Vi ID[" << walletIDStr << "] trong khoang ngay yeu cau.\n";
    }
}
