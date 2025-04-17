#include <iostream>
using namespace std;
bool IsSorted(int arr[], int n) {
	if (n == 0 || n == 1) {
		return true;
	}
	if (arr[0] > arr[1]) {
		return false;
	}
	return IsSorted(arr + 1, n - 1);
}
int main() {
	int arr[] = { 1,2,3,4,5 };
	int n = sizeof(arr) / sizeof(arr[0]);
	if (IsSorted)
		cout << "The array is sorted" << endl;
	else
		cout << "The array is not sorted" << endl;
	return 0;
}