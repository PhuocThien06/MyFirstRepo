#include <iostream>
using namespace std;
int linearSearch(int a[], int n, int k) {
	for (int i = 0;i < n;i++) {
		if (a[i] == k) {
			return i;
		}
	}
	return -1;
}
int main() {
	int n;
	cout << "Nhap so luong phan tu cua mang: ";
	cin >> n;
	int a[100];
	for (int i = 0;i < n;i++) {
		cout << "Nhap phan tu thu " << i << " cua mang: ";
		cin >> a[i];
	}
	int k;
	cout << "Nhap so can tim: ";
	cin >> k;
	cout << linearSearch(a, n, k);
	return 0;
}