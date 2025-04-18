#include "Ham.h"
// SelectionSort
int findmin(int a[], int low, int n) {
	int min = low;
	for (int i = low + 1; i < n;i++) {
		++solansosanh;
		++solansosanh;
		if (a[i] < a[min])
			min = i;
	}
	++solansosanh;
	return min;
}
void swap(int& i, int& j) {
	int temp = i;
	i = j;
	j = temp;
}
void SelectionSort(int a[], int n) {
	for (int i = 0; i < n - 1;i++) {
		++solansosanh;
		int min = findmin(a, i, n);
		swap(a[i], a[min]);
	}
	++solansosanh;
}
//InsertionSort
void InsertionSort(int a[], int n) {
	for (int i = 1;i < n;i++) {
		++solansosanh;
		int key = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > key) {
			++solansosanh;
			a[j + 1] = a[j];
			j = j - 1;
		}
		++solansosanh;
		a[j + 1] = key;
	}
	++solansosanh;
}
//Bubble Sort
void BubbleSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0;j < n - 1 - i; j++) {
			++solansosanh;
			++solansosanh;
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
			}
		}
		++solansosanh;
	}
	++solansosanh;
}
//Heap Sort
void heapify(int a[], int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (++solansosanh && left <n && a[left]> a[largest])
		largest = left;
	if (++solansosanh && right < n && a[right] > a[largest])
		largest = right;
	if (++solansosanh && largest != i) {
		swap(a[i], a[largest]);
		heapify(a, n, largest);
	}
}
void HeapSort(int a[], int n) {
	for (int i = n / 2 - 1; i >= 0;i--) {
		++solansosanh;
		heapify(a, n, i);
	}
	++solansosanh;
	for (int i = n - 1; i > 0;i--) {
		++solansosanh;
		swap(a[0], a[i]);
		heapify(a, i, 0);
	}
	++solansosanh;
}
//Merge Sort
void merge(int arr[], int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;
	int* L = new int[n1];
	int* R = new int[n2];
	for (int i = 0; i < n1; i++) {
		++solansosanh;
		L[i] = arr[left + i];
	}
	++solansosanh;
	for (int j = 0; j < n2; j++) {
		++solansosanh;
		R[j] = arr[mid + 1 + j];
	}
	++solansosanh;
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		++solansosanh;
		++solansosanh;
		if (L[i] <= R[j]) {
			arr[k++] = L[i++];
		}
		else {
			arr[k++] = R[j++];
		}
	}
	++solansosanh;
	while (i < n1) {
		++solansosanh;
		arr[k++] = L[i++];
	}
	++solansosanh;
	while (j < n2) {
		++solansosanh;
		arr[k++] = R[j++];
	}
	++solansosanh;
	delete[] L;
	delete[] R;
}
void MergeSort(int arr[], int left, int right) {
	if (++solansosanh && left < right) {
		int mid = left + (right - left) / 2;
		MergeSort(arr, left, mid);
		MergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}
//Quick Sort
void QuickSort(vector<int>& a, int low, int high) {
	if (++solansosanh && low < high) {
		int pivotIndex = partition(a, low, high);
		QuickSort(a, low, pivotIndex - 1);
		QuickSort(a, pivotIndex + 1, high);
	}
}
int partition(vector<int>& a, int low, int high) {
	int randomIndex = low + rand() % (high - low + 1);
	swap(a[randomIndex], a[high]); 
	int pivot = a[high];
	int i = low - 1;
	for (int j = low; j < high; j++) {
		++solansosanh;
		++solansosanh;
		if (a[j] < pivot) {
			i++;
			swap(a[i], a[j]);
		}
	}
	++solansosanh;
	swap(a[i + 1], a[high]);
	return i + 1;
}
//Radix Sort
void countingSort(vector<int>& arr, int exp) {
	int n = arr.size();
	vector<int> output(n);
	int count[10] = { 0 };
	for (int i = 0; i < n; i++) {
		++solansosanh;
		count[(arr[i] / exp) % 10]++;
	}
	++solansosanh;
	for (int i = 1; i < 10; i++) {
		++solansosanh;
		count[i] += count[i - 1];
	}
	++solansosanh;
	for (int i = n - 1;i >= 0; i--) {
		++solansosanh;
		int digit = (arr[i] / exp) % 10;
		output[count[digit] - 1] = arr[i];
		count[digit]--;
	}
	++solansosanh;
	for (int i = 0; i < n; i++) {
		++solansosanh;
		arr[i] = output[i];
	}
	++solansosanh;
}
void RadixSort(vector<int>& arr) {
	int maxNum = *max_element(arr.begin(), arr.end());
	for (int exp = 1; maxNum / exp > 0; exp *= 10) {
		++solansosanh;
		countingSort(arr, exp);
	}
	++solansosanh;
}