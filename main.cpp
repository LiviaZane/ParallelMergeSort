#include "utils.h"
#include "mergeSortSecvential.h"
#include "mergeSortParallel.h"
#include <chrono>                          // for time
#include <windows.h>                       // for memory usage
#include <list>                            // list and forward_list to compare custom implemented (merge sort)
#include <forward_list>                         // and standard sort() method of list/list_forward


using namespace std;

int main()
{
    int threadsNo = 4;

    srand(time(NULL));                      // reinitialize seed for rand()

    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx (&statex);
    auto initialMemoryLoad = statex.dwMemoryLoad;
    cout << "Initial memory used : " << initialMemoryLoad << "%" << endl << endl;
    ofstream outFileTests("files/tests.csv", ios::out| ios::app);
    //outFileTests << "Type, Size, Threads, InitialMemory, FinalMemory, Time[ms]" << endl;

    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    // Create a sorted array into "sortExpected.bin" file to have a reference for compareTwoArrays(reference, sortedByAlgorithm)
    // Binary format is used because the file is smaller and IO operations are faster
    cout << "An array of " << numberWithComma(n) << " integers is generated and saved in <sortExpected.bin> file." << endl;
    createSortExpectedFile(n);

    // Randomize above array and save it into "unsorted.bin" file to use the same array for all algorithm,
    // and work in the memory just two array (else must have three: sortedReference, unsortedReference, sortingArray)
    cout << "The above array is randomized and saved in <unsorted.bin> file." << endl << endl;
    createUnsortedFile(n);


    // Read the sorted array from "sortExpected.bin" file
    char* fileNameSortedExpected = (char*)"files/sortExpected.bin";
    int* arrSortedExpected = readArrayFromFile(fileNameSortedExpected);       // read an array from a binary file
    int sizeSortedExpected = sizeOfArrayInFile(fileNameSortedExpected);       // and array size
    const char* result = ((bool)isArrayAscendingSorted) ? "Read from file the standard array which is ascending sorted."
                                                  : "Read from file the standard array which is NOT ascending sorted. !!!";
    cout << result  << endl << endl;


    // Read the unsorted array from "unsorted.bin" file
    char* fileNameUnsortedArray = (char*)"files/unsorted.bin";
    int* arrUnsorted = readArrayFromFile(fileNameUnsortedArray);       // read an array from a binary file
    int sizeArrayUnsorted = sizeOfArrayInFile(fileNameUnsortedArray);       // and array size
    cout << "Read from file the unsorted array with a size of " << numberWithComma(sizeArrayUnsorted) << " integers." << endl << endl;


    // Merge sorting a list and a forward_list with their C++ implicit sort() method
    list<int> cppListSorting;
    forward_list<int> cppForwardListSorting;
    for (int i = 0; i < sizeArrayUnsorted; i++)
        cppListSorting.push_back(arrUnsorted[i]);
    auto start = chrono::high_resolution_clock::now();                        // start time counting
    cppListSorting.sort();                                                         // run the algorithm
    auto finish = chrono::high_resolution_clock::now();                       // stop time counting
    GlobalMemoryStatusEx (&statex);
    cout << "Memory used : " << statex.dwMemoryLoad << "%" << endl;
    auto timeTaken =  chrono::duration_cast<std::chrono::milliseconds>(finish-start).count();
    outFileTests << "List,";
    outFileTests << n;
    outFileTests << ",,";
    outFileTests << initialMemoryLoad;
    outFileTests << ",";
    outFileTests << statex.dwMemoryLoad;
    outFileTests << ",";
    outFileTests <<timeTaken << endl;
    cout << "Time for sorting a list (double linked list) with implicit sort() method in C++: " << timeTaken << " ms. " << endl << endl;
    arrUnsorted = readArrayFromFile(fileNameUnsortedArray);
    for (int i = 0; i < sizeArrayUnsorted; i++)
        cppForwardListSorting.push_front(arrUnsorted[i]);
    start = chrono::high_resolution_clock::now();
    cppForwardListSorting.sort();
    finish = chrono::high_resolution_clock::now();
    GlobalMemoryStatusEx (&statex);
    cout << "Memory used : " << statex.dwMemoryLoad << "%" << endl;
    timeTaken =  chrono::duration_cast<std::chrono::milliseconds>(finish-start).count();
    cout << "Time for sorting a forward_list (single linked list) with implicit sort() method in C++: " << timeTaken << " ms. " << endl << endl;
    outFileTests << "ForwardList,";
    outFileTests << n;
    outFileTests << ",,";
    outFileTests << initialMemoryLoad;
    outFileTests << ",";
    outFileTests << statex.dwMemoryLoad;
    outFileTests << ",";
    outFileTests <<timeTaken << endl;

    // Merge sort sequentially recursive algorithm
    cout << "Array of " << numberWithComma(sizeArrayUnsorted) << " elements is merge sorting with sequentially recursive algorithm" << endl;
    arrUnsorted = readArrayFromFile(fileNameUnsortedArray);
    start = chrono::high_resolution_clock::now();
    int* arrSortedSequentiallyRecursive = mergeSortSequentiallyRecursive(arrUnsorted, 0, sizeArrayUnsorted - 1);
    finish = chrono::high_resolution_clock::now();
    GlobalMemoryStatusEx (&statex);
    cout << "Memory used : " << statex.dwMemoryLoad << "%" << endl;
    timeTaken =  chrono::duration_cast<std::chrono::milliseconds>(finish-start).count();
    cout << "Time : " << timeTaken << " ms. " << endl;
    outFileTests << "SecventiallyRecursive,";
    outFileTests << n;
    outFileTests << ",,";
    outFileTests << initialMemoryLoad;
    outFileTests << ",";
    outFileTests << statex.dwMemoryLoad;
    outFileTests << ",";
    outFileTests <<timeTaken << endl;
    result = (compareTwoArrays(arrSortedSequentiallyRecursive, sizeArrayUnsorted, arrSortedExpected, sizeSortedExpected))
        ? "Array was sorted as expected." : "Array was not sorted as expected !!!";
    cout << result << endl << endl;


    // Merge sort sequentially iterative algorithm
    cout << "Array of " << numberWithComma(sizeArrayUnsorted) << " elements is merge sorting sequentially iterative algorithm" << endl;
    arrUnsorted = readArrayFromFile(fileNameUnsortedArray);
    start = chrono::high_resolution_clock::now();
    int* arrSortedSequentiallyIterative = mergeSortSequentiallyIterative(arrUnsorted, sizeArrayUnsorted);
    finish = chrono::high_resolution_clock::now();
    GlobalMemoryStatusEx (&statex);
    cout << "Memory used : " << statex.dwMemoryLoad << "%" << endl;
    timeTaken =  chrono::duration_cast<std::chrono::milliseconds>(finish-start).count();
    cout << "Time : " << timeTaken << " ms. " << endl;
    outFileTests << "SecventiallyIterative,";
    outFileTests << n;
    outFileTests << ",,";
    outFileTests << initialMemoryLoad;
    outFileTests << ",";
    outFileTests << statex.dwMemoryLoad;
    outFileTests << ",";
    outFileTests <<timeTaken << endl;
    result = (compareTwoArrays(arrSortedSequentiallyIterative, sizeArrayUnsorted, arrSortedExpected, sizeSortedExpected))
        ? "Array was sorted as expected." : "Array was not sorted as expected !!!";
    cout << result << endl << endl;


    // Merge sort parallel recursive algorithm
    cout << "Array of " << numberWithComma(sizeArrayUnsorted) << " elements is merge sorting parallel recursive algorithm" << endl;
    arrUnsorted = readArrayFromFile(fileNameUnsortedArray);
    start = chrono::high_resolution_clock::now();
    int* arrSortedParallelRecursive = mergeSortParallelRecursive(arrUnsorted, 0, sizeArrayUnsorted - 1, threadsNo);
    finish = chrono::high_resolution_clock::now();
    GlobalMemoryStatusEx (&statex);
    cout << "Memory used : " << statex.dwMemoryLoad << "%" << endl;
    timeTaken =  chrono::duration_cast<std::chrono::milliseconds>(finish-start).count();
    cout << "Time : " << timeTaken << " ms. " << endl;
    outFileTests << "ParallelRecursive,";
    outFileTests << n;
    outFileTests << ",";
    outFileTests << threadsNo;
    outFileTests << ",";
    outFileTests << initialMemoryLoad;
    outFileTests << ",";
    outFileTests << statex.dwMemoryLoad;
    outFileTests << ",";
    outFileTests <<timeTaken << endl;
    result = (compareTwoArrays(arrSortedParallelRecursive, sizeArrayUnsorted, arrSortedExpected, sizeSortedExpected))
        ? "Array was sorted as expected." : "Array was not sorted as expected !!!";
    cout << result << endl << endl;


    // Merge sort parallel iterative algorithm
    cout << "Array of " << numberWithComma(sizeArrayUnsorted) << " elements is merge sorting parallel iterative algorithm" << endl;
    arrUnsorted = readArrayFromFile(fileNameUnsortedArray);
    start = chrono::high_resolution_clock::now();
    int* arrSortedParallelIterative = mergeSortParallelIterative(arrUnsorted, sizeArrayUnsorted, threadsNo);
    finish = chrono::high_resolution_clock::now();
    GlobalMemoryStatusEx (&statex);
    cout << "Memory used : " << statex.dwMemoryLoad << "%" << endl;
    timeTaken =  chrono::duration_cast<std::chrono::milliseconds>(finish-start).count();
    cout << "Time : " << timeTaken << " ms. " << endl;
    outFileTests << "ParallelRecursive,";
    outFileTests << n;
    outFileTests << ",";
    outFileTests << threadsNo;
    outFileTests << ",";
    outFileTests << initialMemoryLoad;
    outFileTests << ",";
    outFileTests << statex.dwMemoryLoad;
    outFileTests << ",";
    outFileTests <<timeTaken << endl;
    result = (compareTwoArrays(arrSortedParallelIterative, sizeArrayUnsorted, arrSortedExpected, sizeSortedExpected))
        ? "Array was sorted as expected." : "Array was not sorted as expected !!!";
    cout << result << endl << endl;

    outFileTests.close();
    delete[] arrSortedExpected;
    delete[] arrUnsorted;

    return 0;
}
