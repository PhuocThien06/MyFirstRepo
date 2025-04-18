#include <iostream>
using namespace std;
int minLength(int n, int a[],int target) {
	int left = 0, minlength =n+1, sum = 0;
	for (int right=0;right < n;right++) {
		sum += a[right];
		while (sum >= target) {
			minlength = min(minlength, right - left + 1);
			sum -= a[left];
			left++;
		}
	}

	if (minlength == n + 1)
		return 0;
	else return minlength;
}
int main() {
	int n;
	cout << "Nhap so phan tu cua mang: ";
	cin >> n;
	int *a = new int[n];
	for (int i = 0;i < n;i++) {
		cout << "Nhap phan tu thu " << i << " : ";
		cin >> a[i];
	}
	int target;
	cout << "Nhap muc tieu: ";
	cin >> target;
	cout << minLength(n,a,target);
	delete[] a;
	return 0;
}