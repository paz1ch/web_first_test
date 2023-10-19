#include <iostream>
using namespace std;
static int preArray[10];
static int page_fault[100];
static int number_page_fault = 1;

int Is_in_preArray(int page, int value) {
	for (int i = 0; i < page; i++) {
		if (value == preArray[i]) return 1;
	}
	return -1;
}


int Farest_Element(int *ref, int pivot, int page) {
	int min = pivot;
	int vt;
	for (int i = 0; i < page; i++) {
		int j;
		for (j = pivot - 1; j >= 0; j--) {
			if (preArray[i] == ref[j]) {
				if (j < min) {
					min = j;
					vt = i;
				}
			break;
			}

		}
		if (j == pivot)
		return i;
	}
	return vt;
}

int Farest_Element_Oppsite(int *ref, int pivot, int page, int n) {
	int max = pivot;
	int flag[10];
	for (int i = 0; i < page; i++) {
		flag[i] = false;
	}
	int vt = -1;
	for (int i = 0; i < page; i++) {
		for (int j = pivot + 1; j < n; j++) {
			if (preArray[i] == ref[j]) {
				if (j > max) {
					max = j;
					vt = i;
				}
				flag[i] = true;
				break;
			}

		}
	}
	
	for (int i = 0; i < page; i++) {
		if (flag[i] == false) return i;
	}	
	return vt;	
}

void Print(int total_page[10][100], int n, int page, int ref[100]) {
	for (int i = 0; i < n; i++) {
		cout << ref[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < page; i++) {
		for (int j = 0; j < n; j++) {
			if (total_page[i][j] != -1) {
				cout << total_page[i][j] << " ";
			}
			else {
				cout << "  ";
			}
			
		}
		cout << endl;
	}
	for (int i = 0; i < n; i++) {
		if (page_fault[i] == 1) cout << "* ";
		else {
			cout << "  ";
		}
	}
	cout << endl;
	cout << "Number of Page Fault: " << number_page_fault << endl;
}

void FIFO(int ref[], int n, int page)
{
	bool IsFault;
	int total_page[10][100];
	int current_page = 0;
	for (int i = 0; i < page; i++) {
		if (i == 0) { total_page[i][0] = ref[0]; }
		else {
			total_page[i][0] = -1;
		}
	}
	page_fault[0] = 1;

	for (int j = 1; j < n; j++) {
		for (int i = 0; i < page; i++) {
			total_page[i][j] = total_page[i][j-1];
			preArray[i] = total_page[i][j - 1];
		}
		if (Is_in_preArray(page, ref[j]) != -1) {
			page_fault[j] = -1;
		}
		else {
			current_page++;
			if (current_page == page) current_page = 0;
			total_page[current_page][j] = ref[j];
			page_fault[j] = 1;
			number_page_fault++;
			
		}
	}
	Print(total_page, n, page, ref);
}

void OPT(int ref[], int n, int page)
{
	bool IsFault;
	int total_page[10][100];
	int current_page = 0;
	for (int i = 0; i < page; i++) {
		if (i == 0) { total_page[i][0] = ref[0]; }
		else {
			total_page[i][0] = -1;
		}
	}
	page_fault[0] = 1;

	for (int j = 1; j < n; j++)
	{

		for (int i = 0; i < page; i++) {
			total_page[i][j] = total_page[i][j - 1];
			preArray[i] = total_page[i][j - 1];
		}
		///////
		if (Is_in_preArray(page, ref[j]) != -1) {
			page_fault[j] = 0;
		}
		else {
			if (j < page) {
				current_page++;
				total_page[current_page][j] = ref[j];
			}
			else {
				cout<<endl;
				int pivot = Farest_Element(ref, j, page);
				total_page[pivot][j] = ref[j];
			}
			page_fault[j] = 1;
			number_page_fault++;
		}
		/////
	}
	Print(total_page, n, page, ref);
}

void LRU(int ref[], int n, int page)
{
	bool IsFault;
	int total_page[10][100];
	int current_page = 0;
	for (int i = 0; i < page; i++) {
		if (i == 0) { total_page[i][0] = ref[0]; }
		else {
			total_page[i][0] = 0;
		}
	}
	page_fault[0] = 1;

	for (int j = 1; j < n; j++)
	{

		for (int i = 0; i < page; i++) {
			total_page[i][j] = total_page[i][j - 1];
			preArray[i] = total_page[i][j - 1];
		}
		///////
		if (Is_in_preArray(page, ref[j]) != -1) {
			page_fault[j] = 0;
		}
		else {
			if (j < page) {
				current_page++;
				total_page[current_page][j] = ref[j];
			}
			else {

				int pivot = Farest_Element_Oppsite(ref, j, page, n);
				total_page[pivot][j] = ref[j];
			}
			page_fault[j] = 1;
			number_page_fault++;
		}
		/////
	}
	Print(total_page, n, page, ref);
}


int main() {
	int page; int temp;
	int ref[100];
	int n;
	freopen("test1.txt","r",stdin);
	cout << "--- Page Replacement algorithm ---" << endl;
	cout << "Nhap so luong: "; cin >> n;
	cout << "Nhap danh sach trang: ";
	for (int i = 0; i < n; i++) {
		cin >> ref[i];
	}

	cout << "--- Page Replacement algorithm ---" << endl;
	cout << "Input page frames: "; cin >> page;
	cout << "--- Select algorithm ---" << endl;
	cout << "1. FIFO algorithm" << endl;
	cout << "2. OPT algorithm" << endl;
	cout << "3. LRU algorithm" << endl;
	cout << "--- Enter input ---" << endl;
	
	cin >> temp;
	freopen("test2.txt","w",stdout);
	cout << "--- Page Replacement algorithm--- " << endl;
	switch (temp) {
	case 1:
		FIFO(ref, n, page);
		break;
	case 2:
		OPT(ref, n, page);
		break;
	case 3:
		LRU(ref, n, page);
		break;
	}
	return 0;
}