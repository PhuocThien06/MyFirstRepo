#include <iostream>
using namespace std;
bool KiemTra(int weights[], int n, int days, int capacity) {
	int dayCount = 1;
	int currentLoad = 0;
	for (int i = 0;i < n;i++) {
		if (currentLoad + weights[i] > capacity) {
			dayCount++;
			currentLoad = weights[i];
			if (dayCount > days)
				return false;
		}
		else {
			currentLoad += weights[i];
		}
	}
	return true;
}
int minCapacity(int weights[],int n,int days ) {
	int low = 0;
	int high = 0;
	for (int i = 0;i < n;i++){
		low = max(low, weights[i]);
		high += weights[i];
	}
	while (low < high) {
		int mid = low + (high - low) / 2;
		if (KiemTra(weights,n,days,mid)) {
			high = mid;
		}
		else {
			low = mid + 1;
		}
	}
	return low;
}

int main() {
	int n, days;
	cout << "Nhap so goi hang: ";
	cin >> n;
	int* weights = new int[n];
	cout << "Nhap so ngay: ";
	cin >> days;
	int t = 1;
	for (int i = 0;i < n;i++) {
		weights[i] = t;
		t++;
	}
	cout << minCapacity(weights, n, days);
	delete[] weights;
	return 0;
}