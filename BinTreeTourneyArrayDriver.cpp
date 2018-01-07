#include "BinTreeTourneyArray.h"
#include<iostream>
#include<cassert>
#include<string>
#include<fstream>
using namespace std;

int main()
{
	BinTreeTourneyArray myTree;
	ifstream infile;
	infile.open("TourneyNames.txt");
	assert(!infile.fail());
	cout << "\n                Welcome to the Tournament Tree Program!\n\n";
	myTree.loadTournament(infile);
	cout << "Number of Contestants: " << myTree.getNumContestants() << endl;
	cout << "\n\n **************** Pre-Tournament Tree: **************** \n";
	myTree.printDownward(cout);
	cout << "\n **************** Tournament Results: **************** \n";
	myTree.doContest(cout);
	cout << "\n **************** Post-Tournament Tree: **************** \n";
	myTree.printDownward(cout);
	cout << "\n\nThat is all!\n\n";
	cout << "Press 'Enter' to quit.";
	char choice;
	cin.get(choice);
	return 0;
}