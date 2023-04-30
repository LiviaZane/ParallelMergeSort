#include "utils.h"

using namespace std;

void createSortExpectedFile(int n)
{
    int* arr = new int[n];
    for (int i = 0; i < n; i++)
        arr[i] = i;
    ofstream outfile("files/sortExpected.bin", ios::binary);
    outfile.write((char*)&n, sizeof(n));                           // write size to file
    outfile.write((char*)arr, n * sizeof(int));                    // write array to file
    outfile.close();
    delete[] arr;
}

void createUnsortedFile(int n)
{
    int* arr = new int[n];
    for (int i = 0; i < n; i++)
        arr[i] = i;
    int index_one, index_two;
    for (int i = 0; i < n; i++)
    {
        index_one = rand() % n;
        index_two = rand() % n;
        swap(arr[index_one], arr[index_two]);
    }
    ofstream outfile("files/unsorted.bin", ios::binary);
    outfile.write((char*)&n, sizeof(n)); // write size to file
    outfile.write((char*)arr, n * sizeof(int)); // write array to file
    outfile.close();
    delete[] arr;
}

int* readArrayFromFile(const char* fileName)
{
    ifstream infile(fileName, ios::binary);
    int n;
    infile.read((char*)&n, sizeof(n)); // read size from file
    infile.seekg(sizeof(n));  // seek to second line of file
    int* arr = new int[n];
    infile.read((char*)arr, n * sizeof(int)); // read array from file
    infile.close();

    return arr;
}

int sizeOfArrayInFile(const char* fileName)
{
    ifstream infile("files/unsorted.bin", ios::binary);
    int n;
    infile.read((char*)&n, sizeof(n)); // read size from file
    infile.close();
    return n;
}

bool compareTwoArrays(int* arr1, int size1, int* arr2, int size2)
{
    if (size1 != size2)
        return false;
    for(int i=0; i < size1; i++)
    {
        if (arr1[i] != arr2[i])
            return false;
    }
    return true;
}

bool isArrayAscendingSorted(int* arr, int sizeOfArray)
{
    for(int i = 1; i < sizeOfArray; i++)
    {
        if(arr[i] < arr[i-1])
            return false;
    }
    return true;
}

string numberWithComma(int n) {
	string result=to_string(n);
		for(int i=result.size()-3; i>0;i-=3)
			result.insert(i,".");
		return result;
}
