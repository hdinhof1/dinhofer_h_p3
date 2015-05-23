//
//  Contestant.cpp
//  
//
//  Created by Henry on 3/3/15.
//
//

#include "Contestant.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <math.h>

// Contestant is set to null (-1, -1)
Contestant::Contestant() {
	id = -1;
	points = -1;
}

Contestant::Contestant (int n, int p) {
	id = n;
	points = p;
}
Contestant::Contestant (int n, int p, string fileName) {	
	id = n;
	points = p;
	outf.open(fileName, ios::app);
	if (outf.is_open() ) {
	//	cout << "Opened outputfile in Contestant"<<endl;
	}
	else {
		cout << "Error opening output file " <<endl;
	}
}
Contestant:: Contestant(const Contestant & aContestant)
{
	id=points = 0;
	//Copying via assignment operator
	*this = aContestant;
}
int Contestant::getPoints () const{
	return points;
}
int Contestant::getID() const{
	return id;
}
void Contestant::setContestant (int canIHaveYourNumber, int point) {
	id = canIHaveYourNumber;
	points = point;
}
// Min-heap
// percolate down
void Contestant::Heapify (vector <Contestant> &eH, int i, int n)
{
	//provided that i is the value to compare
	int l, r, smallest =i; //index values for left, and right subchildren, larger val
	l = leftChild(i); // get the left child
	r = rightChild(i); // get the right child
	if((l < n ) && (eH[l] < eH[i])) {
		smallest = l; //set smallest to l
	}else {smallest = i;} //set smallest to i
	if((r < n ) && (eH[r] < eH[smallest])){
		smallest = r;
	}
	if(smallest != i) // one of the two child nodes has proved
		// smaller than eH[i], so interchange values
	{
		//push smaller child up, parent down
		Contestant temp = eH[i];
 		eH[i] = eH[smallest];
		eH[smallest] = temp;
		//cout << "calling heapify with smallest "<< smallest<< " n:  " << n << endl;
		Heapify(eH, smallest, n);
	}
}
void Contestant::makeHeap(vector <Contestant> &eH, int n) {
	//int h = (eH.size() - 1 ) /2;
	for (int j = n/2; j >= 1; j-- )
	{
		Heapify(eH, j, n);
	}
}

// Takes in int index value
// Returns left child index
int Contestant::leftChild( int i)
{
	return ( (2*i));
}
// Takes in int index value
// Returns right child index
int Contestant::rightChild (int i)
{
	return ( (2*i) + 1 );
}
// Find the element with id = <k> in O(1) running time.
void Contestant::findContestant (int id, vector<Contestant> eH, vector<Contestant> hA) {
	//return in O(1) time
	if (hA[id].getPoints() != -1 && hA[id].getID() == id) // set lower bound to -1000 for lowest score
	{	 int index = hA[id].getPoints();
		 outf << "Contestant <" << id  << "> is in the extended heap with score <"   <<eH[index].getPoints() << ">." << endl;
	}
	else if (id <eH.size() || hA[id].getPoints() == -1) { // was unsure whether to add && ( id <0 )
		outf<< "Contestant <" <<id << "> is not in the extended heap." << endl;
	}
	else {
		cout << "Error in findContestant given id: " << id<< endl;
	}
	
}
// Insert a new contestant with id = <k> and score = <s> into the extended heap.
void Contestant::insertContestant (int id, int score, string fileName, int heapMax, vector<Contestant> &eH, vector<Contestant> &hA){
	if ( (eH.size() +1) > heapMax ) {
		outf << "Contestant <" <<id << "> could not be inserted because the extended heap is full." << endl;
	}else {
		if ( Contestant::inHeap(id, eH) ) {
		outf<< "Contestent "<< id << " is already in the extended heap: cannot insert" << endl;
		}else {
		Contestant comeondownn (id, score, fileName);
		//cout << comeondownn << endl; Debug
		eH.push_back(comeondownn);
		int size = eH.size()-1;
		while (size >= 1 && comeondownn < eH[size/2] ) {
		//	cout << "size is: " << size << " setting  "  << eH[size] << " = to " << eH[size/2] << endl; Debug percolate_up
			eH[size] = eH[size /2];
			size /= 2;  // swap up, percolate_up
		}
		//cout << "size exits at what value: " << size << endl; Debug
		eH[size] = comeondownn;
		fixHandles(eH, hA);
			outf << "Contestant <" <<id << "> inserted with initial score <" << score<< ">." << endl;
	}
	}
}
// Remove the contestant with the lowest current score
void Contestant::eliminateWeakest (vector <Contestant> &eH, vector<Contestant> &hA, int n) {
	if (n <= 1) {
		outf << "No contestant can be eliminated since the extended heap is empty." << endl;
	}else {
		eH[1].makeHeap (eH, n);
		Contestant eliminated = eH[1];
		int key = eH[1].getID();
		eH[1] = eH[eH.size()-1];
		n -= 1;
		eH.pop_back();
		eH[1].Heapify (eH, 1, n);
		hA[key].setContestant(-1, -1);
		fixHandles (eH, hA); // O(n)
		outf << "Contestant <"<< eliminated.getID() <<"> with current lowest score <"<< eliminated.getPoints() << "> eliminated." << endl;
	}
}
// Add <s> points to the contestant with id = <k>
void Contestant::earnPoints (int id, int pointsToAdd, vector <Contestant> &eH, vector <Contestant> &hA) {
	if (eH[hA[id].getPoints()].getPoints()> 0) {
		int current = eH[hA[id].getPoints()].getPoints();
		current+= pointsToAdd;
		eH[hA[id].getPoints()].setContestant(id, current);
		Heapify(eH, hA[id].getPoints(), eH.size() ); // percolate_down
		fixHandles(eH, hA);
		outf<< "Contestant <" <<id << ">’s score increased by <" << pointsToAdd <<"> points to <"<<  current <<">."<<endl;

	}else {
		outf<< "Contestant <"<< id <<"> is not in the extended heap." << endl;
	}
}
// Take away <p> points from the contestant with id = <k>.
void Contestant::losePoints (int k, int p, vector <Contestant> &eH, vector <Contestant> &hA) {
	if (eH[hA[k].getPoints()].getPoints()> 0 ) {
		int score = eH[hA[k].getPoints()].getPoints();
		score -= p;
		Contestant loser = eH[hA[k].getPoints()];
		loser.setContestant(k, score);
		outf << "Contestant <" <<k <<">’s score decreased by <"<< p <<"> points to <" << score <<">." << endl;
		if (hA[id].getPoints() != 1) { // need to percolate up if position isn't root
			int size = eH.size()-1;
			while (size >= 1 && eH[hA[k].getPoints()] < eH[size/2] ) {
				eH[size] = eH[size /2];
				size /= 2;  // swap up, percolate_up
			}
			eH[size] = loser;
			fixHandles(eH, hA);
		}
	}else {
		outf << "Contestant <" << k<< "> is not in the extended heap." << endl;
	}
}
// Print the contents of the extended heap.
void Contestant::showContestants(vector<Contestant> eH ) {
	if (eH.size() > 1) {
		for (int i = 1; i <eH.size(); i++) {
			outf << "Contestant <" <<eH[i].getID() << ">" << "in extended heap location <" << i << "> with score <" << eH[i].getPoints() << ">."<< endl;
			cout << "Contestant <" <<eH[i].getID() << ">" << "in extended heap location <" << i << "> with score <" << eH[i].getPoints() << ">."<< endl;
		}
	}
	else {
		cout << "Empty array! cant showuanyContestants!" << endl;
	}
}
// Print the contents of the handle array in order, one value per line
void Contestant::showHandles(vector<Contestant> &hA, int n) {
	if (n > 1) {
		for (int i = 1; i < hA.size(); i++ ) {
			if (hA[i].getPoints() == -1 ) {
				outf << "There is no Contestant <"<<i << "> in the extended heap: handle[<"<< i<<">] = -1." << endl;
			}else {
				outf << "Contestant <" << i<< "> stored in extended heap location <"<<hA[i].getPoints()<< ">." << endl;}
		}
	}else {
		outf << "There is no Contestant <"<< n<< "> in the extended heap: handle[<"<< n << ">] = -1."<< endl;
	}
}
// Show the location of the contestant with id <k> in the heap
void Contestant::showLocation(int id, vector <Contestant> &hA) {
	if (hA[id].getID() == -1) {
		outf << "There is no Contestant <"<<id << "> in the extended heap: handle[<"<< id<<">] = -1." << endl;
	}else {
	outf << "Contestant <" << id<< "> stored in extended heap location <"<<hA[id].getPoints()<< ">." << endl;
	}
}
// Remove all contestants from the extended heap, in order, until only one remains
void Contestant::crownWinner(vector <Contestant> &eH, vector<Contestant> &hA, int n) {
	eH[1].makeHeap (eH, n);
	for (int i=n; i > 2; i--) { // assumes that crownWinner isn't run on first take
		int key = eH[1].getID();
		hA[key].setContestant(-1, -1);
		eH[1] = eH[eH.size()-1];
		eH.pop_back();
		eH[1].Heapify (eH, 1, i-1);
		hA[key].setContestant(-1, -1);
		fixHandles (eH, hA); // O(n)
	}
	outf << "Contestant <" << eH[1].getID() << "> wins with score <"<< eH[1].getPoints() <<">!" << endl;
}

// Checks to see if <k> is in handle array
bool Contestant::inHeap (int id, vector <Contestant> hA) {
	bool token = false;
	if (hA[id].getPoints() > 0 ) {return true; }
	else {
		return false;
	}
}
// Initialize all values in handle array
void Contestant::setHa (int maxInt, vector <Contestant> &hA ) {
	Contestant set; 
	for (int i = 0; i< maxInt; i++) {
		hA.push_back(set);
	}
}
// Helper function fixes handle array values
// hA[k].getPoints() = position in extended heap
void Contestant::fixHandles (vector <Contestant> &eH, vector<Contestant> &hA) {
	for (int i=1; i<eH.size(); i++ ) { // O (n)
		int k = eH[i].getID();
		hA[k].setContestant(k, i);
	}
}
// Operator overload
Contestant &Contestant::operator=(const Contestant& right) {
//	cout << "Called assignment operator." << endl;
	id = right.getID();
	points = right.getPoints();
	return (*this);
}

bool Contestant::operator==(const Contestant& right) const {
	Contestant p = right;
	Contestant p2 = *this;
	
	return (p2.id == p.id);
}
bool Contestant::operator < (const Contestant & right) const {
	Contestant p = right;
	Contestant p2 = *this;
	return (p2.points < p.points);
}

bool Contestant::operator > (const Contestant & right) const {
	Contestant p = right;
	Contestant p2 = *this;
	return (p2.points > p.points);
}
bool isLesserThan(char c)
{
	switch (c)
	{
		case '<':
			return true;
		default:
			return false;
	}
}
bool Contestant::has_lessThan (string line) {
	for (int i =0; i<line.length(); i++) {
		if (line[i] == '<') {return true;}
	}
	return false;
}

ostream & operator << (ostream &out, const Contestant &c) {
	Contestant copy = c; //operator= overload
	out << "Contestant <" << copy.getID() << ">  points <"<< copy.getPoints() <<">";
	return out;
}