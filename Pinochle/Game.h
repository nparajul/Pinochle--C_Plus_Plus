/*
************************************************************
* Name:  Nitesh Parajuli                                   *
* Project:  Project 1 Pinochle C++				           *
* Class:  CMPS366 OPL				                       *
* Date:  09/29/2020				                           *
************************************************************
*/

#pragma once
#include"Round.h"
#include "Deck.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include<string>



class Game {
public:
	//Game class constructor
	Game();

	//Game class destructor
	~Game();

	// Utility function
	void beginGame();
	
private:
	
	// game has 2 players
	Player* players[2];
	Human user1;
	Computer user2;

	// private member variables
	
	unsigned int gameRounds;
	unsigned int nextTurn;
	bool isNewGame;
	vector<string> loadFileRoundDetails;

	//Private Utility functions
	int coinToss();
	void play();
	void loadSavedGame();
	string getValueFromLoadLine(string line);
	string removeLeadingSpaces(string line);

};
