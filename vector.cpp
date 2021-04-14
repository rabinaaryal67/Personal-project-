////
//  main.cpp
//  Project_313

#include <iostream>
using namespace std;
template <typename T> class vectorClass
{
	T* arr;
	int capacity;
	int current;

public:
	
	vectorClass()
	{
		arr = new T[1];
		capacity = 1;
		current = 0;
	}
	// Function to add an element at the last
	void push(T data)
	{

		// if the number of elements is equal to the
		// capacity, that means we don't have space to
		// accommodate more elements. We need to double the
		// capacity
		if (current == capacity) {
			T* temp = new T[2 * capacity];

			// copying old array elements to new array
			for (int i = 0; i < capacity; i++) {
				temp[i] = arr[i];
			}

			// deleting previous array
			delete[] arr;
			capacity *= 2;
			arr = temp;
		}

		// Inserting data
		arr[current] = data;
		current++;
	}
	// function to add element at any index
	void push(int data, int index)
	{

		// if index is equal to capacity then this
		// function is same as push defined above
		if (index == capacity)
			push(data);
		else
			arr[index] = data;
	}

	// function to extract element at any index
	T get(int index)
	{

		// if index is within the range
		if (index < current)
			return arr[index];
	}

	// function to delete last element
	void pop() { current--; }

	// function to get size of the vector
	int size() { return current; }

	// function to get capacity of the vector
	int getcapacity() { return capacity; }

	// function to print array elements
	void print()
	{
		for (int i = 0; i < current; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	void search(T key)
	{
		bool flag = false;
		for (int i = 0; i < current; i++) {
			if (arr[i] == key)
			{
				cout << arr[i] << " is persent in the vector at index "<< i <<endl;
				flag = true;
			}			
		}
		if (flag == false)
		{
			cout <<"Element is not persent in vector" <<endl;
		}
		

	}


};


int main()
{
	int random;
	vectorClass<int> v;
	vectorClass<char> v1;
	for (int i = 0; i < 10; i++)
	{
		random = rand() % 100;
		v.push(random);
	}
	char ch;
	for (int i = 0; i < 10; i++)
	{
		random = rand() % 26;
		ch = 'a' + random;
		v1.push(ch);
	}
	
	cout << "Vector elements : ";
	v.print();

	v.push(100, 1);

	cout << "\nAfter updating 1st index" << endl;

	cout << "Vector elements of type int : " << endl;
	v.print();

	cout << "Vector elements of type char : " << endl;
	v1.print();
	cout << "Element at 1st index of type int: " << v.get(1)
		<< endl;
	cout << "Element at 1st index of type char: "
		<< v1.get(1) << endl;

	v.pop();
	v1.pop();

	cout << "\nAfter deleting last element" << endl;
	
	cout << "Vector elements of type int: ";
	v.print();
	cout << "Vector elements of type char: ";
	v1.print();
	int a;
	
	cout << "Search any element in the integer vector\n";
	cin >> a;
	v.search(a);

	cout << "Search any element in the Character vector\n";
	cin >> ch;
	v1.search(ch);
	



	system("pause");

	return 0;
}
