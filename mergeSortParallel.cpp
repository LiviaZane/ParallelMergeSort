#include <thread>
#include <vector>
#include "mergeSortParallel.h"
#include "mergeSortSecvential.h"

using namespace std;

int* mergeSortParallelRecursive(int* arr, int left, int right, int numThreads) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        if (numThreads == 1) {
            mergeSortSequentiallyRecursive(arr, left, mid);
            mergeSortSequentiallyRecursive(arr, mid + 1, right);
        }
        else {
            int numThreadsLeft = numThreads / 2;
            int numThreadsRight = numThreads - numThreadsLeft;
            thread leftThread(mergeSortParallelRecursive, arr, left, mid, numThreadsLeft);
            thread rightThread(mergeSortParallelRecursive, arr, mid + 1, right, numThreadsRight);
            leftThread.join();
            rightThread.join();
        }
        merge(arr, left, mid, right);
    }
    return arr;
}



int* mergeSortParallelIterative(int* arr, int n, int numThreads) {
    if (numThreads == 1) {
            mergeSortSequentiallyIterative(arr, n);
    }
    else {
        thread threads[numThreads];
        int threadSubarraySize = n / numThreads;
        int left, right;
        for (int i = 0; i < numThreads; i++) {
            left = i * threadSubarraySize;
            right = (i + 1) * threadSubarraySize - 1;
            if (i == numThreads - 1)
                right = n - 1;
            threads[i] = thread(mergeSortSequentiallyRecursive, arr, left, right);
        }
        for (int i = 0; i < numThreads; i++)
            threads[i].join();
        while (threadSubarraySize < n) {
            for (int i = 0; i < n; i += 2 * threadSubarraySize) {
                int left = i;
                int mid = i + threadSubarraySize - 1;
                int right = i + 2 * threadSubarraySize - 1;
                if (mid >= n)
                    continue;
                if (right >= n)
                    right = n - 1;
                merge(arr, left, mid, right);
            }
            threadSubarraySize *= 2;
        }
    }
    return arr;
}
