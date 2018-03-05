////////////////////////////////////////////////////////
// Name: Steven Diamante
// Class: ECE 2574
// File name:   searchmap.cpp
// Description: This is a program that will read in a text file containing a flightplan
//              and write an output file that determines the path and cost of each reachable
//              destination.
// Date:        11/5/2014
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <stdlib.h>
#include "stackP.h"
#include "mapclass.h"

using namespace std;



int main(int argc, char* argv[]) {
  ifstream inputFile;
  ofstream outputFile;
  cityType originCity;
  cityType fromCity, toCity, newCity;
  int cost;
  Map newmap;
  Stack Route;
  vector<cityType> destination_Array;
  vector<cityType>::iterator D_it;
  bool norepeats = true;
  
  // The program should take 3 input parameters.
  if (argc != 3) {
    cerr << "Usage: ./search_map input.txt output.txt" << endl;
    return -1;
  }

  // Open the input file and output file.
  inputFile.open(argv[1]);
  if (!inputFile) {
    cerr << "Cannot open input file!!!" << endl;
    return -1;
  }
  
  outputFile.open(argv[2]);
  if (!outputFile) {
    cerr << "Cannot open output file!!!" << endl;
    return -1;
  }

  
  // First read in the origin city.
  inputFile >> originCity;
  if (inputFile.fail()) {
    cerr << "input file is Invalid!!!" << endl;
    return -1;
  }


  // Now read in the data from the input file.
  while(!inputFile.eof())
  {
    inputFile >> fromCity >> toCity >> cost;
    // test whether file stream fails.
    if (inputFile.fail()) {
      inputFile.clear();
      inputFile.ignore(1024, '\n');
      continue;
    }
	newmap.addAdjCity(fromCity, toCity, cost); // Make map of city paths and costs
  }

  // print start of table
	outputFile << endl << left << setw(15) << "Destination" << right << setw(15);
	outputFile << "Flight Route from " << originCity << right << setw(15) << " Total Cost" << endl;

	// --------------------------------------------------------------------------------------------------
	// Setting up vector of destinations
	for(newmap.it = newmap.travelCost.begin(); newmap.it != newmap.travelCost.end(); newmap.it++) // iterating through map <string, int> 
	{
	norepeats = true;
		for(unsigned int n = 0; n < destination_Array.size(); n++) // checking through the vector of destinations
			{
			if(newmap.it->first[1] == destination_Array[n] || newmap.it->first[1] == originCity) // check for repeats and origin
				norepeats = false;
			}
	if(norepeats) // load city if it isn't already in the vector or the origin
		destination_Array.push_back(newmap.it->first[1]);
	}

	// visit all destinations
	for(unsigned int n = 0; n < destination_Array.size(); n++)
	{
	newmap.Travel(originCity, destination_Array[n]);
	// print out flight path or if path not found go to next destination
	if(newmap.travelPossible) // If the destination is possible, then print to the output file
	{
		outputFile << right << setw(5) << destination_Array[n] << right << setw(15);
		while(!newmap.newRoute.isEmpty()) // use newRoute to print the stack to the output file
		{
		newmap.newRoute.getTop(newCity);
		newmap.newRoute.pop();
		outputFile << newCity << " ";
		}
		outputFile << right << setw(17) << newmap.totalCost << endl;
	}
	else
		outputFile << ""; // dummy space
	}
	 
  // close files
  inputFile.close();
  outputFile.close();
  
	
	cin.get();	// pause display
	return 0;


} // End main
