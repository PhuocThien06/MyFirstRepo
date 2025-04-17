#include <iostream>
using namespace std;
void TowerOfHanoi(int n, char a, char b, char c) {
	if (n == 1) {
		cout << "Chuyen dia 1 tu: " << a << " sang " << b << endl;
		return;
	}
	TowerOfHanoi(n - 1, a, c, b);
	cout << "Chuyen dia " << n << " tu " << a << " sang " << b << endl;
	TowerOfHanoi(n - 1, c, b, a);
}
int main() {
	cout << "Nhap n: ";
	int n;
	cin >> n;
	TowerOfHanoi(n, 'A', 'B', 'C');
}
