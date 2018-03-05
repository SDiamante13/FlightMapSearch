////////////////////////////////////////////////////////
// ECE 2574, Homework 3, Steven Diamante
// File name: stackP.cpp
// Description: Header file for the ADT Stack
// Date: 10/23/2014

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <string>
#include <stdlib.h>
#include "stackP.h"
using namespace std;

class StackException: public logic_error
{
public:
StackException(const string & message = "")
:logic_error(message)
{}
};

// Constructor: create a polynomial in a circular linked listwith a coefficient, exponent, and pointer
Stack::Stack()
{
	topPtr = new node;
	topPtr->next = topPtr; 
	topPtr->prev = topPtr;
}

// Copy constructor: create a deep copy of poly orig
Stack::Stack(const Stack& stackA)
{
	if(stackA.topPtr->next == NULL) // if stack is empty
		topPtr->next = NULL;
	else                      // copy first node
	{
		topPtr = new node;
		topPtr->city = stackA.topPtr->city;
		// deep copy rest of stack
		node *writePtr = topPtr;
		for(node *copyPtr = stackA.topPtr -> next; copyPtr != NULL; copyPtr = copyPtr->next) // pop until isEmpty
		{
			writePtr = new node;
			writePtr = writePtr->next;
			writePtr->city = copyPtr->city;
		}
		writePtr->next = NULL;
	}

};

// Check if the stack is empty
bool Stack::isEmpty() const
{
	if(topPtr->next == topPtr)
		return true;
	else
		return false;
};

// Destructor: deallocate memory that was allocated dynamically
Stack::~Stack()
{
	while(!isEmpty())
	{
	pop();
	}
};

// Push a new city into the stack
void Stack::push(StackItemType newCity)
{
	node *pushPtr = new node;
	if(pushPtr == NULL)
		throw StackException("Out of Memory");
	else
	{	
		node *cur = topPtr->next;
		pushPtr->city = newCity;
		pushPtr->next = cur;
		pushPtr->prev = cur->prev;
		cur->prev = pushPtr;
		pushPtr->prev->next = pushPtr;
	}
};

void Stack::pop()
{
	if(isEmpty())
		throw StackException("Stack is empty");
	else
	{
	node *cur = topPtr->next;
	(cur->prev)->next = cur->next;
	(cur->next)->prev = cur->prev;
	delete cur;
	}
};


void Stack::getTop(StackItemType& topCity)
{
	if(isEmpty())
		return;
	else
		topCity = (topPtr->next)->city;
};




