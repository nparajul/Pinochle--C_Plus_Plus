/*
************************************************************
* Name:  Nitesh Parajuli                                   *
* Project:  Project 1 Pinochle C++				           *
* Class:  CMPS366 OPL				                       *
* Date:  09/29/2020				                           *
************************************************************
*/

#pragma once
#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"


class Human :public Player
{
public:
	// Human Class constructor
	Human();

	//Human class destructor
	~Human();

private:
	//utility functions for Human Player
	void userTurn(TurnInfo* turnInfo);
	void makeMove(TurnInfo* turnInfo);
	void declareMeld();
	void getHelp(TurnInfo* turnInfo);
	void meldHelp();


};
#endif // !HUMAN_H

