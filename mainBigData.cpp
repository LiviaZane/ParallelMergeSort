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
    int threadsNo = 16;

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

    int* arrUnsortedSample = new int[n];
    for (int i = 0; i < n; i++)
        arrUnsortedSample[i] = i;
    int index_one, index_two;
    for (int i = 0; i < n; i++)
    {
        index_one = rand() % n;
        index_two = rand() % n;
        swap(arrUnsortedSample[index_one], arrUnsortedSample[index_two]);
    }

    /*
    // Merge sorting a list and a forward_list with their C++ implicit sort() method
    list<int> cppListSorting;
    forward_list<int> cppForwardListSorting;
    for (int i = 0; i < n; i++)
        cppListSorting.push_back(arrUnsortedSample[i]);
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
    int* arrUnsorted = new int[n];
    for (int i = 0; i < n; i++)
        arrUnsorted[i] = arrUnsortedSample[i];
    for (int i = 0; i < n; i++)
        cppForwardListSorting.push_front(arrUnsortedSample[i]);
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

    */
    int* arrUnsorted = new int[n];
    for (int i = 0; i < n; i++)
        arrUnsorted[i] = arrUnsortedSample[i];

/*

    // Merge sort sequentially recursive algorithm
    cout << "Array of " << numberWithComma(n) << " elements is merge sorting with sequentially recursive algorithm" << endl;
    auto start = chrono::high_resolution_clock::now();
    int* arrSortedSequentiallyRecursive = mergeSortSequentiallyRecursive(arrUnsorted, 0, n - 1);
    auto finish = chrono::high_resolution_clock::now();
    GlobalMemoryStatusEx (&statex);
    cout << "Memory used : " << statex.dwMemoryLoad << "%" << endl;
    auto timeTaken =  chrono::duration_cast<std::chrono::milliseconds>(finish-start).count();
    cout << "Time : " << timeTaken << " ms. " << endl;
    outFileTests << "SecventiallyRecursive,";
    outFileTests << n;
    outFileTests << ",,";
    outFileTests << initialMemoryLoad;
    outFileTests << ",";
    outFileTests << statex.dwMemoryLoad;
    outFileTests << ",";
    outFileTests <<timeTaken << endl;


    // Merge sort sequentially iterative algorithm
    cout << "Array of " << numberWithComma(n) << " elements is merge sorting sequentially iterative algorithm" << endl;
    for (int i = 0; i < n; i++)
        arrUnsorted[i] = arrUnsortedSample[i];
    start = chrono::high_resolution_clock::now();
    int* arrSortedSequentiallyIterative = mergeSortSequentiallyIterative(arrUnsorted, n);
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
*/

    // Merge sort parallel recursive algorithm
    cout << "Array of " << numberWithComma(n) << " elements is merge sorting parallel recursive algorithm" << endl;
    for (int i = 0; i < n; i++)
        arrUnsorted[i] = arrUnsortedSample[i];
    auto start = chrono::high_resolution_clock::now();
    int* arrSortedParallelRecursive = mergeSortParallelRecursive(arrUnsorted, 0, n - 1, threadsNo);
    auto finish = chrono::high_resolution_clock::now();
    GlobalMemoryStatusEx (&statex);
    cout << "Memory used : " << statex.dwMemoryLoad << "%" << endl;
    auto timeTaken =  chrono::duration_cast<std::chrono::milliseconds>(finish-start).count();
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


    // Merge sort parallel iterative algorithm
    cout << "Array of " << numberWithComma(n) << " elements is merge sorting parallel iterative algorithm" << endl;
    for (int i = 0; i < n; i++)
        arrUnsorted[i] = arrUnsortedSample[i];
    start = chrono::high_resolution_clock::now();
    int* arrSortedParallelIterative = mergeSortParallelIterative(arrUnsorted, n, threadsNo);
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


    outFileTests.close();
    delete[] arrUnsortedSample;
    delete[] arrUnsorted;

    return 0;
}
