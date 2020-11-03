/*
************************************************************
* Name:  Nitesh Parajuli                                   *
* Project:  Project 1 Pinochle C++				           *
* Class:  CMPS366 OPL				                       *
* Date:  09/29/2020				                           *
************************************************************
*/

#include "pch.h"
#include "Card.h"
#include<string>
#include<iostream>

/* *********************************************************************
Function Name: Card
Purpose: To construct a card object
Parameters:
	face, a string passed by value that holds the face of the card to construct.
	suit, a string passed by value that holds the suit of the card to construct.
Return Value: None
Algorithm: Constructs a card object by initializing member variables.
Assistance Received: None
********************************************************************* */
Card::Card(string face, string suit) {
	this->mface = face;
	this->msuit = suit;
	this->activeMeldsUsedFor = 0;
}

/* *********************************************************************
Function Name: ~Card
Purpose: Card class destructor.
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Card::~Card() 
{

}

/* *********************************************************************
Function Name: showCard
Purpose: To print the card's value to the console
Parameters: None
Return Value: None
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
void Card::showCard()
{
	cout << this->mface << this->msuit;
}

/* *********************************************************************
Function Name: convertFaceToPoints
Purpose: To get a card's points
Parameters: None
Return Value: points, an int that holds the card's points.
Local Variables: facevalue, a string that holds the card's faceValue
Algorithm: Check card's facevalue and return the points as per the game's rule
Assistance Received: None
********************************************************************* */
int Card::convertFaceToPoints()
{
	string faceValue = this->getFace();
	int points;
	
	if(faceValue == "9")
	{
		points= 0;
	}
	else if (faceValue == "X")
	{
		points= 10;
	}
	else if (faceValue == "J")
	{
		points= 2;
	}
	else if (faceValue == "Q")
	{
		points= 3;
	}
	else if (faceValue == "K")
	{
		points= 4;
	}
	else if (faceValue == "A")
	{
		points= 11;
	}
	else
	{
		cout << "Invalid face value.";
		return 0;
	}

	return points;

}

/* *********************************************************************
Function Name: cardDescription
Purpose: To print a card's detailed description to the console
Parameters: None
Return Value: None
Local Variables: description, a string which holds the complete description and is displayed to the console
Algorithm: Append a card's detailed face name based on it's face value and repeat the same for the suit.
Assistance Received: None
********************************************************************* */
void Card::cardDescription()
{
	string description = "";
	string faceValue = this->getFace();

	if(faceValue == "9")
	{
		description.append("Nine");
	}
	else if (faceValue == "X")
	{
		description.append("Ten");
	}
	else if (faceValue == "J")
	{
		description.append("Jack");
	}
	else if (faceValue == "Q")
	{
		description.append("Queen");
	}
	else if (faceValue == "K")
	{
		description.append("King");
	}
	else if (faceValue == "A")
	{
		description.append("Ace");
	}
	else
	{
		return;
	}

	string suitValue = this->getSuit();
	if (suitValue == "H")
	{
		description.append(" of Hearts");
	}
	else if (suitValue == "C")
	{
		description.append(" of Clubs");
	}
	else if (suitValue == "S")
	{
		description.append(" of Spades");
	}
	else if (suitValue == "D")
	{
		description.append(" of Diamonds");
	}
	else
	{
		return;
	}

	cout << description;

}