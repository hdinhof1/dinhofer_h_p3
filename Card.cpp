//
//  Card.cpp
//  
//
//  Created by Henry on 2/12/15.
//
//

#include "Card.h"
#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <string>
#include <vector> 
#include <locale>
#include <queue>


Card::Card (string n) {
	int space = n.find(" ");
	name = n.substr(0, space);
	string val = n.substr(space+1, n.length() - 1 );
	value = atoi(val.c_str());
	weight = profit= ratio = 0;
	cout << "Card set to " << name << " and value "<< value << " weight:" << weight << endl;
}

Card:: Card ( string n, int v, int p, int w) {
	
	value = v;
	name = n;
	profit = p;
	weight = w;

	// makes sense to just strip the int out from the string getline
	
	/*
	a = first;
	b = second;
	//ofstream outf;
	outf.open(outFileName);
	//outf.open(argv[2]);
	if (outf.is_open() ) {
		cout << "Opened outputfile"<<endl;
	}
	else {
		cout << "Error opening file " <<endl;
	}
	*/
}
Card::Card (Card &c, vector <Card> &mpf) {
	if (isFound (c, mpf) ) {
		value = c.value;
		name = c.name;
		profit = c.profit;
		//Card temp = mpf.find (c);
		//cout << "indexVal " << indexVal << endl;
	}
}
Card:: Card(const Card & aCard)
{
//	cout << "Copying via assignment operator" << endl;
	*this = aCard;
}

void Card::setValue (string n, int v) {
	value = v;
}
string Card::getName () const{
	return name;
}
int Card::getValue () const{
	return value;
}
int Card::getWeight() const{
	return weight;
}
int Card::getProfit() const{
	return profit;
}
int Card::getRatio() const{
	return ratio;
}
void Card::setProfitRatio (int w) {
	weight = w;
	profit = (getValue() - w );
	ratio = ( getProfit() / getWeight() );
	cout << "ratio is set to " << ratio << endl;
}

bool Card::isFound (Card &c, vector <Card> card ) {
	bool b = false;
	for (int i = 0; i < card.size(); i++ ) {
		if (card[i] == c)
		{b = true; }
	}
	return b;
}

int Card::getIndex (Card &c, vector <Card> card)
{
	int finalVal = -1;
	for (int i = 0; i < card.size(); i++ ) {
		if (card[i] == c) {
			finalVal = i;
			cout << "finalVal is " << finalVal << " i is " <<i <<endl;
		}
	}
	return finalVal;
}

// Operator overload
//  Reversed to sort into descending profit/weight ratios
bool Card::operator > (const Card & right) const {
	Card p = right;
	Card p2 = *this;
	return (p2.ratio < p.ratio);
}

bool Card::operator < (const Card & right) const {
	Card p = right;
	Card p2 = *this;
	return (p2.ratio > p.ratio);
}

bool Card::operator () (const Card &left, const Card &right) const  {
	return left.ratio  < right.ratio;
}

bool operator == (const Card &c1, const Card &c2 )  {
	return c1.name == c2.name;
}


int operator+ ( const Card &c1, const Card &c2) {
	//if (c1 == c2)
	//{
		return (c1.value - c2.value);
		//c2.setValue (c1.value - c2.value);
	//}
}
// Takes in int index value
// Returns right child index
int leftChild( int i) {return ( (2*i) +1); }
// Takes in int index value
// Returns right child index
int rightChild (int i) {return ( (2*i) + 2 );}

// Solution Set to push correct card to?
void DFS (int i, int tier, int n, vector<Card> data) {
	int l, r;
	l = leftChild(i);
	r = rightChild(i);
	if (l >= n || r >= n) {
		//cout << "Uh-oh heap[ " << i << "]: " << heap[i] << endl;
		return;
	}
	else {
	//	cout << "reached heap[ " << i << "]: " << heap[i] << endl;
	//	cout<< " queue at q[ " <<tier << "]: " << q.front() << endl;
	//	q.pop();
		DFS(l, tier+1, n, data);
		DFS(r, tier+1, n, data);
		// explore v
		// DFS (left (v))
		// DFS (right (v))
	}
}
vector<Card> Card::computeMaxProfit (vector<Card> I, int W)
{
	int maxProfit =0;
	vector <Card> S; // current set to consider
	vector <Card> M; // current maxProfit subset
	int sum =0;
	int currentProfit = 0;
	for (int i= 0; i< I.size(); i++) {
		sum += I[i].getWeight();
		maxProfit += I[i].getValue();
		Card copy = I[i];
		M.push_back(copy );
	}
	if ( sum <= W) {
		return M;
	}
	else {
		
		sum = maxProfit = 0; //reset
		for (int i = 0; i < I.size(); i++) {
			if ( (sum += I[i].getWeight() ) <= W) {
				sum+= I[i].getWeight();
				currentProfit += I[i].getValue();
				Card copy = I[i];
				S.push_back(copy);
			}
		}
		if (currentProfit > maxProfit ) {
			maxProfit = currentProfit;
			M.clear();
			for (Card c: S) {
				Card copy = c;
				M.push_back(copy); }
		}
		//Utilizes next permutation function to go through all possible subsets, brute force

		while (next_permutation(I.begin(), I.end()  ))
		{
			sum = currentProfit = 0;
			for (int i = 0; i < I.size(); i++ ) {
				if ( (sum += I[i].getWeight() ) <= W) {
					sum+= I[i].getWeight();
					currentProfit += I[i].getValue();
					Card copy = I[i];
					S.push_back(copy);
				}
			}
			if (currentProfit > maxProfit ) {
				maxProfit = currentProfit;
				M.clear();
				for (Card c: S) {
					Card copy = c;
					M.push_back(copy); }
			}
		}
	}
	return M;

}
Card &Card::operator=(const Card& right) {
	value = right.getValue();
	name = right.getName();
	profit = right.getProfit();
	weight = right.getWeight();
	ratio = right.getRatio();
	return (*this);
}

ostream & operator << (ostream &out, const Card &c) {
	
	Card copy = c;
	//if (copy.carValue == 13)  ...cout
	out <<copy.name << " val:"<< copy.value <<" profit: "<<copy.profit << " weight:"<< copy.weight <<" ratio: "<< copy.ratio << " ";
	
	
	return out;
}







