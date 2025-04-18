#pragma once
#ifndef _HAM_H_
#define _HAM_H_
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <time.h>
#include <cstdlib> 
using namespace std;
extern long long solansosanh;
int findmin(int a[], int low, int n);
void swap(int& i, int& j);
void SelectionSort(int a[],int n);
void InsertionSort(int a[], int n); 
void BubbleSort(int a[], int n);
void heapify(int a[], int n, int i);
void HeapSort(int a[], int n);
void merge(int arr[], int left, int mid, int right);
void MergeSort(int arr[], int left, int right);
int partition(vector<int>& a, int low, int high);
void QuickSort(vector<int>& a, int low, int high);
void countingSort(vector<int>& arr, int exp);
void RadixSort(vector<int>& arr);
#endif // !
