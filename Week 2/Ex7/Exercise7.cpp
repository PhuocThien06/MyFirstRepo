#include <iostream>
using namespace std;
void Sort(int a[], int n) {
	for (int i = 0;i < n - 1;i++) {
		for (int j = i + 1;j < n;j++) {
			if (a[j] < a[i]) {
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}
void Sum(int a[], int n) {
	int** result = new int* [n * n];
	int count = 0;
	for (int i = 0;i < n-2;i++) {
		if (i > 0 && a[i] == a[i - 1]) {
			continue;
		}
		int left = i + 1;
		int right = n - 1;
		while (left < right) {
			int sum = a[i] + a[left] + a[right];
			if (sum == 0) {
				result[count] = new int[3];
				result[count][0] = a[i];
				result[count][1] = a[left];
				result[count][2] = a[right];
				count++;
				while (left < right && a[left] == a[left + 1]) left++;
				while (left < right && a[right] == a[right - 1]) right--;
				left++;
				right--;
			}
			else if (sum < 0)
				left++;
			else if (sum > 0)
				right--;
		}
	}
	for (int i = 0;i < count;i++) {
		cout << "[" << result[i][0] << "," << result[i][1] << "," << result[i][2] << "]" << " , ";
		delete[] result[i];
	}
	delete[] result;
}
int main() {
	int n;
	cout << "Nhap so phan tu: ";
	cin >> n;
	int* a = new int[n];
	for (int i = 0;i < n;i++) {
		cout << "Nhap phan tu thu " << i << " : ";
		cin >> a[i];
	}
	Sort(a, n);
	Sum(a, n);
	delete[] a;
	return 0;
}