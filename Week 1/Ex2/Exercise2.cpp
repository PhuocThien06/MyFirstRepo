#include <iostream>
using namespace std;
int factorial(int n) {
	if (n <= 1)return 1;
	return n * factorial(n-1);
}
int main() {
	int n;
	cout << "Nhap n: ";
	cin >> n;
	int kq = 1;
	cout << factorial(n);
	return 0;
}