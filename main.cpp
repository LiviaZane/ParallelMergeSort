#include <iostream>
#include <cstdlib>  // for rand()
#include <chrono>   // for time mesurement

using namespace std;

void merge(int arr[], int start_index, int middle_index, int end_index) {
    int merged_arr[end_index - start_index + 1];
    int i = start_index, j = middle_index + 1, k = 0;
    while (i <= middle_index && j <= end_index) {
        if (arr[i] <= arr[j]) {
            merged_arr[k] = arr[i];
            ++i;
        } else {
            merged_arr[k] = arr[j];
            ++j;
        }
        ++k;
    }
    while (i <= middle_index) {
        merged_arr[k] = arr[i];
        ++i;
        ++k;
    }
    while (j <= end_index) {
        merged_arr[k] = arr[j];
        ++j;
        ++k;
    }
    for (i = start_index; i <= end_index; ++i) {
        arr[i] = merged_arr[i - start_index];
    }
}

void mergeSort(int arr[], int start_index, int end_index) {
    if (start_index >= end_index) {
        return;
    }
    int middle_index = start_index + (end_index - start_index) / 2;
    mergeSort(arr, start_index, middle_index);
    mergeSort(arr, middle_index + 1, end_index);
    merge(arr, start_index, middle_index, end_index);
}

int main() {
    const int size = 900;
    int arr[size];

    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % size;
    }

    cout << "Inainte de sortare: ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // merge-sort array and time counting
    auto start_time = chrono::high_resolution_clock::now();
    mergeSort(arr, 0, size - 1);
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = end_time - start_time;

    cout << "Dupa sortare: ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Timp procesor pentru algoritm merge-sort cu " << size << " elemente, este de: " << duration.count() << " ns." << endl;

    return 0;
}
