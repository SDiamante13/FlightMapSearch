////////////////////////////////////////////////////////
// ECE 2574, Homework 3, Steven Diamante
// File name: mapclass.cpp
// Description: Implementation file for the ADT Map
// Date: 10/31/2014


#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <string>
#include <map>
#include <vector>
#include <stdlib.h>
#include "stackP.h"
#include "mapclass.h"
using namespace std;


// Constructor: create an map;
Map::Map()
{
	totalCost = 0;
};



// Destructor: deallocate memory that was allocated dynamically
Map::~Map()
{

};

// create map of city paths and costs, store as map<string, int> travelCost
void Map::addAdjCity(cityType fromCity, cityType toCity, int cost)
{
  char pathChar[2];
  pathChar[0] = fromCity;
  pathChar[1] = toCity;
  string pathString = string(pathChar);
  pathString.resize(2);
  travelCost[pathString] = cost;
};

// Find the next city path
// if a path does not exist backtrack and find another path
void Map::getAdjCity(cityType& currentCity)
{
  map<string, int>::iterator it;
  bool found = false;
  for(it = travelCost.begin(); it != travelCost.end(); it++)
  {
	  if(it->first[0] == currentCity && !isVisited(it->first[1]))
	  {
		  currentCity = it->first[1];
		  Route.push(currentCity);
		  markVisited(currentCity);
		  totalCost += it->second;
		  found = true;
		  break;
	  }
  }
  if(!found) // if newCity is not found, pop from stack
	{	
		Route.pop();
		cityType backtrack;
		Route.getTop(backtrack);
		char backChar[2];
		backChar[0] = backtrack;
		backChar[1] = currentCity;
		string pathString = string(backChar);
		pathString.resize(2);
		totalCost -= travelCost.at(pathString);
	}
  };

// Mark currentCity as visited
// visitedCities is a vector of cityTypes
void Map::markVisited(cityType currentCity)
{
	visitedCities.push_back(currentCity);
};

// isVisited(someCity) will check is someCity has already been visited
bool Map::isVisited(cityType someCity)
{
	bool visitedFlag = false;
	for(unsigned int n = 0; n < visitedCities.size(); n++)
	{
		if(visitedCities[n] == someCity) // this city has been visited
			visitedFlag = true;
	}
return visitedFlag;
};

// Clear the visited cities 
void Map::clearVisitedCities()
{
	visitedCities.erase(visitedCities.begin(), visitedCities.end());
};

// Function to print flight map for testing purposes
void Map::printMap() 
{
	for(it = travelCost.begin(); it != travelCost.end(); it++)
	{
		cout << it->first << right << setw(5) << it->second << endl;
	}
};

	

void Map::Travel(cityType origin, cityType destination)
{
	cityType topCity;
	cityType cityStack;
	const cityType trueOrigin = origin; 
	while(!newRoute.isEmpty())
	newRoute.isEmpty(); // clear last stack
	clearVisitedCities();
	travelPossible = true; 
	totalCost = 0; // reset total Cost 
	Route.push(origin); // origin is the first city in the stack
	markVisited(origin); // Mark Origin city as visited
	getAdjCity(origin); // find next city
	topCity = origin;

	while(topCity != destination && travelPossible) // Look for path 
	{
	getAdjCity(origin); // find next city
	Route.getTop(origin); // get top of stack
	topCity = origin; // topCity is the new current city
		if(topCity == trueOrigin) //  A route was never found
			travelPossible = false;
	} // end of destination loop
	if(travelPossible) // stores stack into vector currentStack
	{
		while(!Route.isEmpty())
		{ 
		Route.getTop(cityStack);
		newRoute.push(cityStack);
		Route.pop();
		}
	}
};





