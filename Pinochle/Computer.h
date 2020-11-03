/*
************************************************************
* Name:  Nitesh Parajuli                                   *
* Project:  Project 1 Pinochle C++				           *
* Class:  CMPS366 OPL				                       *
* Date:  09/29/2020				                           *
************************************************************
*/

#pragma once
#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"

class Computer :public Player
{
public:
	//Computer class contructor
	Computer();

	//Computer class destructor
	~Computer();

private:
	//Utility functions for computer player
	void userTurn(TurnInfo* turnInfo);
	void makeMove(TurnInfo* turnInfo);
	void declareMeld();
};

#endif

