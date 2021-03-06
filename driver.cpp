//
//  driver.cpp
//  
//
//  Created by Henry on 3/3/15.
//
//


#include <stdio.h>
#include <string>
#include <ostream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <time.h>
#include <locale>
#include <queue>
#include "Contestant.h"
#include "Card.h"

using namespace std;

bool by_descending_profit (Card a, Card b) {
	return (a.getProfit() > b.getProfit());
}
// n is size of MPFtotal
/*  profit(v) = sum of profits of all items included in the knapsack up to node v (on a path from root to v)
 
 weight(v) = the sum of the weights of all items included in the knapsack up to node v (on a path from root to v)
upperBound(v) is ≥ the maximum profit that can be found by expanding the whole subtree of the state space tree rooted at v. */

vector<Card> KWF(int i, int weight, int w, int p, int C, int n, vector<Card> data ) {
	int weightSoFar = weight;
	vector<Card> x;
	while ( (weightSoFar < C) && (i < data.size() ) ){
		if (weightSoFar + data[i].getWeight()<= C ) {
			Card c = data[i];
			x.push_back(c);
			weightSoFar += c.getWeight();
		}
		i += 1;
	}
	return x;
}
vector <Card> improve_greedy (vector<Card> greedy1, vector<Card> greedy2) {
	int pmax=0, maxProfit=0;
	for (int i =0; i< greedy1.size(); i++) {
		maxProfit += greedy1[i].getProfit();
	}
	// I thought for loop but could be wrong
	pmax += greedy2[0].getProfit();
	if (maxProfit > pmax) {return greedy1; }
	else {vector<Card> ret; Card max = greedy2[0]; ret.push_back(max);
		return ret; }
}
int compute_upper_bound (int i, int profit, int weight, int C, int n, vector<Card> data) {
	int weightSoFar = weight;
	int bound = profit;
	cout << "compute_upper_bound, bound is set to " << bound << " weightSoFar "<< weight << endl;
	vector<Card> x;
	while ( (weightSoFar < C) && (i < data.size() ) ){
		if ( (weightSoFar + data[i].getWeight() )<= C ) {
			Card c = data[i];
			x.push_back(c);
			weightSoFar += c.getWeight();
			bound += c.getProfit();
			cout << "weightSoFar (C_U_B) is " << weightSoFar << "bound is " << bound << endl;
		}else {
			int remaining = (C- weightSoFar ) * (data[i].getRatio() );
			cout << "remaining is " << remaining << endl;
			bound += ( (C- weightSoFar) * (data[i].getRatio() ) );
			cout << " bound is finally " << bound << endl;
			weightSoFar = C;
		}
		i += 1;
	}
	x.clear();
	return bound;
}
bool promising (int i, int profit,int weight, int C, int maxprofit, vector<Card> data) {
	bool ret = false;
	cout << "\nin promising params int i, int weight, int profit, int C, int maxprofit are " << i << weight << profit << C << maxprofit << endl;
	int weightSoFar = weight+ data[i].getWeight();
	int bound = compute_upper_bound(i+1, profit, weightSoFar, C, data.size(), data );
	cout << "bound at end of promising" << bound << endl;
	if ( (bound > maxprofit) && (weightSoFar <= C) ) {
		ret = true;
		cout << "bound is found promising bound > maxprofit) && (weightSoFar <= C) bound maxprofit weightsofar" << bound <<" " << maxprofit<< " " << weightSoFar << " "<< endl;
	}
	return ret;
}

vector <Card> knapsack (int i, int profit, int weight, int C, vector<Card> data) {
	int maxProfit = 0, numbest= 0;
	vector <Card> bestset;
	// if (weightSoFar = S) print include[1] to include[i]
	cout << "knapsack is called with int i, int profit, int weight, int C, data " << i << profit << weight << C << endl;
	if (weight == C) {
		return bestset;
	}
	if ( (weight <= C) && (profit > maxProfit) ) {
		// save better solution
		    /// update maxprofit numbest and bestset
		maxProfit = profit;
		numbest = i;
		Card c = data[i];
		bestset.push_back(c);
		
	}
	if (promising(i, profit, weight, C, maxProfit, data) ) {
		knapsack(i+1, profit+data[i+1].getProfit(), weight+data[i+1].getWeight(), C, data);
	}
	else {
		knapsack(i+1, profit, weight, C, data);
	}
	//bestset.push_back(
	
}
// struct created if space becomes a problem
struct baseballCard{
	int weight;
	int profit;
	string name;
}; baseballCard mattHarvey; baseballCard davidWright, sample;


int main(int argc, char const *argv[])
{
	clock_t begin = clock();
	
/*	queue <int> q;
	q.push(0); q.push(2); q.push(4); q.push(6);
	DFS(1, 0, q);
	ofstream outf("test.txt");
 */
	string progName(argv[0]);
	cout << endl << "Argc is an integer containing the number of arguments, " << endl;
	cout << "including the program name itself. " << endl << endl;
	cout << "This program contains " << argc << " argument(s)." << endl << endl;
	cout << "You ran this program with " << progName << endl;
	cout << "The other arguments are: " << endl;
	for (int i=1; i<argc; i++)
		cout << "argv[" << i << "]: " << argv[i] << endl;
	// One "C++" way to convert the C-style string in argv[1] into an int
	// Don't forget to #include <sstream>
	if (argc > 1) {
		istringstream buf(argv[1]); // create an input string stream
		int num1;
		buf >> num1; // use the extraction operator
		cout << "argv[1] as an int: " << num1 << endl;
	}
	string line;
	ifstream in (argv[2] ); // market-price-file
	ofstream outf (argv[6], ios::app );
    if (!outf.is_open() || !in.is_open() || argc != 8)  { cout << "error opening input /output files please check again " << argv[2] << " " << argv[4] << endl; exit(0); }
	bool pos = true;
	int totalMPF = 0;
	vector <Card> data; //Card t("Tester 0"); data.push_back(t);
	vector <Card> sub;
//	vector <Card>::iterator It;
	// market-price-file
	if ( in.is_open() ){
		while (!in.eof())
		{
			getline (in, line);
			if (pos) { totalMPF = atoi(line.c_str());
			//	cout << totalMPF << "totalMPF " << endl;
				pos =false;
			}else {
			cout << "Am i inside this loop?" << endl;
			Card c2(line);
			data.push_back(c2);
			}
		}
	}
	in.close();
	//price-list-file
	ifstream prices (argv[4]); // price-list-file
	string input; int subsetSize; int S;
	if ( prices.is_open() ) {
	while (!prices.eof() ) {
		getline (prices, input);
		locale l;
		int space = input.find(" ");
		string temp = input.substr(0, space);
		string val = input.substr(space+1, input.length() - 1 );
		
		if (isdigit (input[0], l) ) {
			subsetSize = atoi(temp.c_str());
			S = atoi(val.c_str());
			cout << "Maximize n: " << subsetSize << " items while spending under $" << S << endl;
			// maximal
			// clear off subarray
		}else {
			Card pedro(input);
			int weight = pedro.getValue();
			int position = pedro.getIndex(pedro, data);
			if ( position == -1) {
				cout<< "Cannot run 32BadPriceList / did you delete the SmallMarketPriceList newline and/or SmallPriceList newline   " <<pedro <<endl;
				bool check = pedro.isFound(pedro, data);
				cout << "checking isFound is true/false: " << check << endl;
				break;
			}
		data[position].setProfitRatio(weight);
			// O(n2) could use a vector iterator
		}
	}
	}
	prices.close();
	
	Card hearts ("Player2 20");
	Card spade("Player3 15");
	Card negative ("PlayerOcho -20"); negative.setProfitRatio(5);
	//data.push_back(negative);
	Card moVaughn ("Movaughn 1492");
	bool check = moVaughn.isFound(moVaughn, data); cout << "checking isFound is true/false:" << check << endl;
	int position = spade.getIndex(spade, data);
	cout <<"size of Card " <<sizeof(spade) << " getIndex check position = "<<position << endl;
	
	for (Card c : data) {cout << c << endl; }
	//qsort (&data, totalMPF, sizeof(Card), compare);
	
	// faster than quicksort, does Nlogn

	cout << "size of mattHarvey " << sizeof(mattHarvey) << endl;
	cout << "size of int " << sizeof (int ) << endl;

	sort (data.begin(), data.end());
	cout << "\n descending ratio order" << endl;
	for (Card c : data) {cout << c << endl; }
	vector <Card> greedy1 = KWF(0, 0, 0,0 ,S, data.size(), data );
	cout << "\n KWF greedy1 " <<endl;
	for (Card c : greedy1) {cout << c <<endl; }
	cout << "\n by_descending_profit" << endl;
	sort (data.begin(), data.end(), by_descending_profit );
	int maxProfit = data[0].getProfit();
	vector <Card> greedy2 = KWF(0, 0, 0,0 ,S, data.size(), data );
	cout << "S is currently: " << S << endl;
	for (Card c : greedy2) {cout << c << endl; outf << c << endl; }
	
	cout << "is the first node promising? " << promising(0, 0, 0, S, 0, data) << endl;
	
	//vector<Card> knap = knapsack(0, 0, 0, S, data);
	
	
	clock_t end = clock();
	double t_elapsed = double (end - begin) / (CLOCKS_PER_SEC);
	cout <<"Time elapsed is currently: "  << t_elapsed << endl;
	
	
	return 0;
}
