#include "main.h"

using namespace std;

int* createArray(int arraySize);
void initializeArray(int* array, int arraySize);
void printArray(int* array, int arraySize);
void deleteArray(int* array);

int main() {
	bool isRunning{ true };
	int arrSize{ 1 };

	while (isRunning) {
		cout << "Enter the size of your array (or '0' to stop the loop): ";
		cin >> arrSize;

		if (arrSize > 0) {
			// Create the array based on user input
			int* arr = createArray(arrSize);
			cout << "Array of size " << arrSize << " created at: " << arr << endl;

			// Initialize the array with values from '0' to 'arrSize - 1'
			initializeArray(arr, arrSize);
			cout << "Array initialized with values from 0 to " << arrSize - 1 << ":" << endl;

			// Print the values of the array
			printArray(arr, arrSize);

			// De-allocate the array's dynamically-allocated memory.
			deleteArray(arr);
			cout << "The array has been deleted from memory." << endl;
		}
		else {
			isRunning = false;
		}
	}

	cout << "Exiting program...";

	return 0;
}

int* createArray(int arraySize) {
	int* array = (int*)malloc(arraySize * sizeof(int));

	return array;
}

void initializeArray(int* array, int arraySize) {
	for (int i = 0; i < arraySize; i++) {
		*(array + i) = i;
	}
}

void printArray(int* array, int arraySize) {
	for (int i = 0; i < arraySize; i++) {
		cout << *(array + i) << " ";
	}
	cout << endl;
}

void deleteArray(int* array) {
	free(array);
}