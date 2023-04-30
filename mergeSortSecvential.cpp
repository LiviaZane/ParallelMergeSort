#include "mergeSortSecvential.h"

using namespace std;


void merge(int* arr, int left, int middle, int right) {    // just this function is used to merge sub-array in all other algorithms
    int i, j, k;               // iterators for left sub-array (i), right sub-array (j) and merged array
    int leftSize = middle - left + 1;            // left sub-array size
    int rightSize = right - middle;              // right sub-array size
    int* leftSubarray = new int[leftSize];
    int* rightSubarray = new int[rightSize];          // create left and right sub-arrays
    for (i = 0; i < leftSize; i++)          // copy elements from arr into left sub-array
        leftSubarray[i] = arr[left + i];
    for (j = 0; j < rightSize; j++)         // copy elements from arr into right sub-array
        rightSubarray[j] = arr[middle + 1 + j];
    i = 0; j = 0; k = left;            // reset counters, to merge elements from sub-arrays back to the merged array
    while (i < leftSize && j < rightSize) {    // loop with i through left sub-array and j through right sub-array
        if (leftSubarray[i] <= rightSubarray[j]) { // the smaller element is copied back into the array, starting with the smaller
            arr[k++] = leftSubarray[i++];       //  index and the index of that sub-array and of merged array should be incremented
        }
        else {
            arr[k++] = rightSubarray[j++];
        }
    }
    while (i < leftSize) {
        arr[k++] = leftSubarray[i++];              // copy the remaining elements from left and right sub-array, if any
    }
    while (j < rightSize) {
        arr[k++] = rightSubarray[j++];
    }
    delete[] leftSubarray;
    delete[] rightSubarray;
}



int* mergeSortSequentiallyIterative(int* arr, int n) {   // Merge sub-arrays in bottom-up manner.
    int subArraySize;                             // size of sub-arrays to be merged (between 1 and n/2)
    int leftArrayStartIndex;                      // starting index of left sub-array to be merged (between 0 and n-1)
    // First merge sub-arrays of size 1 to create sorted sub-arrays of size 2,
    // then merge sub-arrays of size 2 to create sorted sub-arrays of size 4, and so on.
    // Divide the array into sub-arrays of [1, 2, 4, 8, 16......]
    for (subArraySize = 1; subArraySize <= n - 1; subArraySize = 2 * subArraySize) {
        // for subArraySize = 1, leftArrayStartIndex = 0, 2, 4, 6, 8…
        // for subArraySize = 2, leftArrayStartIndex = 0, 4, 8, 16 ...
        // for subArraySize = 4, leftArrayStartIndex = 0, 8, 16, 32 ...
        // …
        for (leftArrayStartIndex = 0; leftArrayStartIndex < n - 1; leftArrayStartIndex += 2 * subArraySize) {
            // Find ending index of left sub-array. middle+1 is starting point of right sub-array
            int middle = min(leftArrayStartIndex + subArraySize - 1, n - 1);
            // Find ending index of right sub-array. middle+1 is starting point of right sub-array
            int rightArrayEndIndex = min(leftArrayStartIndex + 2 * subArraySize - 1, n - 1);
            // Merge sub-arrays arr[leftStartIndex...mid] and arr[middle+1...right_end]
            merge(arr, leftArrayStartIndex, middle, rightArrayEndIndex);
        }
    }
    return arr;
}



int* mergeSortSequentiallyRecursive(int* arr, int left, int right) {    // Merge sub-arrays in top-down manner.
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSortSequentiallyRecursive(arr, left, middle);
        mergeSortSequentiallyRecursive(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
    return arr;
}
