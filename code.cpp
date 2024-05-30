#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include "mylib.h"

using namespace std;

void box(int x, int y, int w, int h, int t_color, int b_color, string nd);
void boxloading(int x, int y, int w, int h, int t_color, int b_color, string nd);

template<class V> class Entry {
public:
	string key; // t? c?n du?c d?ch
	V PA; // phiên âm
	V value; // t? du?c d?ch ra
	V DongNghia;// t? d?ng nghia
	size_t hash; // mã bam

	Entry(string key, V DongNghia = V(), V PA = V(), V value = V()) {
		this->key = key;
		this->value = value;
		this->PA = PA;
		this->DongNghia = DongNghia;
		hash = hashCode();
	}

	size_t hashCode() {
		size_t ma = 0;
		size_t n = key.length();
		for (size_t i = 1; i <= n; ++i) {
			ma += key[i - 1] * pow(31, n - i);
		}
		return ma;
	}
};

template<class V> class Hash {
private:
	size_t capacity;
	list<Entry<V>>* table;

public:
	Hash(size_t cap = 10) {
		if (cap <= 0) {
			capacity = 10;
		}
		else capacity = cap;
		table = new list<Entry<V>>[capacity];
	}
	size_t hashCode(size_t code) {
		return code % capacity;
	}
	void insert(string key, V DongNghia, V PA, V value) {
		strUpr(key);
		Entry<V> entry(key, DongNghia, PA, value);
		size_t index = hashCode(entry.hash);
		table[index].push_back(entry);
	}
	void strUpr(string& s) {
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] >= 'a' && s[i] <= 'z') s[i] -= 32;
		}
	}
	V TimKiem(string key) {
		strUpr(key);
		Entry<V> entry(key);
		size_t index = hashCode(entry.hash);
		for (auto i = table[index].begin(); i != table[index].end(); ++i) {
			if ((*i).hash == entry.hash) {
				return  (*i).PA + "(" + (*i).value + ")" + (*i).DongNghia;
			}
		}
		return V();
	}

	V Value(string key) {
		strUpr(key);
		Entry<V> entry(key);
		size_t index = hashCode(entry.hash);
		for (auto i = table[index].begin(); i != table[index].end(); ++i) {
			if ((*i).hash == entry.hash) {
				return  (*i).value;
			}
		}
		return V();
	}

	void setValue(string key, V newValue) {
		strUpr(key);
		Entry<V> entry(key);
		size_t index = hashCode(entry.hash);
		for (auto i = table[index].begin(); i != table[index].end(); ++i) {
			if ((*i).hash == entry.hash) {
				(*i).value = newValue;
				return;
			}
		}
	}

	void remove(string key) {
		Entry<V> entry(key);
		size_t index = hashCode(entry.hash);
		for (auto i = table[index].begin(); i != table[index].end(); i++)
		{
			if ((*i).hash == entry.hash) {
				table[index].erase(i);
				return;
			}
		}
	}

	~Hash() {
		delete[] table; // thu h?i b? nh? dã c?p phát d?ng
	}
};

bool checkAV(string s) {
	stringstream ss(s);
	string tmp;
	if (getline(ss, tmp, '_')) return true;
	return false;
}

void ChuyenHoa(string& s) {
	stringstream ss(s);
	s = "";
	getline(ss, s, '_');
	string tmp;
	while (getline(ss, tmp, '_')) s = s + " " + tmp;
}

// d?ch
void KhoiTao(Hash<string>& hashTable, string nameFile) {
	ifstream fi(nameFile);
	while (!fi.eof()) {
		string s, tmp;
		fi >> s;
		stringstream ss(s);
		string s1, s2, s3, s4;
		getline(ss, s1, '(');
		if (checkAV(s1)) {
			ChuyenHoa(s1);
		}
		getline(ss, s2, ')');
		if (checkAV(s2)) {
			ChuyenHoa(s2);
		}
		getline(ss, tmp, '/');
		getline(ss, s3, '/');
		s3 = '/' + s3;
		s3 += '/';
		getline(ss, s4, '_');
		while (getline(ss, tmp, '_')) s4 = s4 + " " + tmp;
		hashTable.insert(s1, s2, s3, s4);
	}
	fi.close();
}



bool end() {
	gotoXY(47, 16); cout << "   Bấm phím ESC để thoát!" << endl;
	gotoXY(60, 17); cout << "\n\t\t\t\t\t    Chương trình tiếp tục sau ";
	int i = 10;
	while (i > 0) {
		char key;
		if (kbhit()) {
			key = getch();
			if (key == 27) {
				system("cls");
				return true;
			}
		}
		i--;
		gotoXY(71, 18); cout << "" << i << " giây\r"; //g++ code.cpp -o code.exe && code.exe
		Sleep(1000);
	}
	return false;
}


void dich(int i) {
	Hash<string> hashTable;
	string nameFile;
	if (i == 1) {
		nameFile = "inAV.txt";
	}
	else nameFile = "inPV.txt";
	KhoiTao(hashTable, nameFile);
	system("cls");
	// list<string> xoa;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tĐANG CHẠY";
	for (int n = 0; n < 10; n++)
	{
		cout << ".";
		Sleep(90);
	}
	set<string> xoa;
	xoa.insert("#");
	system("cls");
	while (1) {
		string s;
		box(33, 3, 55, 2, 11, 9, "Nhập từ bạn cần tìm: ");
		gotoXY(68, 4); getline(cin, s);
		cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tĐANG DỊCH";
		for (int n = 0; n < 15; n++)
		{
			cout << ".";
			Sleep(50);
		}
		system("cls");
		if (xoa.find(s) == xoa.end() && hashTable.TimKiem(s) != string()) {
			string kq = hashTable.TimKiem(s);
			string nghia, phienAm, dongNghia;
			stringstream ss(kq);
			getline(ss, phienAm, '(');
			getline(ss, nghia, ')');
			getline(ss, dongNghia);
			box(21, 2, 78, 23, 11, 9, " ");
			box(25, 3, 70, 7, 11, 9, " ");
			gotoXY(28, 5); cout << "Từ của bạn: " << s;
			gotoXY(28, 6); cout << "Phiên âm: " << phienAm << endl;
			gotoXY(28, 7); cout << "Nghĩa: " << nghia << endl;
			if (dongNghia[0] != '!') {
				gotoXY(28, 8); cout << "Từ đồng nghĩa: " << dongNghia << endl;
			}

			if (end()) return;
			system("cls");
			char key;
			box(40, 10, 42, 8, 11, 9, " ");
			gotoXY(49, 12);
			cout << "Bấm vào 1 để có thể xóa từ ";
			gotoXY(58, 13);
			cout << s;
			gotoXY(48, 15); cout << "Nhấn enter để tiếp tục dịch!";
			key = getch();
			if (key == 1 + '0'){
				system("cls");
				hashTable.remove(s);
				xoa.insert(s);
				cout << "Xóa thành công! " << s;
				Sleep(900);
			}
			// cout<<"b?m 1 d? nghe phiên âm";
			//FILE *FPA = fopen("1.mp3", "r");
		}
		else
		{
			box(37, 8, 45, 12, 11, 9, " ");
			gotoXY(60, 6); cout << "\n\n\n\n\n\t\t\t\t\t      Không tìm thấy từ bạn muốn!" << endl;
			if (end()) return;
			system("cls");
			box(40, 10, 42, 8, 11, 9, " ");
			gotoXY(49, 12);
			cout << "Bấm vào 1 để có thể thêm từ ";
			gotoXY(58, 13);
			cout << s;
			gotoXY(48, 15);
			cout << "Nhấn enter để tiếp tục dịch!";
			char key;
			key = getch();
			if (key == 1 + '0') {
				system("cls");
				string s1, s2, s3;
				box(25, 3, 70, 7, 11, 9, " ");
				gotoXY(28, 5);
				cout << "đồng nghĩa của (" << s << ") nếu không có thì nhấn !: "; getline(cin, s1);
				gotoXY(28, 6);
				cout << "Phiên âm: "; getline(cin, s2);
				gotoXY(28, 7);
				cout << "nghĩa của từ: "; getline(cin, s3);
				hashTable.insert(s, s1, s2, s3);
				if (xoa.find(s) != xoa.end()) xoa.erase(s);
			}
		}
		system("cls");
	}
}


//                     ===================================game=================================== 

int KhoiTaoGame(Hash<string>& hashTable, string nameFile, string arrayTD[]) {
	ifstream fi(nameFile);
	int d = 0;
	while (!fi.eof()) {
		string s, tmp;
		fi >> s;
		stringstream ss(s);
		string s1, s2, s3, s4;
		getline(ss, s1, '(');
		if (checkAV(s1)) {
			ChuyenHoa(s1);
		}
		arrayTD[d++] = s1;
		getline(ss, s2, ')');
		if (checkAV(s2)) {
			ChuyenHoa(s2);
		}
		getline(ss, tmp, '/');
		getline(ss, s3, '/');
		s3 = '/' + s3;
		s3 += '/';
		getline(ss, s4, '_');
		while (getline(ss, tmp, '_')) s4 = s4 + " " + tmp;
		hashTable.insert(s1, s2, s3, s4);
	}
	fi.close();
	return d;
}

int chuanBiGame(Hash<string>& hashTable, int i, string arrayTD[]) {
	string nameFile;
	if (i == 1) {
		nameFile = "inAV.txt";
	}
	else nameFile = "inPV.txt";
	int sl = KhoiTaoGame(hashTable, nameFile, arrayTD);
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tĐANG CHẠY";
	for (int n = 0; n < 10; n++)
	{
		cout << ".";
		Sleep(90);
	}
	system("cls");
	return sl;
}

void EndGame(int slDung, int slSai) {

	int tong = slDung + slSai;
	float _ptDung = (float)slDung / tong * 100, _ptSai = 100.0 - _ptDung;
	box(40, 10, 42, 10, 11, 9, " ");
	gotoXY(45, 12); cout << "Tổng số lượng câu hỏi vừa chơi: " << tong << endl;
	gotoXY(45, 13); cout << "Bạn đã trả lời đúng(" << _ptDung << "%): " << slDung << endl;
	gotoXY(45, 14); cout << "Bạn đã trả lời sai(" << _ptSai << "%): " << slSai << endl;

	if (_ptDung > 80) {
		gotoXY(45, 15); cout << "bạn rất suất sắc" << endl;
	}
	else if (_ptDung > 50) {
		gotoXY(45, 15); cout << "bạn có sự tiến bộ!!!" << endl;
	}
	else {
		gotoXY(45, 15); cout << "bạn cần có sự cố gắng hơn!!!" << endl;
	}
	if (end()) return;
	system("cls");
	return;

}

string great(int i) {
	switch (i) {
	case 1:
	case 2:gotoXY(52, 13);
		return " BẠN LÀM TỐT LẮM!";
	case 3:
	case 4:gotoXY(52, 13);
		return " BẠN THẬT XUẤT SẮC!";
	case 5:
	case 6:gotoXY(52, 13);
		return " BẠN QUÁ ĐẲNG CẤP";
	}gotoXY(56, 13);
	return "   VICTORY";

}

// void troGiup5050(char dapAn){

// }
// ================================================================================================================ edit bay gio================================
void troGiupNguoiThan(char dapAn) {
	char choose;
	while (1) {
		cout << "bạn muốn gọi cho ai ???" << endl;
		cout << "1. messi" << endl;
		cout << "2. ronaldo" << endl;
		cout << "Chọn: "; cin >> choose;
		if (choose) {
			cout << "Messi : ";
		}
		else cout << "Ronaldo : ";
		cout << "tôi nghĩ là đáp án: " << dapAn;
		int i = 10;
		while (i > 0) {
			i--;
			gotoXY(60, 18); cout << "Trởi lại câu hỏi sau: ";
			gotoXY(83, 18); cout << "" << i << " giây\r"; //g++ code.cpp -o code.exe && code.exe
			Sleep(1000);
		}
		system("cls");
		return;
	}
}

void hoiYKienKhanGia(char dapAn) {
	int kq = dapAn - 'A';
	int a[4];
	srand(time(NULL));
	a[kq] = 50 + rand() % (25 - 0 + 1);
	int conLai = 100 - a[kq];
	for (int i = 0; i < 4; ++i) {
		if (i != kq) {
			a[i] = rand() % (conLai - 0 + 1);
			conLai -= a[i];
		}
	}
	for (int i = 0; i < 4; ++i) {
		cout << "Đáp án " << char(i + 'A') << "có " << a[i] << "%" << endl;
	}
	int i = 10;
	while (i > 0) {
		i--;
		gotoXY(60, 18); cout << "Trởi lại câu hỏi sau: ";
		gotoXY(83, 18); cout << "" << i << " giây\r"; //g++ code.cpp -o code.exe && code.exe
		Sleep(1000);
	}
	system("cls");
}

int troGiup5050(char dapAn) {
	int xoa = 0;
	int kq = dapAn - 'A';
	srand(time(NULL));
	int xoaDA1 = -1;
	while (xoa < 10) {
		int random = rand() % (3 - 0 + 1);
		while (random == kq || xoaDA1 == random) random = rand() % (3 - 0 + 1);
		xoaDA1 = random;
		xoa = xoa * 10 + random;
	}
	return xoa;
}

int TroGiup(char dapAn, int& hetTroGiup) {
	system("cls");
	char key;
	int n = hetTroGiup;
	set<int> xoaTroGiup;
	xoaTroGiup.insert(4);
	while (n >= 1) {
		xoaTroGiup.insert(n % 10);
		n /= 10;
	}
	while (1) {
		box(47, 9, 30, 2, 11, 9, "");
		gotoXY(50, 10);
		cout << "1. 50 50"; 
		if (xoaTroGiup.find(1) != xoaTroGiup.end()){
			gotoXY(80, 10); cout << " X" << endl;
		}
		box(47, 12, 30, 2, 11, 9, "");
		gotoXY(50, 13);
		cout << "2. Gọi cho người thân."; 
		if (xoaTroGiup.find(2) != xoaTroGiup.end()) {
			gotoXY(80, 13); cout << " X" << endl;
		}
		box(47, 15, 30, 2, 11, 9, "");
		gotoXY(50, 16);
		cout << "3. Hỏi ý kiến khán giả."; 
		if (xoaTroGiup.find(3) != xoaTroGiup.end()){
			gotoXY(80, 16); cout << " X" << endl; 
		}
		box(47, 18, 30, 2, 11, 9, "");
		gotoXY(50, 19);
		cout << "chọn: "; cin >> key;
		if (key == 1 + '0' && xoaTroGiup.find(key - '0') == xoaTroGiup.end()) {
			system("cls");
			hetTroGiup = hetTroGiup * 10 + (key - '0');
			return troGiup5050(dapAn);
		}
		else if (key == 2 + '0' && xoaTroGiup.find(key - '0') == xoaTroGiup.end()) {
			troGiupNguoiThan(dapAn);
			hetTroGiup = hetTroGiup * 10 + (key - '0');
			system("cls");
			return 0;
		}
		else if (key == 3 + '0' && xoaTroGiup.find(key - '0') == xoaTroGiup.end()) {
			hoiYKienKhanGia(dapAn);
			hetTroGiup = hetTroGiup * 10 + (key - '0');
			system("cls");
			return 0;
		}
		system("cls");
	}
}
//====================================================================================================================
void startGame1(int choose) {
	Hash<string> hashTable;
	string arrayTD[5000];
	int hetTroGiup = 0;
	int sl = chuanBiGame(hashTable, choose, arrayTD);
	int d = 0;
	int slDung = 1, slSai = 0;
	while (1) {
		system("cls");
		srand(time(NULL));
		int a[4];
		a[0] = rand() % (sl - 0 + 1);
		string tuHoi = hashTable.Value(arrayTD[a[0]]);

		for (int i = 1; i < 4; ++i) {
			a[i] = rand() % (sl - 0 + 1);
			while (a[i] == a[0]) a[i] = rand() % (sl - 0 + 1);
		}
		int kq = rand() % (3 - 0 + 1), dem = 1;
		string in[4];
		in[kq] = arrayTD[a[0]];

		for (int i = 0; i < 4; ++i) {
			if (i != kq) in[i] = arrayTD[a[dem++]];
		}
		char key;
		bool ok = false;
		int help = 0;
		while (!ok) {
			//box chứa từ điển
			box(20, 2, 80, 4, 11, 9, " ");
			gotoXY(22, 4); cout << "Câu " << slSai + slDung;
			gotoXY(29, 4); cout << "Nghĩa của từ: " << tuHoi << endl;
			char out = 'A';
			if (help != 0) {
				in[help / 10] = "";
				in[help % 10] = "";
			}
			for (int i = 0; i < 4; ++i) {
				if (i == 0) {
					//box option 1 trò chơi
					box(47, 9, 30, 2, 11, 9, "");
					gotoXY(50, 10); cout << out++ << "." << in[i] << endl;

				}if (i == 1) {
					//box option 1 trò chơi
					box(47, 12, 30, 2, 11, 9, "");
					gotoXY(50, 13); cout << out++ << "." << in[i] << endl;
				}if (i == 2) {
					//box option 1 trò chơi
					box(47, 15, 30, 2, 11, 9, "");
					gotoXY(50, 16); cout << out++ << "." << in[i] << endl;
				}if (i == 3) {
					//box option 1 trò chơi
					box(47, 18, 30, 2, 11, 9, "");
					gotoXY(50, 19); cout << out++ << "." << in[i] << endl;
				}
			}
			box(47, 23, 30, 2, 11, 9, "");
			//system("cls");
			if (hetTroGiup < 100) {
				gotoXY(45, 27); cout << "Bạn có thể dùng sự trợ giúp khi nhấn .";
			}
			gotoXY(53, 24); cout << "Bạn chọn đáp án: ";
			cin >> key;
			system("cls");
			if (key == '.') help = TroGiup(kq + 'A', hetTroGiup);
			else if (key == char(kq + 'A') || char(key - 32) == char(kq + 'A')) {
				box(40, 12, 42, 10, 11, 9, " ");
				gotoXY(52, 14); cout << "Bạn đã trả lời đúng" << endl;
				++d;
				++slDung;
				cout << great(d) << endl; // background đẹp xíu nha
				ok = true;
				help = 0;
			}
			else if ((key >= 'A' && key <= 'D') || (key >= 'a' && key <= 'd')) {
				box(40, 12, 42, 10, 11, 9, " ");
				gotoXY(52, 14); cout << "Bạn trả lời sai rồi!!!";
				gotoXY(54, 16); cout << "Đáp án phải là: " << char(kq + 'A') << endl;
				d = 0;
				++slSai;
				ok = true;
				help = 0;
			}
			else {
				system("cls");
				help = 0;
			}
			if (ok) //box(33, 7, 65, 16, 11, 9, " ");  
				gotoXY(39, 9); cout << " ";// cout << in[kq] << " nghĩa là: " << tuHoi << endl;
		}
		gotoXY(48, 19); cout << "Nhấp ENTER để tiếp tục chơi!!!" << endl;
		gotoXY(51, 20); cout << "Bấm phím ESC để thoát." << endl;
		key = getch();
		if (key == 27) {
			system("cls");
			EndGame(slDung - 1, slSai);
			return;
		}
		system("cls");
	}
}
void strUpr(string& s) {
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] >= 'a' && s[i] <= 'z') s[i] -= 32;
	}
}

bool strCmp(string s1, string s2) {
	if (s1.length() != s2.length()) return false;
	strUpr(s1);
	strUpr(s2);
	for (int i = 0; i < s1.size(); ++i) {
		if (s1[i] != s2[i]) return false;
	}
	return true;
}

void goiY(string kq) {
	int n = kq.size();
	int dau = n / 2;
	set<int> st;
	srand(time(NULL));
	while (dau != 0) {
		int i = rand() % (n - 0 + 1);
		while (st.find(i) != st.end()) {
			i = rand() % (n - 0 + 1);
		}
		st.insert(i);
		kq[i] = '_';
		--dau;
	}
	box(40, 12, 42, 10, 11, 9, " ");
	gotoXY(50, 14); cout << "gợi ý của bạn là: " << kq;
	int i = 10;
	while (i > 0) {
		i--;
		gotoXY(49, 18); cout << "Trở lại câu hỏi sau: ";
		gotoXY(70, 18); cout << "" << i << " giây\r"; //g++ code.cpp -o code.exe && code.exe
		Sleep(1000);
	}
	system("cls");
}

void startGame2(int choose) {
	Hash<string> hashTable;
	string arrayTD[5000];
	int sl = chuanBiGame(hashTable, choose, arrayTD);
	int d = 0;
	int slDung = 1, slSai = 0;
	int slGoiY = 5;
	bool check = false; // để hiển thị khi chưa sử dụng gợi ý
	while (1) { 
		srand(time(NULL));
		int kq = rand() % (sl - 0 + 1);
		string tuHoi = hashTable.Value(arrayTD[kq]);
		string s; box(22, 3, 70, 2, 11, 9, "");
		if (slGoiY != 0 && !check) {
			box(40, 12, 42, 10, 11, 9, " ");
			gotoXY(49, 14);
			cout << "bạn có " << slGoiY << " lần được gợi ý!";
			gotoXY(47, 16);
			cout<<" bấm . để được sự gợi ý";
		}
		// if (slGoiY == 0) cin.ignore();
		gotoXY(15, 4); cout<< " Câu " << slDung + slSai;
		gotoXY(24, 4); cout << "Nghĩa của: " << tuHoi << " --> "; getline(cin, s);
		if (s[0] == '.') {
			goiY(arrayTD[kq]);
			--slGoiY;
			check = true;
			box(22, 3, 70, 2, 11, 9, "");
			gotoXY(24, 4); cout << "Nghĩa của: " << tuHoi << " --> "; getline(cin, s);
		}
		system("cls");
		if (strCmp(s, arrayTD[kq])) {
			box(37, 8, 45, 13, 11, 9, " ");
			gotoXY(47, 10); cout << "  Câu trả lời chính xác!!!" << endl;
			++d;
			++slDung;
			cout << great(d) << endl;
			check = false;
		}
		else {
			box(37, 8, 45, 13, 11, 9, " ");
			gotoXY(45, 10); cout << "Thật tiếc!Bạn chọn nhầm rùi!!!";
			gotoXY(46, 12); cout << "Nghĩa của nó phải là: " << arrayTD[kq] << endl;
			d = 0;
			++slSai;
			check = false;
		}
		gotoXY(48, 17); cout << "Nhấp ENTER để tiếp tục chơi!!!" << endl;
		gotoXY(48, 18); cout << "Bấm phím ESC để thoát." << endl;
		char key;
		key = getch();
		if (key == 27) {
			system("cls");
			EndGame(slDung - 1, slSai);
			return;
		}
		system("cls");
	}
}

void menuGame() {
	while (1) {
		char choose;
		//box chứa menu
		box(39, 5, 48, 2, 11, 9, " ");
		//box chứa option1 
		box(47, 9, 31, 2, 11, 9, " ");
		//box chứa opton2
		box(47, 12, 31, 2, 11, 9, " ");
		//box chứa option 3
		box(47, 15, 31, 2, 11, 9, " ");
		gotoXY(44, 6); cout << "\t\t MENU TRÒ CHƠI";
		gotoXY(49, 10); cout << "1. Trò chơi chọn đáp án đúng" << endl;
		gotoXY(49, 13); cout << "2. Trò chơi tìm nghĩa" << endl;
		gotoXY(49, 16); cout << "Bạn chọn: ";
		choose = getch();
		system("cls");
		char start;
		while (1) {
			//box chứa option1 
			box(47, 9, 31, 2, 11, 9, " ");
			//box chứa opton2
			box(47, 12, 31, 2, 11, 9, " ");
			//box chứa option 3
			box(47, 15, 31, 2, 11, 9, " ");
			gotoXY(49, 10); cout << "1. Việt sang Anh " << endl;
			gotoXY(49, 13); cout << "2. Việt sang Pháp" << endl;
			gotoXY(49, 16); cout << "Bạn chọn: ";
			start = getch();
			if (start == 27) return;
			if (start != '1' && start != '2') {
				system("cls");
				continue;
			}
			break;
		}
		cout << "start";
		switch (choose) {
		case '1':
			startGame1(start - '0');
			break;
		case '2':
			startGame2(start - '0');
			break;
		}
	}
}


void menu() {
	while (1) {
		char choose;
		box(21, 2, 78, 23, 11, 9, " ");
		box(27, 4, 66, 19, 11, 9, " ");
		box(39, 5, 40, 2, 11, 9, " ");
		box(47, 8, 25, 2, 11, 9, " ");
		box(47, 11, 25, 2, 11, 9, " ");
		box(47, 14, 25, 2, 11, 9, " ");
		box(47, 17, 25, 2, 11, 9, " ");
		box(47, 20, 25, 2, 11, 9, " ");
		gotoXY(43, 6); cout << "============= Từ Điển =============" << endl;
		gotoXY(49, 9); cout << "1. Anh sang Việt" << endl;
		gotoXY(49, 12); cout << "2. Pháp sang Việt" << endl;
		gotoXY(49, 15); cout << "3. Trò chơi " << endl;
		gotoXY(49, 18); cout << "ESC. Thoát" << endl;
		gotoXY(49, 21); cout << "Bạn chọn: "; choose = getch();
		if (choose == 27) {
			return;
		}
		switch (choose) {

		case '1':
			dich(choose - '0');
			system("cls");
			break;
		case '2':
			system("cls");
			dich(choose - '0');
			system("cls");
			break;
		case '3':
			system("cls");
			menuGame();
			system("cls");
		}
	}
}

void box(int x, int y, int w, int h, int t_color, int b_color, string nd)
{

	textcolor(b_color);
	for (int iy = y + 1; iy <= y + h - 1; iy++) {
		for (int ix = x + 1; ix <= x + w - 1; ix++)
		{
			gotoXY(ix, iy); cout << " ";
		}
	}
	//---------------------ve khung----------------

	SetColor(t_color);//update
	for (int ix = x; ix <= x + w; ix++)
	{
		gotoXY(ix, y);
		cout << "\u2500";
		gotoXY(ix, y + h);
		cout << "\u2500";
	}
	for (int iy = y; iy <= y + h; iy++)
	{
		gotoXY(x, iy);
		cout << "\u2502";
		gotoXY(x + w, iy);
		cout << "\u2502";
	}
	//noi dung hien thi
	gotoXY(x + 14, y + 1)
		; cout << nd;

	//goc tren trai
	gotoXY(x, y); cout << "\u250C";
	//goc tren phai
	gotoXY(x + w, y); cout << "\u2510";
	//goc duoi trai
	gotoXY(x, y + h); cout << "\u2514";
	//goc duoi phai
	gotoXY(x + w, y + h); cout << "\u2518";
}
void boxloading(int x, int y, int w, int h, int t_color, int b_color, string nd)
{
	system("cls");
	textcolor(b_color);
	for (int iy = y + 1; iy <= y + h - 1; iy++) {
		for (int ix = x + 1; ix <= x + w - 1; ix++)
		{
			gotoXY(ix, iy); cout << " ";
		}
	}
	//---------------------ve khung----------------

	SetColor(t_color);//update
	for (int ix = x; ix <= x + w; ix++)
	{
		gotoXY(ix, y);
		cout << "\u2500";
		gotoXY(ix, y + h);
		cout << "\u2500";
	}
	for (int iy = y; iy <= y + h; iy++)
	{
		gotoXY(x, iy);
		cout << "\u2502";
		gotoXY(x + w, iy);
		cout << "\u2502";
	}
	//noi dung hien thi
	box(21, 2, 78, 23, 11, 9, "");
	box(37, 5, 45, 12, 11, 9, "");
	gotoXY(x + 14, y + 1); cout << nd;

	//goc tren trai
	gotoXY(x, y); cout << "\u250C";
	//goc tren phai
	gotoXY(x + w, y); cout << "\u2510";
	//goc duoi trai
	gotoXY(x, y + h); cout << "\u2514";
	//goc duoi phai
	gotoXY(x + w, y + h); cout << "\u2518";

	//noi dung giao dien
	gotoXY(31, 7); cout << "\t\t    ================================";
	gotoXY(33, 10); cout << "\t\t\t TỪ ĐIỂN";
	gotoXY(31, 13); cout << "\t\t    ================================";
	gotoXY(31, 21); cout << "\t\t\t   ĐANG TẢI TÀI NGUYÊN\n\n";

	for (int i = 0; i <= 99; i++)
	{
		cout << "\t\t\t\t\t\t\t" << "   " << i << "%\r";
		Sleep(20);
	}
	system("cls");
}
void cover()
{


	box(21, 2, 78, 23, 11, 9, " ");
	cout << endl;
	gotoXY(31, 7); cout << "\t\t      ______________________________\n\n";
	gotoXY(31, 9); cout << "\t\t\t TECH DICTIONARY OF VUONG";
	gotoXY(31, 11); cout << "\t\t      ______________________________";
	gotoXY(27, 14); cout << "\t\t  	 WELCOM TO MY DICTIONARY";
	gotoXY(31, 16); cout << "\t\t       Thanks for using my service";
	cout << endl << endl;

	cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t      Copyrights 2022, Vuong Tech Dictionary, All Rights Resserved. ";
	for (int n = 0; n < 20; n++)
	{
		cout << ".";
		Sleep(100);
	}
}

int main() {
	SetConsoleOutputCP(65001);
	system("cls");
	boxloading(20, 1, 80, 25, 9, 9, "");
	cover();
	system("cls");
	menu();
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t    CẢM ƠN CÁC BẠN ĐÃ SỬ DỤNG DỊCH VỤ!!!" << char(3);
}
