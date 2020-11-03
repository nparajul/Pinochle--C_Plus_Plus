/*
************************************************************
* Name:  Nitesh Parajuli                                   *
* Project:  Project 1 Pinochle C++				           *
* Class:  CMPS366 OPL				                       *
* Date:  09/29/2020				                           *
************************************************************
*/


#pragma once
#include"Card.h"
#include"Deck.h"
#include "TurnInfo.h"
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<map>


class Player
{
public:
	// Player class constrcutor
	Player();

	// Accessors
	inline const vector<Card*> getHandPile() { return mHandPile; }
	inline const vector<Card*> getCapturePile() { return mCapturePile; }
	inline const map < Card*, vector<string>> getMeldMap() { return this->meldMap; }
	inline const unsigned int getPlayerRoundScore() { return this->mPlayerRoundScore; }
	inline const unsigned int getPlayerTotalScore() { return this->mPlayerTotalScore; }
	inline const bool getQuitGame() { return quitGame; }
	inline Card* getLatestMove() { return latestMove; }
	inline Card* getTrumpCard() { return this->trumpCard; }

	// Mutators
	inline void updatePlayerTotalScore(int score) { mPlayerTotalScore += score; }
	inline void addToCapturePile(Card* card) { mCapturePile.push_back(card); }
	inline void updatePlayerScore(int score) { this->mPlayerRoundScore += score; }


	// Utility functions - needed for game play and console outputs
	void printHandCards();
	void printCapturePile();
	void dealSingleCard(Card* card);
	void displayPlayerStats();
	string getActiveMeld();
	void updateMeldMap(Card* card, string meldType);
	int validateMeldCards(vector<Card*> meldCards);
	void clearPilesandScores();


	//Virtual functions
	virtual void userTurn(TurnInfo* turnInfo) = 0;
	virtual void declareMeld() = 0;
	
	// Utility functions for saving/loading
	void savePlayersStats(ofstream &saveFile);
	void loadScores(string score);
	void loadHandPile(string pile);
	void loadCapturePile(string pile);
	void loadMeldPile(string pile, char trumpSuit);
	


protected:

	//protected member variables
	vector<Card*> mHandPile;
	vector<Card*> mCapturePile;
	vector<Card*> mPlayablePile;
	vector<Card*> mMeldPile;
	map < Card*, vector<string>> meldMap;
	map < string, vector<vector<Card*>>> activeMelds;
	Card* latestMove;
	Card* trumpCard;
	int mPlayerRoundScore;
	int mPlayerTotalScore;
	bool quitGame;

	// protected virtual member function
	virtual void makeMove(TurnInfo* turnInfo) = 0;

	// protected utility member functions
	string getMeldType(vector<string> meldCards, char trumpSuit);
	int getMeldPoints(string meldType);
	map<string, vector<vector<Card*>>> totalPossibleMelds(vector<Card*> cards);
	void generateAllCardsCombo(vector<vector<Card*>>&combos, vector<Card*> cards, int requiredLength, int startIndex, int currLength, vector<bool> check);
	map<int, int> bestChaseMove(TurnInfo* turnInfo);
	int bestLeadMove(TurnInfo* turnInfo);
	void removePlayedCard(Card* playedCard);
};
