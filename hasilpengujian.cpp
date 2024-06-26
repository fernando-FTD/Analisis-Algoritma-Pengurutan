#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#include <functional>

using namespace std;

// Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

// Insertion Sort
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(arr[min_idx], arr[i]);
    }
}

// Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r)
        return;

    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

// Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

template<typename Func>
long long measureTime(Func sortFunc, vector<int>& arr) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

int main() {
    vector<int> sizes = {10, 100, 500, 1000, 10000};
    ofstream results("sorting_results.csv");

    results << "Size,Type,BubbleSort,InsertionSort,SelectionSort,MergeSort,QuickSort\n";

    for (int size : sizes) {
        vector<int> arr_random(size);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, size);

        for (int& x : arr_random)
            x = dis(gen);

        vector<int> arr_reverse = arr_random;
        sort(arr_reverse.begin(), arr_reverse.end(), greater<int>());

        vector<int> arr_sorted = arr_random;
        sort(arr_sorted.begin(), arr_sorted.end());

        // Data Acak
        results << size << ",Random,";
        {
            vector<int> arr_copy = arr_random;
            results << measureTime(bubbleSort, arr_copy) << ",";
        }
        {
            vector<int> arr_copy = arr_random;
            results << measureTime(insertionSort, arr_copy) << ",";
        }
        {
            vector<int> arr_copy = arr_random;
            results << measureTime(selectionSort, arr_copy) << ",";
        }
        {
            vector<int> arr_copy = arr_random;
            results << measureTime([&](vector<int>& a) { mergeSort(a, 0, a.size() - 1); }, arr_copy) << ",";
        }
        {
            vector<int> arr_copy = arr_random;
            results << measureTime([&](vector<int>& a) { quickSort(a, 0, a.size() - 1); }, arr_copy) << "\n";
        }

        // Data Terurut Terbalik
        results << size << ",Reverse,";
        {
            vector<int> arr_copy = arr_reverse;
            results << measureTime(bubbleSort, arr_copy) << ",";
        }
        {
            vector<int> arr_copy = arr_reverse;
            results << measureTime(insertionSort, arr_copy) << ",";
        }
        {
            vector<int> arr_copy = arr_reverse;
            results << measureTime(selectionSort, arr_copy) << ",";
        }
        {
            vector<int> arr_copy = arr_reverse;
            results << measureTime([&](vector<int>& a) { mergeSort(a, 0, a.size() - 1); }, arr_copy) << ",";
        }
        {
            vector<int> arr_copy = arr_reverse;
            results << measureTime([&](vector<int>& a) { quickSort(a, 0, a.size() - 1); }, arr_copy) << "\n";
        }

        // Data Sudah Terurut
        results << size << ",Sorted,";
        {
            vector<int> arr_copy = arr_sorted;
            results << measureTime(bubbleSort, arr_copy) << ",";
        }
        {
            vector<int> arr_copy = arr_sorted;
            results << measureTime(insertionSort, arr_copy) << ",";
        }
        {
            vector<int> arr_copy = arr_sorted;
            results << measureTime(selectionSort, arr_copy) << ",";
        }
        {
            vector<int> arr_copy = arr_sorted;
            results << measureTime([&](vector<int>& a) { mergeSort(a, 0, a.size() - 1); }, arr_copy) << ",";
        }
        {
            vector<int> arr_copy = arr_sorted;
            results << measureTime([&](vector<int>& a) { quickSort(a, 0, a.size() - 1); }, arr_copy) << "\n";
        }
    }

    results.close();
    cout << "Results saved to sorting_results.csv" << endl;
    return 0;
}
