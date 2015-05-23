//
//  Card.h
//  
//
//  Created by Henry on 2/12/15.
//
//

#ifndef ____Card__
#define ____Card__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>
#include <vector>
#include <list>


using namespace std;

class Card {
private:
	int value;
	string name;
	int  profit;
	int weight;
	int ratio;
	//ofstream outf;

public:
	
	Card (string n);
	Card(string name, int value, int profit, int weight);
	Card (Card &c, vector<Card> &v);
	Card (const Card & aCard);
	bool isFound (Card &c, vector <Card> card);
	vector<Card> computeMaxProfit(vector<Card> I, int W);
	Card &operator= (const Card &right);
	bool operator > (const Card & right) const;
	bool operator < (const Card &right) const;
	bool operator () (const Card &left, const Card & right) const;

	friend int operator+ ( const Card &c1,  const Card &c2);
	friend bool operator== (const Card &c1, const Card &c2);
	void setValue (string n, int v);
	void setProfit (Card c);
	void setProfitRatio (int w);
	string getName() const;
	int getValue() const;
	int getProfit() const;
	int getWeight() const;
	int getRatio() const;
	int getIndex(Card &c, vector <Card>card);
	//void DFS (int, int, int, queue<int> );
	friend ostream & operator << (ostream&out, const Card &c);
	
	//bool operator== ( const Nick &n1, const Nick &n2)
	//{
	//	return n1.username == n2.username;
	//}

	//string createName(string val);
	
	
	//friend isPowerOfTwo (unsigned int x);
	
};


#endif /* defined(____Card__) */
