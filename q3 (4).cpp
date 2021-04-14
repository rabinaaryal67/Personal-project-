#include <iostream>
using namespace std;
#define M 4
#define N 4

//bubble 
void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

// A function to implement bubble sort  
void bubbleSort(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place  
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
}

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

void selectionSort(int arr[], int n)
{
	int i, j, min_idx;

	// One by one move boundary of unsorted subarray  
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in unsorted array  
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		// Swap the found minimum element with the first element  
		swap(&arr[min_idx], &arr[i]);
	}
}

void sort_bubble(int m[M][N])
{
	// One by one sort 
	// individual rows.
	for (int i = 0; i < M; i++)
		bubbleSort(m[i], N);

	// Printing the sorted matrix
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			cout << (m[i][j]) << " ";
		cout << endl;
	}

}
void sort_insertion(int m[M][N])
{
	// One by one sort 
	// individual rows.
	for (int i = 0; i < M; i++)
		insertionSort(m[i], N);

	// Printing the sorted matrix
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			cout << (m[i][j]) << " ";
		cout << endl;
	}

}


void sort_selection(int m[M][N])
{
	// One by one sort 
	// individual rows.
	for (int i = 0; i < M; i++)
		selectionSort(m[i], N);

	// Printing the sorted matrix
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			cout << (m[i][j]) << " ";
		cout << endl;
	}

}



// Driver code
int main()
{

	
	int m[M][N] = { {9, 8, 7, 1},
					{7, 3, 0, 2},
					{9, 5, 3, 2},
					{6, 3, 1, 2} };
	cout << "\nReal Matrix\n";
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			cout << (m[i][j]) << " ";
		cout << endl;
	}
	cout << "\nSort by bubbleSort\n";
	sort_bubble(m);

	cout << "\n\nSort by insertion sort\n";

	int m1[M][N] = { {9, 8, 7, 1},
					{7, 3, 0, 2},
					{9, 5, 3, 2},
					{6, 3, 1, 2} };

	sort_insertion(m1);
	
	cout << "\n\nSort by Selection sort\n";
	int m2[M][N] = { {9, 8, 7, 1},
					{7, 3, 0, 2},
					{9, 5, 3, 2},
					{6, 3, 1, 2} };

	sort_selection(m2);
	system("pause");
	return 0;
}


