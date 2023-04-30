#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <iostream>
#include <fstream>


void createSortExpectedFile(int n);
void createUnsortedFile(int n);
int* readArrayFromFile(const char* fileName);
int sizeOfArrayInFile(const char* fileName);
bool compareTwoArrays(int* arr1, int size1, int* arr2, int size2);
bool isArrayAscendingSorted(int* arr, int sizeOfArray);
std::string numberWithComma(int n);

#endif // UTILS_H_INCLUDED
