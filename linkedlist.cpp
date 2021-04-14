#include <iostream>
#include <string>

using namespace std;

template <class T>
class LinkedList
{
private:
	struct node
	{
		T data;
		node * next;
	} *head;

public:
	//constructor
	LinkedList()
	{
		head = NULL;
	}


	//destructor
	~LinkedList()
	{
		node *p, *q;
		p = head;
		if (p == NULL) return;
		while (p) {
			q = p->next;
			delete p;
			p = q;
		}
	}
	//add new node in the linked list
	void add(T d)
	{
		node *p, *q;
		if (head == NULL) {
			head = new node;
			head->data = d;
			head->next = NULL;
			return;
		}
		p = head;
		while (p->next != NULL)
			p = p->next;
		q = new node;
		q->data = d;
		q->next = NULL;
		p->next = q;
	}


	//display all nodes of linked list 
	void display(const char* s)
	{
		node *p;
		if (head == NULL) return;
		p = head;
		while (p) {
			if (s == "string")
				cout << p->data << endl;
			else
				cout << p->data << ' ';
			p = p->next;
			if (p != NULL) {
				if (p == head) return;
			}
		}
		if (s == "integer") cout << endl;
	}
	// Checks whether the value x is present in linked list */
	bool search(T x)
	{
		node* current = head; // Initialize current  
		while (current != NULL)
		{
			if (current->data == x)
				return true;
			current = current->next;
		}
		return false;
	}
	// Delete the node from the linked list whose data = key;
	void deleteNode(T key)
	{

		// Store head node
		node* temp = head;
		node* prev = NULL;

		// If head node itself holds
		// the key to be deleted
		if (temp != NULL && temp->data == key)
		{
			head = temp->next; // Changed head
			delete temp;            // free old head
			return;
		}

		// Else Search for the key to be deleted, 
		// keep track of the previous node as we
		// need to change 'prev->next' */
		else
		{
			while (temp != NULL && temp->data != key)
			{
				prev = temp;
				temp = temp->next;
			}

			// If key was not present in linked list
			if (temp == NULL)
				return;

			// Unlink the node from linked list
			prev->next = temp->next;

			// Free memory
			delete temp;
		}
	}

};




int main()
{
	LinkedList<char> list1;
	char ch;
	int random;
	for (int i = 0; i < 10; i++)
	{
		random = rand() % 26;
		ch = 'a' + random;
		list1.add(ch);
	}	
	cout << "\nElements persent in the linked List are as follow: \n";
	list1.display("char");

	cout << "\nWhich character do you want to Remove in this linked list?\n";
	cin >> ch;
	list1.deleteNode(ch);
	cout << "\nList after removing node\n";
	list1.display("char");



	cout << "\nWhich character do you want to Search in this linked list?\n";
	cin >> ch;
	
	bool r = list1.search(ch);
	if (r == true)
	{
		cout << "\nThe Element is persent in the Linked list\n";
	}
	else
	{
		cout << "\nNot persent in linked list\n";
	}
	
	list1.display("char");


	LinkedList<int> List2;
	for (int i = 0; i < 10; i++)
	{
		random = rand() % 100;
		List2.add(random);
	}	
	cout << "\nLinked list of the integers are as follow:\n";
	List2.display("integer");
	int num;
	cout << "\nWhich Integer do you want to Remove in this linked list?\n";
	cin >> num;
	List2.deleteNode(num);
	cout << "\nList after removing node\n";
	List2.display("integer");

	cout << "\nWhich Integer do you want to Search in this linked list?\n";
	cin >> num;

	r = List2.search(num);
	if (r == true)
	{
		cout << "\nThe Element is persent in the Linked list\n";
	}
	else
	{
		cout << "\nNot persent in linked list\n";
	}

	List2.display("integer");

	system("pause");
	return 0;
}