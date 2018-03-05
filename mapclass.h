////////////////////////////////////////////////////////
// ECE 2574, Homework 3, Steven Diamante
// File name: mapclass.h
// Description: Header file for the ADT Mapclass
// Date: 10/23/2014

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
using namespace std;

// Here the user can specify a different type;
// your implementation should work for double, float, and int
typedef char cityType;

class Map
{

public:
// Constructor: create a map
Map();

// Destructor: deallocate memory that was allocated dynamically
~Map();
void addAdjCity(cityType fromCity, cityType toCity, int cost);
void getAdjCity(cityType& currentCity);
void markVisited(cityType currentCity);
bool isVisited(cityType someCity);
void clearVisitedCities();
void printMap();
void Travel(cityType destination, cityType origin);
void printTable();
map<string, int> travelCost;
map<string, int>::iterator it;
Stack newRoute;
bool travelPossible;
int totalCost;
Stack Route;

private:
vector<cityType> visitedCities;
}; // End mapClass class



// End header file
