////////////////////////////////////////////////////////
// ECE 2574, Homework 3, Steven Diamante
// File name: stackP.h
// Description: Header file for the ADT Stack
// Date: 10/23/2014

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

// Here the user can specify a different type;
// your implementation should work for double, float, and int

typedef char StackItemType;
class Stack
{

public:
// Constructor: create a stack that contains a dummy node and stores cities, two pointers: prev and next
Stack();
// Copy constructor: create a deep copy of stackA
Stack(const Stack& stackA);
bool isEmpty() const;
// Destructor: deallocate memory that was allocated dynamically
~Stack();
void push(StackItemType newCity);
void pop();
void getTop(StackItemType& topCity);


private:
struct node
{
	StackItemType city; // the city in which you are currently in
	node *next; // always points to dummy node
	node *prev; // 
};
node *topPtr;

}; // End Stack class

// End header file
