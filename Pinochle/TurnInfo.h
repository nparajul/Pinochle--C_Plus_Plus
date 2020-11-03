/*
************************************************************
* Name:  Nitesh Parajuli                                   *
* Project:  Project 1 Pinochle C++				           *
* Class:  CMPS366 OPL				                       *
* Date:  09/29/2020				                           *
************************************************************
*/

#pragma once
#ifndef TURNINFO_H
#define TURNINFO_H

#include"Card.h"
#include "Deck.h"



class TurnInfo
{
public:
	TurnInfo(Card* trumpcard, int leadIndex);
	~TurnInfo();

	//accessors
	inline Card* getTrump() { return this->mTrumpCard;}
	inline const int getLeadPlayerIndex(){ return this->mLeadPlayerIndex;}
	inline Card* getLeadCard() { return this->mLeadCard; }
	//mutator
	inline void setLeadCard(Card* card) { this->mLeadCard = card; }


private:
	//private member variables
	Card* mTrumpCard;
	int mLeadPlayerIndex;
	Card* mLeadCard;
	
};



#endif // !TURNINFO_H

