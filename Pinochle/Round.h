/*
************************************************************
* Name:  Nitesh Parajuli                                   *
* Project:  Project 1 Pinochle C++				           *
* Class:  CMPS366 OPL				                       *
* Date:  09/29/2020				                           *
************************************************************
*/
#pragma once
#include<iostream>
#include "Game.h"
#include "Player.h"
#include<vector>
#include "Card.h"
#include"Deck.h"
#include "TurnInfo.h"

class Round
{
public:

	//Round class constructor
	Round(Player* players[], unsigned int gameRounds,int nextTurn);

	//Round class destructor
	~Round();

	//Utility functions
	void beginRound();
	void loadRoundDetails(vector<string> savedRoundDetails);
private:

	// member variables
	Player** players;
	Deck* tDeck;
	Card* trumpCard;
	unsigned int mGameRounds;
	unsigned int mRoundTurns;
	unsigned int leadPlayerIndex;
	unsigned int chasePlayerIndex;
	bool isNewRound;

	// private member functions
	void dealCards(Player* player, int cards);
	int determineTurnWinner(int leadIndex, int chaseIndex);
	void saveGame();

};