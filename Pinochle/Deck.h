/*
************************************************************
* Name:  Nitesh Parajuli                                   *
* Project:  Project 1 Pinochle C++				           *
* Class:  CMPS366 OPL				                       *
* Date:  09/29/2020				                           *
************************************************************
*/



#ifndef DECK_H
#define DECK_H
#include<vector>
#include<iostream>
#include"Card.h"
#include<algorithm>
#include<random>
#include<chrono>
#include<sstream>

using namespace std;

class Deck
{
public:

	//Deck class constructor
	Deck();

	//Deck  class destructor
	~Deck();

	//Accessors
	const int firstCardPos() { return mTopCardPos; }
	vector<Card*> getDeck() { return this->mdeck; }
	

	//Utility functions
	void shuffleDeck();
	Card* drawCard();
	void loadDeck(string deck);
	void createNewDeck();
	void displayStockPile();


private:
	// vector containing all shuffled cards 
	vector<Card*> mdeck;

	// index of the next card to be used from mDeck
	int mTopCardPos;
};





#endif