#pragma once
#include<iostream>
#include<fstream>
using namespace std;

typedef string elementType;
typedef elementType* elementTypePtr;

const string EMPTY_SPOT = "empty";

class BinTreeTourneyArray
{
public:
	BinTreeTourneyArray();
	BinTreeTourneyArray(const BinTreeTourneyArray &btta);
	BinTreeTourneyArray& operator = (const BinTreeTourneyArray &btta);
	~BinTreeTourneyArray();
	void loadTournament(istream &infile);
	void printDownward(ostream &outStream);
	void doContest(ostream &outStream);
	int getNumContestants() const;
	int getArraySize() const;
private:
	int isPowerOfTwo(int x);//numbers of rows in binaryTree
	elementTypePtr contestList; //this is actually string* contestList
	int contestants; // the number of contestants
	int arraySize; //the size of the array
};
