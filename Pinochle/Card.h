/*
************************************************************
* Name:  Nitesh Parajuli                                   *
* Project:  Project 1 Pinochle C++				           *
* Class:  CMPS366 OPL				                       *
* Date:  09/29/2020				                           *
************************************************************
*/


#pragma once
#ifndef CARD_H
#define CARD_H
#include "pch.h"
#include<string>


using namespace std;

class Card {


public:

	//Card Class constructor
	Card(string face, string suit);

	//Card class destructor
	~Card();

	// Accessors
	string getFace() { return this->mface; }
	string getSuit() { return this->msuit; }
	const int getActiveMeldNums() { return activeMeldsUsedFor; }

	// Utility functions
	int convertFaceToPoints();
	void showCard();
	void cardDescription();
	inline void setActiveMeldNums(int activeMeldNums){	activeMeldsUsedFor += activeMeldNums;}


private:
	//face value of the card
	string mface;

	// suit value of the card
	string msuit;

	//number of active melds the card is currently used for
	int activeMeldsUsedFor;
};

#endif // !CARD_H