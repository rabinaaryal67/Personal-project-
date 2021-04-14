#include <iostream>
#include <chrono>
using namespace std;


// A recursive binary search function. It returns 
// location of x in given array arr[l..r] is present, 
// otherwise -1 
int rec_binarySearch(int arr[], int l, int r, int x)
{
	if (r >= l) {
		int mid = l + (r - l) / 2;

		// If the element is present at the middle 
		// itself 
		if (arr[mid] == x)
			return mid;

		// If element is smaller than mid, then 
		// it can only be present in left subarray 
		if (arr[mid] > x)
			return rec_binarySearch(arr, l, mid - 1, x);

		// Else the element can only be present 
		// in right subarray 
		return rec_binarySearch(arr, mid + 1, r, x);
	}

	// We reach here when element is not 
	// present in array 
	return -1;
}


// A iterative binary search function. It returns 
// location of x in given array arr[l..r] if present, 
// otherwise -1 
int iter_binarySearch(int arr[], int l, int r, int x)
{
	while (l <= r) {
		int m = l + (r - l) / 2;

		// Check if x is present at mid 
		if (arr[m] == x)
			return m;

		// If x greater, ignore left half 
		if (arr[m] < x)
			l = m + 1;

		// If x is smaller, ignore right half 
		else
			r = m - 1;
	}

	// if we reach here, then element was 
	// not present 
	return -1;
}

struct Node
{
	int data;
	struct Node* next;
};

Node *newNode(int x)
{
	struct Node* temp = new Node;
	temp->data = x;
	temp->next = NULL;
	return temp;
}

// function to find out middle element 
struct Node* middle(Node* start, Node* last)
{
	if (start == NULL)
		return NULL;

	struct Node* slow = start;
	struct Node* fast = start->next;

	while (fast != last)
	{
		fast = fast->next;
		if (fast != last)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}

	return slow;
}

// Function for implementing the Binary 
// Search on linked list 
struct Node* link_binarySearch(Node *head, int value)
{
	struct Node* start = head;
	struct Node* last = NULL;

	do
	{
		// Find middle 
		Node* mid = middle(start, last);

		// If middle is empty 
		if (mid == NULL)
			return NULL;

		// If value is present at middle 
		if (mid->data == value)
			return mid;

		// If value is more than mid 
		else if (mid->data < value)
			start = mid->next;

		// If the value is less than mid. 
		else
			last = mid;

	} while (last == NULL ||
		last != start);

	// value not present 
	return NULL;
}



int main(void)
{

	int sum=0;
	int* arr = new int[1000000];

	for (int j = 0; j < 1000000; j++)
	{
		int k = rand() % 100;
		sum = sum + k;
		//cout << sum << " ";
		arr[j] = sum;
	}
	cout << "Last ten Numbers of 1 million size array is = " << endl;
	for (int j = 1000000-1, i=0; i < 10; j--,i++)
	{
		cout << arr[j] << " ";
	}
	int x = 0;
	cout << "\n Enter number you want to search = ";
	cin >> x;
	int n = 1000000;
	cout << "\n\n\t\t\t\t Array size = " << n << endl;
	
	// Record start time
	auto start = std::chrono::high_resolution_clock::now();
	cout << "\n\n\t\t**************************Recursive Binary Search***********************************\n";
	int result = rec_binarySearch(arr, 0, n - 1, x);
	auto end = std::chrono::high_resolution_clock::now();
	auto diff = end - start;
	(result == -1) ? cout << "Element is not present in array\n"
		: cout << "Element is present at index =" << result << endl;
	cout <<"Total time to execute this function = "<< chrono::duration <double, nano>(diff).count() << " ns" << endl;
	cout << "\n\n\n\t\t**************************Iterative Binary Search***********************************\n";
	// Record start time
	start = std::chrono::high_resolution_clock::now();
	int result1 = iter_binarySearch(arr, 0, n - 1, x);
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	(result1 == -1) ? cout << "Element is not present in array\n"
		: cout << "Element is present at index = " << result1 << endl;
	cout << "Total time to execute this function = " << chrono::duration <double, nano>(diff).count() << " ns" << endl;
	delete[] arr;


	int* arr1 = new int[10000000];
	for (int j = 0; j < 10000000; j++)
	{
		int k = rand() % 100;
		sum = sum + k;
		//cout << sum << " ";
		arr1[j] = sum;
	}
	cout << "\n\n\n\n\n\nLast ten Numbers of 10 million size array is = " << endl;
	for (int j = 10000000 - 1, i = 0; i < 10; j--, i++)
	{
		cout << arr1[j] << " ";
	}
	x = 0;
	cout << "\n Enter number you want to search = ";
	cin >> x;
	n = 10000000;
	cout << "\n\n\t\t\t\t Array size = " << n << endl;
	// Record start time
	start = std::chrono::high_resolution_clock::now();
	cout << "\n\n\t\t**************************Recursive Binary Search***********************************\n";
	result = rec_binarySearch(arr1, 0, n - 1, x);
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	(result == -1) ? cout << "Element is not present in array\n"
		: cout << "Element is present at index =" << result << endl;
	cout << "Total time to execute this function = " << chrono::duration <double, nano>(diff).count() << " ns" << endl;
	cout << "\n\n\n\t\t**************************Iterative Binary Search***********************************\n";

	// Record start time
	start = std::chrono::high_resolution_clock::now();
	result1 = iter_binarySearch(arr1, 0, n - 1, x);
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	(result1 == -1) ? cout << "Element is not present in array\n"
		: cout << "Element is present at index = " << result1 << endl;

	cout << "Total time to execute this function = " << chrono::duration <double, nano>(diff).count() << " ns" << endl;

	delete[] arr1;


	//Node *head = newNode(1);
	//head->next = newNode(4);
	//head->next->next = newNode(7);
	//head->next->next->next = newNode(8);
	//head->next->next->next->next = newNode(9);
	//head->next->next->next->next->next = newNode(10);
	//int value = 7;
	//if (link_binarySearch(head, value) == NULL)
	//	printf("Value not present\n");
	//else
	//	printf("Present");



	system("pause");
	return 0;
}
