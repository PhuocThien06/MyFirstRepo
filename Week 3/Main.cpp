/*
 cd .\x64\Debug\
./main.exe -a selection-sort -i ./Input.txt -o ./Output.txt
*/
#include "Ham.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <time.h>
long long solansosanh = 0;
using namespace std;
template <class T>
void HoanVi(T& a, T& b)
{
	T x = a;
	a = b;
	b = x;
}
void GenerateRandomData(int a[], int n) {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % n;
	}
}
void GenerateSortedData(int a[], int n) {
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}
void GenerateReverseData(int a[], int n) {
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}
void GenerateNearlySortedData(int a[], int n) {
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		int r1 = rand() % n;
		int r2 = rand() % n;
		HoanVi(a[r1], a[r2]);
	}
}
void GenerateData(int a[], int n, int dataType) {
	switch (dataType)
	{
	case 0:
		GenerateRandomData(a, n);
		break;
	case 1:
		GenerateSortedData(a, n);
		break;
	case 2:
		GenerateReverseData(a, n);
		break;
	case 3:
		GenerateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}
int main(int argc, char* argv[]) {
    int m, dataType;
    cout << "Nhap so phan tu cua mang: ";
    cin >> m;
    cout << "Chon kieu du lieu (0: Ngau nhien, 1: Tang dan, 2: Giam dan, 3: Gan nhu co thu tu): ";
    cin >> dataType;
    int* a = new int[m];
    GenerateData(a, m, dataType);
    ofstream outFile("Input.txt");
    if (outFile.is_open()) {
        outFile << m << endl;
        for (int i = 0; i < m; i++)
        {
            outFile << a[i] << " ";
        }
        outFile.close();
        cout << "Du lieu da duoc ghi vao input.txt\n";
    }
    else
    {
        cout << "Khong the mo file de ghi!\n";
    }
    delete[] a;
    if (argc < 6) {
        cout << "Usage: " << argv[0] << " -a [algorithm] -i [input file] -o [output file]\n";
        return 1;
    }
    string algorithm, inputFile, outputFile;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            algorithm = argv[i + 1];
        }
        else if (strcmp(argv[i], "-i") == 0) {
            inputFile = argv[i + 1];
        }
        else if (strcmp(argv[i], "-o") == 0) {
            outputFile = argv[i + 1];
        }
    }
    // Đọc dữ liệu từ file input
    ifstream inFile(inputFile);
    if (!inFile) {
        cout << "Khong the mo file input!\n";
        return 1;
    }
    int n;
    inFile >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        inFile >> arr[i];
    }
    std::vector<int> array(arr, arr + n);
    inFile.close();
    clock_t start, end;
    start = clock();
    // Gọi thuật toán sắp xếp tương ứng
    if (algorithm == "selection-sort") {
        SelectionSort(arr, n);
    }
    else if (algorithm == "insertion-sort") {
        InsertionSort(arr, n);
    }
    else if (algorithm == "merge-sort") {
        MergeSort(arr, 0, n - 1);
    }
    else if (algorithm == "bubble-sort") {
        BubbleSort(arr, n);
    }
    else if (algorithm == "heap-sort") {
        HeapSort(arr, n);
    }
    else if (algorithm == "quick-sort") {
        QuickSort(array, 0,n - 1);
    }
    else if (algorithm == "radix-sort") {
        RadixSort(array);
    }
    else {
        cout << "Thuat toan khong hop le!\n";
        delete[] arr;
        return 1;
    }
    if (algorithm == "quick-sort" || algorithm == "radix-sort") {
        for (int i = 0; i < n; i++) {
            arr[i] = array[i];
        }
    }
    end = clock();
    double thoigianchay = double(end - start) * 1000 / CLOCKS_PER_SEC;
    cout << "Thoi gian chay: " << thoigianchay << " miligiay" << endl;
    cout << "So lan so sanh: " << solansosanh << " lan " << endl;
    // Ghi kết quả ra file output
    ofstream resultFile(outputFile);
    if (!resultFile) {
        cout << "Khong the mo file output!\n";
        delete[] arr;
        return 1;
    }
    resultFile << n << endl;
    for (int i = 0; i < n; i++) {
        resultFile << arr[i] << " ";
    }
    resultFile.close();
    cout << "Sap xep hoan tat!\n";
    delete[] arr;
    return 0;
}
