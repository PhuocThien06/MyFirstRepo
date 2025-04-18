#include <iostream>
using namespace std;
bool KiemTra(int a[], int left,int right, int x) {
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (a[mid] == x) {
			return true;
		}
		if (a[mid] < x)
			left = mid - 1;
		if (a[mid] > x)
			right = mid + 1;
	}
	return false;
}
bool KiemTraSum(int a[], int n, int target) {
	for (int i = 0;i < n;i++) {
		int temp = target - a[i];
		if (KiemTra(a, 0, n - 1,temp))
			return true;
	}
	return false;
}
int main() {
	int n;
	cout << "Nhap so phan tu cua mang: ";
	cin >> n;
	int* a = new int[n];
	for (int i = 0;i < n;i++) {
		cout << "Nhap phan tu thu " << i << " : " << endl;
		cin >> a[i];
	}
	int target;
	cout << "Nhap target: ";
	cin >> target;
	if (KiemTraSum)
		cout << "YES";
	else cout << "NO";
	return 0;
}
		
		