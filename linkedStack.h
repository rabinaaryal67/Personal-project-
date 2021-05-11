//Header File: linkedStack.h

#ifndef H_StackType
#define H_StackType

#include <iostream>
#include <cassert>

#include "stackADT.h"

using namespace std;

//declare our generic template type
template <class Type>
//This structure holds nodeType information
struct nodeType
{
    //declare variable to hold type info
    Type info;
    //Make our linked list link variable a generic type 'Type'
    nodeType<Type> *link;
};

template <class Type>
//Inherit our abstract datatype STackADT
class linkedStackType: public stackADT<Type>
{
public:
    //declare our assignment operator
    const linkedStackType<Type>& operator=
                              (const linkedStackType<Type>&);

/// our get accessor to check if the list is empty
    bool isEmptyStack() const;

// our get accessor to check if the list is full
    bool isFullStack() const;

  // our void function to initalize the stack
    void initializeStack();

// our void function to push values into the stack
    void push(const Type& newItem);

    //our function to get the topmost value of our stack
    Type top() const;

 // our functiont to pop our values to the top
    void pop();

//our parameterless constructor
    linkedStackType();

// our copy constructor
    linkedStackType(const linkedStackType<Type>& otherStack);

// our destructor to de initialize our dynamic variables
    ~linkedStackType();
//private instant variables
private:
    nodeType<Type> *stackTop; //pointer to the stack
    // our private void function to copy our linkedstacktype
    void copyStack(const linkedStackType<Type>& otherStack);

};



template <class Type>

//Do all constructor initalization
linkedStackType<Type>::linkedStackType()
{
    stackTop = nullptr;
}

template <class Type>
//check if the stack is empty
bool linkedStackType<Type>::isEmptyStack() const
{
    return(stackTop == nullptr);
}

template <class Type>
//check if the stack is full
bool linkedStackType<Type>:: isFullStack() const
{
    return false;
}

template <class Type>
//initialize the stack
void linkedStackType<Type>:: initializeStack()
{
    nodeType<Type> *temp;

    while (stackTop != nullptr)
    {
        temp = stackTop;

        stackTop = stackTop->link;

        delete temp;
    }
}

template <class Type>
//push value into our stack
//by linking it with our existing top value

void linkedStackType<Type>::push(const Type& newElement)
{
    nodeType<Type> *newNode;

    newNode = new nodeType<Type>;

    newNode->info = newElement;

    newNode->link = stackTop;
    stackTop = newNode;

} //end push


template <class Type>
//get our top value
Type linkedStackType<Type>::top() const
{
    assert(stackTop != nullptr);

    return stackTop->info;
}//end top

template <class Type>
//move the value to the top
void linkedStackType<Type>::pop()
{
    nodeType<Type> *temp;

    if (stackTop != nullptr)
    {
        temp = stackTop;

        stackTop = stackTop->link;

        delete temp;
    }
    else
        cout << "Cannot remove from an empty stack." << endl;
}//end pop

template <class Type>
//copy object of type linkedSTacktype
void linkedStackType<Type>::copyStack
                     (const linkedStackType<Type>& otherStack)
{
    nodeType<Type> *newNode, *current, *last;

    if (stackTop != nullptr)
        initializeStack();

    if (otherStack.stackTop == nullptr)
        stackTop = nullptr;
    else
    {
        current = otherStack.stackTop;


        stackTop = new nodeType<Type>;

        stackTop->info = current->info;
        stackTop->link = nullptr;

        last = stackTop;
        current = current->link;


        while (current != nullptr)
        {
            newNode = new nodeType<Type>;

            newNode->info = current->info;
            newNode->link = nullptr;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }
    }
}


template <class Type>
//Copy constructor
linkedStackType<Type>::linkedStackType(
                      const linkedStackType<Type>& otherStack)
{
    stackTop = nullptr;
    copyStack(otherStack);
}


template <class Type>
//our destructor
linkedStackType<Type>::~linkedStackType()
{
    initializeStack();
}

template <class Type>
//Our assignment operator
const linkedStackType<Type>& linkedStackType<Type>::operator=
    			  (const linkedStackType<Type>& otherStack)
{
    if (this != &otherStack)
        copyStack(otherStack);

    return *this;
}

#endif
