/*
************************************************************
* Name:  Nitesh Parajuli                                   *
* Project:  Project 1 Pinochle C++				           *
* Class:  CMPS366 OPL				                       *
* Date:  09/29/2020				                           *
************************************************************
*/

#include"pch.h"
#include "TurnInfo.h"


/* *********************************************************************
Function Name: TurnInfo
Purpose: To construct a turninfo object
Parameters:
	trumpCard - pointer to a card object, the trump card of the round
	leadIndex - int, the index of the lead player
Return Value: None
Algorithm: Constructs a turninfo object by initializing member variables.
Assistance Received: None
********************************************************************* */
TurnInfo::TurnInfo(Card* trumpcard, int leadIndex)
{
	this->mTrumpCard = trumpcard;
	this->mLeadPlayerIndex = leadIndex;
}


/* *********************************************************************
Function Name: ~TurnInfo
Purpose: To destruct a turninfo object
Parameters: None
Return Value: None
Algorithm: None
Assistance Received: None
********************************************************************* */
TurnInfo::~TurnInfo()
{

}