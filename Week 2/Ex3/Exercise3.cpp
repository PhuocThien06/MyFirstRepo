#include <iostream>
using namespace std;
int findMin(int nums[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] > nums[right]) {
            left = mid + 1;  
        }
        else {
            right = mid;  
        }
    }
    return nums[left];  
}
int main() {
    int n;
    cout << "Nhap so luong phan tu: ";
    cin >> n;
    int* nums = new int[n];
    cout << "Nhap cac phan tu cua mang: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    cout << "Phan tu nho nhat: " << findMin(nums, n) << endl;
    delete[] nums;
    return 0;
}
