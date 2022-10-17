#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <fstream>
#include <string>

#pragma
using namespace std::chrono;

//void write_to_csv(std::string &fileName, int arrayLength, auto duration);

void print(int *, int);

void write_to_csv(std::string, int, long long int);


// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(int *, int const, int const, int const);

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int *, int const, int const);


// Driver code
int main() {
    std::srand(time(nullptr));

    std::string file_name = "./merge-10kstep.csv";
    std::ofstream file;
    file.open(file_name, std::ios::out);

    int size;

    for (size = 100; size < 1000000; size = size + 10000) {
        int *list = new int[size];

        for (int i = 0; i < size; ++i) {
            list[i] = rand() % size;
        }
        std::cout << "List Size: " << size << std::endl;
        //print(list, size);

        auto start = high_resolution_clock::now();

        mergeSort(list, 0, size - 1);

        //print(list, size);

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        std::cout << "Duration: " << duration.count() << std::endl;

        //write_to_csv(file_name, size, duration.count());


        if (file.is_open()) {
            file << size << "," << duration.count() << std::endl;
        }
    }
    int *list = NULL;
    delete list;

    file.close();
    return 0;
}

// ref. https://www.geeksforgeeks.org/merge-sort/
void mergeSort(int *array, int const begin, int const end) {
    if (begin >= end)
        return; // Returns recursively

    auto mid = begin + (end - begin) / 2;
    // left
    mergeSort(array, begin, mid);
    // right
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

void merge(int *array, int const left, int const mid,
           int const right) {
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    // Create temp arrays
    int *leftArray = new int[subArrayOne],
            *rightArray = new int[subArrayTwo];

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (int i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    int indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne
           && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne]
            <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray]
                    = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        } else {
            array[indexOfMergedArray]
                    = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

int *getArray(int size) {
    int *arr = new int[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % size;

    }
    return arr;
}

void write_to_csv(std::string &fileName, int arrayLength, long long int duration) {
    std::string l = std::to_string(arrayLength);
    std::string d = std::to_string(duration);

    std::ofstream file;
    file.open(fileName, std::ios::out);
    if (file.is_open()) {
        file << l << "," << d << std::endl;
        file.close();
    }
}

void print(int *array, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}
