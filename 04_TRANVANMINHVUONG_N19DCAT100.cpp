#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <iomanip>
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;

typedef struct ex{
	string data;
	ex *pNext;
	ex *pRev;
}EX;
struct node
{
	string tu;
	string nghia;
	string loaitu;
	EX info;
	node *pNext;
};
typedef struct node NODE;

struct list
{
	NODE *pHead;
	NODE *pTail;
};
typedef struct list LIST;

void khoiTao(LIST &l)
{
	l.pHead = NULL;
	l.pTail = NULL;
}

bool isEmpty(LIST &l)
{
	if (l.pHead == NULL)
		return true;
	return false;
}
NODE *setfullTu(string tu,string nghia,string viDu,string loaitu)
{
	NODE *p= new NODE;
	p->tu=tu;;
	p->loaitu=loaitu;
	p->nghia=nghia;
	p->info.data=viDu;
	return p;
}
NODE *khoiTaoNODE(string tu,string nghia,string viDu,string loaitu)
{
	NODE *p = new NODE;
	if (p == NULL)
	{
		cout << "Khong du bo nho cap phat !";
		return NULL;
	}
	p=setfullTu(tu,nghia,viDu,loaitu);
	p->pNext = NULL;
	return p;
}

NODE *findTail(LIST &l)
{
	if (isEmpty(l))
		return NULL;
	NODE *p = l.pHead;
	while (p->pNext != NULL)
	{
		p = p->pNext;
	}
	return p;
}

// ------------- khai bao protype --------------
string search;
void themVaoDau(LIST &l, NODE *p);
void xoaDau(LIST &l);
void themVaoCuoi(LIST &l, NODE *p);
void xoaCuoi(LIST &l);
void xoaNodeCoKhoaBatKy(LIST &l, string tu);
void chinhSuaTu(LIST &l);
void menu();
bool kiemTraChuoi(string s);
string chuanHoaChuoi(string s);
void deleteList(LIST &l);
int tapTuDien(string p);
bool soSanh(string input, NODE *p);
NODE* timkiem(LIST l, string input);
void inDanhSachTu(LIST l, string input);
void xuatFullTu(NODE *p);
void gotoxy(short x, short y);
// ------------- ham main --------------
int main()
{
	menu();
	return 0;
}

// ------------- function --------------
void xuatFullTu(NODE *p)
	{
		string s = p->tu;
		cout <<"\t\t\t"<< setw(13) << left<<p->tu;
		string loaiTuMoi, nghiaMoi, viDuMoi, loaiTuCopy = p->loaitu + ';', nghiaCopy = p->nghia + '/', viDuCopy = p->info.data + '/';
		string MloaiTuMoi[100], MnghiaMoi[100], MviDuMoi[100], temp1 = "", temp2 = "";
		bool KT[100];
		int doDaiType = 0, doDaiMean = 0, doDaiExample = 0;
		for (int i = 0; i < loaiTuCopy.length(); i++)
			if (loaiTuCopy[i] == ';')
				doDaiType++;
		for (int i = 0; i < nghiaCopy.length(); i++)
			if (nghiaCopy[i] == ';' || nghiaCopy[i] == '/')
			{
				doDaiMean++;
				temp1 += nghiaCopy[i];
			}

		for (int i = 0; i < viDuCopy.length(); i++)
			if (viDuCopy[i] == ';' || viDuCopy[i] == '/')
			{
				doDaiExample++;
				temp2 += viDuCopy[i];
			}

		int GTLN = max(doDaiType, max(doDaiMean, doDaiExample));
		for (int i = 0; i < GTLN; i++)
		{
			MloaiTuMoi[i] = "";
			MnghiaMoi[i] = "";
			MviDuMoi[i] = "";
		}
		for (int i = 0; i < GTLN;)
		{
			for (int j = 0; j < loaiTuCopy.length(); j++)
				if (loaiTuCopy[j] != ';')
					loaiTuMoi += loaiTuCopy[j];
				else
				{
					MloaiTuMoi[i] = loaiTuMoi;
					loaiTuCopy = loaiTuCopy.erase(0, j + 1);
					loaiTuMoi = loaiTuMoi.erase(0, loaiTuMoi.length());
					break;
				}
			int z = 0, nho1 = i, nho2 = i;
			for (int j = 0; j < nghiaCopy.length(); j++)
			{
				if (nghiaCopy[j] != ';' && nghiaCopy[j] != '/')
				{
					nghiaMoi += nghiaCopy[j];
				}
				else
				{
					MnghiaMoi[nho1] = nghiaMoi;
					nho1++;
					nghiaMoi = nghiaMoi.erase(0, nghiaMoi.length());
					if (nghiaCopy[j] == '/')
					{
						z = j;
						break;
					}
				}
			}
			nghiaCopy = nghiaCopy.erase(0, z + 1);
			for (int j = 0; j < viDuCopy.length(); j++)
			{
				if (viDuCopy[j] != ';' && viDuCopy[j] != '/')
				{
					viDuMoi += viDuCopy[j];
				}
				else
				{
					MviDuMoi[nho2] = viDuMoi;
					nho2++;
					viDuMoi = viDuMoi.erase(0, viDuMoi.length());
					if (viDuCopy[j] == '/')
					{
						z = j;
						break;
					}
				}
			}
			viDuCopy = viDuCopy.erase(0, z + 1);
			if (nho1 > nho2)
				i = nho1;
			else
				i = nho2;
		}
		for (int i = 0; i < GTLN; i++)
		{
			while (MloaiTuMoi[i][0] == ' ')
				MloaiTuMoi[i].erase(0, 1);
			while (MloaiTuMoi[i][MloaiTuMoi[i].length() - 1] == ' ')
				MloaiTuMoi[i].erase(MloaiTuMoi[i].length() - 1, 1);
			while (MnghiaMoi[i][0] == ' ')
				MnghiaMoi[i].erase(0, 1);
			while (MnghiaMoi[i][MnghiaMoi[i].length() - 1] == ' ')
				MnghiaMoi[i].erase(MnghiaMoi[i].length() - 1, 1);
			for (int j = 0; j < MnghiaMoi[i].length(); j++)
				while (MnghiaMoi[i][j] == ' ' && MnghiaMoi[i][j + 1] == ' ')
					MnghiaMoi[i].erase(j, 1);
			while (MviDuMoi[i][0] == ' ')
				MviDuMoi[i].erase(0, 1);
			while (MviDuMoi[i][MviDuMoi[i].length() - 1] == ' ')
				MviDuMoi[i].erase(MviDuMoi[i].length() - 1, 1);
			for (int j = 0; j < MviDuMoi[i].length(); j++)
				while (MviDuMoi[i][j] == ' ' && MviDuMoi[i][j + 1] == ' ')
					MviDuMoi[i].erase(j, 1);
			if (i == 0)
				cout << setw(20) << left << MloaiTuMoi[i]
					 << setw(40) << left << MnghiaMoi[i]
					 << setw(46) << left << MviDuMoi[i] << endl;
			else
				cout << "\t\t\t" << setw(13) << left << " "
					 << setw(20) << left << MloaiTuMoi[i]
					 << setw(40) << left << MnghiaMoi[i]
					 << setw(46) << left << MviDuMoi[i] << endl;
		}
	}
void menu()
{
	LIST l;
	khoiTao(l);
	ifstream fw, ft, fm, fe;
	string tu, loai, nghia, vd;
	int count = 0;
	fw.open("word.txt", ios::in);
	ft.open("type.txt", ios::in);
	fm.open("mean.txt", ios::in);
	fe.open("example.txt", ios::in);
	while (!fw.eof())
	{
		count++;
		getline(fw, tu, ' ');
		getline(ft, loai, ' ');
		getline(fm, nghia, '@');
		getline(fe, vd, '@');
		NODE *p = khoiTaoNODE(tu,nghia,vd,loai);
		themVaoCuoi(l, p);
	}

	int luaChon;
	while (true)
	{
		system("cls");
		cout << "\t\t\t\t\t\t\t\t==================================" << endl
			 << "\t\t\t\t\t\t\t\t||         ****MENU****         ||" << endl
			 << "\t\t\t\t\t\t\t\t||   1. TIM KIEM                ||" << endl
			 << "\t\t\t\t\t\t\t\t||   2. THEM TU                 ||" << endl
			 << "\t\t\t\t\t\t\t\t||   3. CHINH SUA TU            ||" << endl
			 << "\t\t\t\t\t\t\t\t||   4. XOA TU                  ||" << endl
			 << "\t\t\t\t\t\t\t\t||   5. XOA TOAN BO TU DIEN     ||" << endl
			 << "\t\t\t\t\t\t\t\t||   6. XEM TOAN BO TU DIEN     ||" << endl
			 << "\t\t\t\t\t\t\t\t||   0. THOAT KHOI TU DIEN      ||" << endl
			 << "\t\t\t\t\t\t\t\t==================================" << endl
			 << endl
			 << endl;


		cout << "\n\n\tMoi ban nhap lua chon: ";
		cin >> luaChon;

		if (luaChon < 0 || luaChon > 6)
		{
			cout << "\n\tLua chon cua ban khong dung!";
			getch();
		}
		else if (luaChon == 1)
		{
			int keyCode=0,pos=0;
			string input = "";
			do
			{
				system("cls");
				bool timKiem = false;
				system("cls");
				cout << "\t\t\t\t\t\t\t\t===================================" << endl
					 << "\t\t\t\t\t\t\t\t||" << char(254) << " ESC   :  Quay lai MENU       ||" << endl
					 << "\t\t\t\t\t\t\t\t===================================" << endl;
				cout<< "NHAP TU CAN TRA"<<endl;
				cout << char(218);
				for (int i = 0; i < 10; i++) {
					cout << char(196);
				}
				cout << char(191) << endl;
				
				cout << char(179) << input;
				for (int i = 0; i < 10 - input.size(); i++) {
					cout << char(255);
				}
				cout << char(179);
				
				cout << endl << char(192);
				for (int i = 0; i < 10; i++) {
					cout << char(196);
				}
				cout << char(217);
	
				inDanhSachTu(l,input);
				gotoxy(1 + input.size(), 5);
				keyCode = getch();
				
				switch (keyCode) {
				case 8: 
					input = input.substr(0, input.size() - 1); 
					break;
				case 13: 
					for (NODE *k = l.pHead; k != NULL; k = k->pNext)
					if (input == k->tu)
					{
						system("cls");
						timKiem = true;
						SetConsoleTextAttribute(console, 75);
						cout << "\n\n\t\t\t" << setw(13) << left << "Word" << setw(20) << left << "Type" << setw(40) << left << "Mean" << setw(46) << left << "Example" << endl;
						SetConsoleTextAttribute(console, 7);
						xuatFullTu(k);
						cout << endl;
						cout << "\n\t\t\t\t\t[NOTE]: An phim bat ky de quay lai menu chuc nang!";
						getch();
					}
					if (!timKiem)
					{
						system("cls");
						cout << "\n\t\t[ERROR]: Tu '" << input << "' chua co trong tu dien!" << endl
							 << "\t\tNhan phim bat ky de quay lai!" << endl;
						getch();
					}
				default:
					if (keyCode >= 97 && keyCode <= 122) {
						input += char(keyCode);
					}
				}
			}while(keyCode!=27);
		}
		else if (luaChon == 2)
		{
			system("cls");
			bool timKiem = false;

			cout << "\n\t\t\tNhap tu can THEM: ";
			cin >> search;
			search = chuanHoaChuoi(search);

			for (NODE *k = l.pHead; k != NULL; k = k->pNext)
				if (search == k->tu)
					timKiem = true;
			if (timKiem)
			{
				cout << "\n\t\t[ERROR]: Tu '" << search << "' da ton tai trong tu dien!" << endl
					 << "\t\tNhan phim bat ky de quay lai menu chuc nang" << endl;
				getch();
			}
			else
			{
				string saveLoai = " ", saveNghia = " ", saveViDu = " ";
				ofstream fw, ft, fm, fe;
				cout << "\t\t\t\t\t\t\t\t===================================" << endl
					 << "\t\t\t\t\t\t\t\t||" << char(254) << " ESC   :  Quay lai MENU       ||" << endl
					 << "\t\t\t\t\t\t\t\t||" << char(254) << " Enter :  Tiep tuc them       ||" << endl
					 << "\t\t\t\t\t\t\t\t===================================" << endl
					 << endl;
				cout << "\t\t\t\t\t\t\t[NOTE]: Hay ngan cach cac nghia & vi du boi dau ';' !" << endl;
				while (true)
				{
					char key = getch();
					if (key == 27)
						break;
					string loai, nghia, vd;
					fflush(stdin);
					cout << "Nhap loai tu: ";
					cin >> loai;
					fflush(stdin);
					saveLoai = saveLoai + loai ;
					cout << "Nhap nghia cua tu: ";
					getline(cin, nghia);
					saveNghia = saveNghia + nghia + '/'; 
					cout << "Nhap vi du: ";
					getline(cin, vd);
					saveViDu = saveViDu + vd + '/'; 
					cout << endl;
				}
				loai = saveLoai.substr(1, saveLoai.length() - 1);
				nghia = saveNghia.substr(1, saveNghia.length() - 1);
				vd = saveViDu.substr(1, saveViDu.length() - 1);
				NODE *p = khoiTaoNODE(search,nghia,vd,loai);
				search = tu + ' ' + search;
				loai = loai + ' ' + loai;
				nghia = nghia + '@' + nghia;
				vd = vd + '@' + vd;
				themVaoCuoi(l, p);
				ofstream foW("word.txt"), foT("type.txt"), foM("mean.txt"), foE("example.txt");
				foW << search;
				foT << loai;
				foM << nghia;
				foE << vd;
				foW.close();
				foT.close();
				foM.close();
				foE.close();
			}
		}
		else if (luaChon == 3)
		{
			system("cls");
			bool timKiem = false;
			do
			{
				cout << "\n\t\t\tNhap tu can CHINH SUA: ";
				cin >> search;
				if (!kiemTraChuoi(search))
				{
					
					cout << "\n\t\t\t[NOTE]: Tu nay KHONG CO trong tu dien!" << endl;
					
				}
			} while (!kiemTraChuoi(search));
			search = chuanHoaChuoi(search);

			for (NODE *k = l.pHead; k != NULL; k = k->pNext)
				if (search == k->tu)
					timKiem = true;
			if (!timKiem)
			{
				
				cout << "\n\t\t[ERROR]: Tu '" << search << "' KHONG CO trong tu dien!" << endl;
				getch();
			}

			chinhSuaTu(l);
		}
		else if (luaChon == 4)
		{
			system("cls");
			cout<<"DANH SACH TU CO TRONG TU DIEN\n";
			bool timKiem = false;
			for (NODE *k = l.pHead; k != NULL; k = k->pNext)
			{
				cout << k->tu << " ";
			}
			
			cout << "\n\n\t\t\t\tNhap tu can XOA: ";
			
			
			cin >> search;
			search = chuanHoaChuoi(search);
			ofstream foW1("word.txt"), foT1("type.txt"), foM1("mean.txt"), foE1("example.txt");
			for (NODE *k = l.pHead; k != NULL; k = k->pNext)
				if (k->tu == search)
				{
					timKiem = true;
					xoaNodeCoKhoaBatKy(l, search);
					break;
				}

			if (timKiem == true)
			{
				for (NODE *k = l.pHead; k != NULL; k = k->pNext)
				{
					if (k->pNext == NULL)
					{
						foW1 << k->tu;
						foT1 << k->loaitu;
						foM1 << k->nghia;
						foE1 << k->info.data;
					}
					else
					{
						foW1 << k->tu << ' ';
						foT1 << k->loaitu << ' ';
						foM1 << k->nghia << '@';
						foE1 << k->info.data << '@';
					}
				}
				cout << "\n\t\t\t[NOTE]: Tu '" << search << "' da duoc xoa!" << endl
					 << "\t\t\tNhan phim bat ky de quay lai menu chuc nang" << endl;
				getch();
			}
			foW1.close();
			foT1.close();
			foM1.close();
			foE1.close();

			if (!timKiem)
			{
				cout << "\n\t\t[ERROR]: Tu '" << search << "' KHONG CO trong tu dien!" << endl;
				getch();
			}
		}
		else if (luaChon == 5)
		{
			system("cls");
			ofstream foW1("word.txt"), foT1("type.txt"), foM1("mean.txt"), foE1("example.txt");
			deleteList(l);
			foW1.close();
			foT1.close();
			foM1.close();
			foE1.close();
			cout<<setw(95)<<right<<"DA XOA TOAN BO TU DIEN";
			getch();
		}
		else if (luaChon == 6)
		{
			system("cls");
			SetConsoleTextAttribute(console, 91);
			cout << "\n\n\t\t\t" << setw(13) << left << "Word" << setw(20) << left << "Type" << setw(40) << left << "Mean" << setw(46) << left << "Example" << endl;
			SetConsoleTextAttribute(console, 7);
			for (NODE *k = l.pHead; k != NULL; k = k->pNext)
			{
				xuatFullTu(k);
				cout<<"\t\t\t_______________________________________________________________________________________________________________________"<<endl;
			}
			cout<< "\n\t\t\t\t\t\t[NOTE]:Nhan phim bat ky de quay lai menu chuc nang" << endl;
			getch();
		}
		else // luaChon == 0;
			break;
	}

	fw.close();
	ft.close();
	fm.close();
	fe.close();
}

void chinhSuaTu(LIST &l)
{
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
		if (search == k->tu)
		{
			bool timKiem = true;

			while (true)
			{
				system("cls");
				
				cout << "\n\n";
				cout << "\t\t\t\t============================" << endl
					 << "\t\t\t\t||    1. Sua loai tu      ||" << endl
					 << "\t\t\t\t||    2. Sua nghia        ||" << endl
					 << "\t\t\t\t||    3. Sua vi du        ||" << endl
					 << "\t\t\t\t||    4. Sua tat ca       ||" << endl
					 << "\t\t\t\t||    0. Cancel           ||" << endl
					 << "\t\t\t\t============================" << endl;
			

				int luaChon1;
				cout << "\n\tNhap lua chon cua ban: ";
				cin >> luaChon1;
				if (luaChon1 < 0 || luaChon1 > 4)
				{
					
					cout << "\n\tLua chon cua ban khong dung! Vui long nhap lai!" << endl;
					getch();
				}

				else if (luaChon1 >= 1 && luaChon1 <= 4)
				{
					if (luaChon1 == 1)
					{
						string loaiTu1;
						cout << "\tNhap LOAI TU: ";
						cin.ignore();
						getline(cin, loaiTu1);
						k->loaitu=loaiTu1;
					}
					if (luaChon1 == 2)
					{
						string nghia1;
						cout << "\tNhap NGHIA: ";
						cin.ignore();
						getline(cin, nghia1);
						k->nghia=nghia1;
					}
					if (luaChon1 == 3)
					{
						string viDu1;
						cout << "\tNhap VI DU: ";
						cin.ignore();
						getline(cin, viDu1);
						k->info.data=viDu1;
					}
					if (luaChon1 == 4)
					{
						string tu1;
						cout << "\t\tNhap tu ban muon THAY THE: ";
						cin.ignore();
						getline(cin, tu1);
						k->tu=tu1;

						string loaiTu1;
						cout << "\t\tNhap LOAI TU: ";
						getline(cin, loaiTu1);
						k->loaitu=loaiTu1;

						string nghia1;
						cout << "\t\tNhap NGHIA: ";
						getline(cin, nghia1);
						k->nghia=nghia1;

						string viDu1;
						cout << "\t\tNhap VI DU: ";
						getline(cin, viDu1);
						k->info.data=viDu1;
					}
					ofstream foW1("word.txt"), foT1("type.txt"), foM1("mean.txt"), foE1("example.txt");
					for (NODE *k = l.pHead; k != NULL; k = k->pNext)
					{
						if (k->pNext == NULL)
						{
							foW1 << k->tu;
							foT1 << k->loaitu;
							foM1 << k->nghia;
							foE1 << k->info.data;
						}
						else
						{
							foW1 << k->tu << ' ';
							foT1 << k->loaitu << ' ';
							foM1 << k->nghia << '@';
							foE1 << k->info.data << '@';
						}
					}
					foW1.close();
					foT1.close();
					foM1.close();
					foE1.close();
				}
				else
				{
					break;
				}
			}
		}
}

void xoaNodeCoKhoaBatKy(LIST &l, string tu)
{

	if (l.pHead == NULL)
	{
		return;
	}

	if (l.pHead->tu == tu)
	{
		xoaDau(l);
		return;
	}

	if (findTail(l)->tu == tu)
	{
		xoaCuoi(l);
		return;
	}

	NODE *g = new NODE;
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (k->tu == tu)
		{
			g->pNext = k->pNext;
			delete k;
			return;
		}
		g = k;
	}
}

void xoaCuoi(LIST &l)
{
	if (l.pHead == NULL)
	{
		return;
	}
	if (l.pHead->pNext == NULL)
	{
		xoaDau(l);
		return;
	}

	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (k->pNext == findTail(l))
		{
			delete findTail(l);
			k->pNext = NULL;
			findTail(l)->tu = k->tu;
			return;
		}
	}
}

void themVaoCuoi(LIST &l, NODE *p)
{
	if (l.pHead == NULL)
	{
		themVaoDau(l, p);
	}
	else
	{
		findTail(l)->pNext = p;
	}
}

void xoaDau(LIST &l)
{ 
	if (l.pHead == NULL)
	{
		return;
	}
	NODE *p = l.pHead;
	l.pHead = l.pHead->pNext;
	delete p;
}

void themVaoDau(LIST &l, NODE *p)
{
	if (l.pHead == NULL)
	{
		l.pHead = p;
	}
	else
	{
		p->pNext = l.pHead;
		l.pHead = p;
	}
}

bool kiemTraChuoi(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if ((s[i] < 65) || (s[i] > 90 && s[i] < 97) || (s[i] > 122))
			return false;
	}
	return true;
}

string chuanHoaChuoi(string s)
{
	string st = "";
	for (int i = 0; i < s.length(); i++)
		if (s[i] >= 65 && s[i] <= 90)
			st += char(s[i] + 32);
		else
			st += s[i];
	return st;
}
void deleteList(list &l)
{
	NODE* node = l.pHead;
	while (node != NULL)
	{
		xoaDau(l);
		node = l.pHead;
	}
	l.pTail = NULL;
}
int tapTuDien(string p) {
	return p[0] - 97;
}
bool soSanh(string input, NODE *p) {
	string tu = p->tu;	
	for (int i = 0; i < input.size(); i++) {
		if (input[i] != tu[i]) {
			return false;
		}
	}
	return true;
}

NODE* timkiem(LIST l, string input) {
	NODE *p = l.pHead;
	while (p != NULL) {
		if (soSanh(input, p)) {
			return p;
		}
		p = p->pNext;
	}	
	return NULL;
}
void inDanhSachTu(LIST l, string input) {
	NODE *tuHienTai = NULL; 
	int index = -1;
	if (input != "") {
		index = tapTuDien(input);
	}
	
	int count = 0;
	for (int i = 0; i < 26; i++) {
		if (l.pHead == NULL) continue; 
		NODE *p = l.pHead;
		if (index != -1) {
			p = timkiem(l, input);
		}
		while (true) {
			if (p == NULL) break;
			if (count == 0) {
				tuHienTai = p;
			}
			cout << endl << " " << p->tu << " ";
			count++;
			p = p->pNext;
		}
		if (index != -1) break;
		if (count >= 15 ) break;
	}
}
void gotoxy(short x, short y) {
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = {x, y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
