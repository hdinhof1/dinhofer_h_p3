//
//  Contestant.h
//  
//
//  Created by Henry on 3/4/15.
//
//

#ifndef ____Contestant__
#define ____Contestant__

#include <stdio.h>

#include <string>
#include <list>
#include <ctype.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Contestant;

class Contestant
{
public:
	Contestant();
	Contestant(int, int);
	Contestant (int, int, string);
	Contestant (const Contestant &aContestant);
	int getPoints() const;
	int getID() const;
	void setContestant (int, int);
	void setIndex(int);
	static bool inHeap (int, vector<Contestant> );
	static void setHa (int, vector <Contestant> &ha);
	void fixHandles (vector<Contestant> &eH ,vector<Contestant> &hA);
	void Heapify (vector <Contestant> &eH, int, int);
	void makeHeap (vector<Contestant> &eH, int);
	int leftChild (int);
	int rightChild (int);
	void eliminateWeakest (vector<Contestant> &eH, vector <Contestant> &hA, int n);
	void findContestant(int, vector<Contestant> eH, vector<Contestant> hA);
	void insertContestant(int, int, string,int, vector <Contestant> &eH, vector<Contestant> &hA);
	void earnPoints(int, int, vector<Contestant> &, vector <Contestant> &);
	void losePoints (int, int, vector <Contestant> &eH, vector <Contestant> &hA);
	void showContestants(vector <Contestant> eH);
	void showHandles(vector<Contestant> &, int);
	void showLocation (int, vector<Contestant>&);
	void crownWinner(vector <Contestant> &eH, vector<Contestant> &hA, int n);
	Contestant &operator= (const Contestant &right);
	bool operator== (const Contestant & right) const;
	bool operator < (const Contestant & right) const;
	bool operator > (const Contestant & right) const;
	bool isLesserThan (char);
	static bool has_lessThan (string line);
	static void stripLettersAndLessThanGreaterThan (string &);
	
	friend ostream & operator << (ostream&out, const Contestant &c);

	
private:
	int id;
	int points;
	ofstream outf;
	
};


#endif /* defined(____Contestant__) */
