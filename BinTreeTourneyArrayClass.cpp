#pragma once
#include<iostream>
#include<fstream>
#include<cassert>
#include<string>
#include<random>
#include<ctime>
#include "BinTreeTourneyArray.h"

//Author: Sean Mathews
//File: BinTreeTourneyArrayClass.cpp
//Date Modified: 12/6/2017
//Description: Finishing a couple functions for a tournament to commence in a binary tree format

using namespace std;

BinTreeTourneyArray::BinTreeTourneyArray()
{
	contestList = nullptr;
	contestants = arraySize = 0;
}

BinTreeTourneyArray::BinTreeTourneyArray(const BinTreeTourneyArray &btta)
{
	contestants = btta.contestants;
	arraySize = btta.arraySize;
	contestList = new elementType[arraySize];
	for (int i = 0; i < arraySize; i++)
		contestList[i] = btta.contestList[i];
}
BinTreeTourneyArray& BinTreeTourneyArray::operator = (const BinTreeTourneyArray &btta)
{
	if (contestList != nullptr)
		delete[] contestList;
	contestants = btta.contestants;
	arraySize = btta.arraySize;
	contestList = new elementType[arraySize];
	for (int i = 0; i < arraySize; i++)
		contestList[i] = btta.contestList[i];
	return *this;
}
BinTreeTourneyArray::~BinTreeTourneyArray()
{
	if (contestList != nullptr)
		delete[] contestList;
}

int BinTreeTourneyArray::getNumContestants() const
{
	return contestants;
}

int BinTreeTourneyArray::getArraySize() const
{
	return arraySize;
}

//From ExploringBinary.com
int BinTreeTourneyArray::isPowerOfTwo(int x)
{
	while (((x % 2) == 0) && x > 1) /* While x is even and > 1 */
		x /= 2;
	return (x == 1);
}

void BinTreeTourneyArray::loadTournament(istream &infile)
{
	
	

	infile >> contestants; //reads in number of contestants
	 //outputs the number of emptyrows to print
	int startingEmptyNodes = (contestants - 1);
	arraySize = contestants + startingEmptyNodes;//number of empty nodes + contestants that are read in is the array's size

	//while the file didnt hit the eof, first read in the number of rows, then 
	string contestantName;
	
	delete[] contestList;
	contestList = nullptr;

	contestList = new string[arraySize];//this creates a dynamic array of array size
	//if you arent at index "numberOfContestants" then print empty, then go on to print the rest of the list
	
	for (int i = 0; i < startingEmptyNodes; i++)
	{
		contestList[i] = EMPTY_SPOT;
	}
	
		//read in names
	for (int i = startingEmptyNodes; i < arraySize; i++) 
	{
		infile >> contestantName;//reads in name

		contestList[i] = contestantName;//reads in each name into an index
	}

	/*while (infile.good()) {
		 
		infile >> contestantName >> " " >> contestantName;
		arraySize += 2;


	}*/
}

void BinTreeTourneyArray::printDownward(ostream &outStream)
{	
	

	int numberOfEmptyRows = log2(contestants);
	int numberOfEmptyNodes = contestants - 1;

	int prevResult = 0; // this uses the previous result to help print stuff
	// 0 + 2^1 = 2 2,6, etc represent the actual index numbers, which is what i is
	// 2 + 2^2 = 6
	// 6 + 2^3 = 14
	// 14 + 2^4 = 30
	int powerTracker = 0;//this is used to increment the power tracker to know when to print 
	int endOfEmptys = 0;//the reference that will be used to determine whether an endl will occur or not
	int indexesWithEmptys = 0;

	//make a tracker to keep track of where what indexs ur at, but thats i...

	//ok so i want this thing to be able to know how many rows there are,i have that, and then find the index to make an endl at, then keep doing that until it finds i bigger than number of emptyNoes which is contestants - 1
	//differentiate between an empty and and empty w/ endl
	//if there is 3 empty rows, it implies 0 + 2 + 4
	for (int i = contestants; i < arraySize; i++)
	{
		while (indexesWithEmptys < contestants) { //while you arent printing the contestants, decide between to print an empty or an empty with an endl;

			if (indexesWithEmptys == endOfEmptys) {  
				outStream << contestList[indexesWithEmptys] << endl;
				outStream << endl;										

				powerTracker += 1; //increment powerTracker to get ready to calculate the next index to endl at

				prevResult = endOfEmptys;//what this does is assign the PREVIOUS endOfEmptys to prevResult, allowing it to go to the next index when it should have an endl
				endOfEmptys = prevResult + pow(2, powerTracker); // increment the next index number that will determine when to print the 

			}

			else {
				outStream << contestList[indexesWithEmptys] << ":";
			}
			indexesWithEmptys += 1; //increments the indexesWithEmptys to keep it going til you get to an endl
		}

		outStream << contestList[i] << ":";

	}
}

void BinTreeTourneyArray::doContest(ostream& outStream)
{
	// The next three statements were taken/modified from:
	// http://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(0, 1); // from this point on use "dis(gen)" to get a 
											   // random 0 or 1
	
	//int* winLoseArray = new int[arraySize]; 
	//int index = contestList[(arraySize - emptyNodes) - 1]; //this gives starting index for each list possibility
	//while( (isPowerOfTwo(index)) != (isPowerOfTwo(contestants)) )//this is saying  [|empty|empty|empty|a|b|c|d|] 
	//while 
		
	
	int roundCounter = 0;
	
	int safeArraySize = arraySize;
	int safeContestants = contestants;//put these in references to not lose data

	for  (int i = safeContestants - 1; i < safeArraySize; i++)// this will execute when a round has completed 
	{
		roundCounter++;
		cout << "Round: " << roundCounter;
		cout << endl;

		//so all the stuff needs to be moved and decided in here, including the reassigning the names at index whatever to index 2 1 0
		//outcomePerson1 will always have an odd index number, person2 will have even index number
		for (int subRound = safeContestants - 1; subRound < safeArraySize; subRound += 2)
		{
			int Winner = ( (subRound - 1) / 2);

			int outComePerson1 = dis(gen) % contestants; //represents one contestant's winner or loser will be decided, outcome is the 1 or 0 for each node, also represents the other person's winner or loser
			int outComePerson2 = dis(gen) % (contestants + 1); //i represents the index where the

			//this takes care when you both have 2 losers or winner, once it breaks then outcomePerson1 and 2 will be different
			while (outComePerson1 == outComePerson2) {
				outComePerson1 = dis(gen) % subRound;
				outComePerson2 = dis(gen) % (subRound + 1);

			}
			//display stuff
			

			cout << contestList[subRound] << " vs " << contestList[subRound + 1];

			if (outComePerson1 == 1) {
				//which is index 3, then move index3 to i-2
				//contestList[subRound - 2] = contestList[subRound];//out of the two contestants, 

				//contestList[] = contestList[subRound - 2];

				cout << "	Winner: " << contestList[subRound] << endl;
				contestList[Winner] = contestList[subRound];

			}


			else
			{
				//contestList[subRound - 2] = contestList[subRound + 1];
				cout << "	Winner: " << contestList[subRound + 1] << endl;
				contestList[Winner] = contestList[subRound + 1];
			}

		}
		//decrease everything by half
		safeArraySize = (safeArraySize / 2); //half the arraySize
		safeContestants = (safeContestants / 2); // half the number of contestants
		i = safeContestants - 1; // to reset the round 
	}

	cout << "Champion: " << contestList[0];



	



}
