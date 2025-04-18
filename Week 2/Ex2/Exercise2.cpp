#include <iostream>
using namespace std;
int sentinelLinearSearch(int a[], int n, int k) {
	int last = a[n - 1];
	a[n - 1] = k;
	int i = 0;
	while (a[i] != k) {
		i++;
	}
	a[n - 1] = last;
	if (i < n || a[n - 1] == k) {
		return i;
	}
	return -1;
}
int main(){
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
	cout << sentinelLinearSearch(a, n, k);
	return 0;
}