/*
************************************************************
* Name:  Nitesh Parajuli                                   *
* Project:  Project 1 Pinochle C++				           *
* Class:  CMPS366 OPL				                       *
* Date:  09/29/2020				                           *
************************************************************
*/

#include"pch.h"
#include"Deck.h"
#include"Card.h"

/* *********************************************************************
Function Name: Deck
Purpose: To construct a deck object
Parameters: None
Return Value: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Deck::Deck()
{
	
}

/* *********************************************************************
Function Name: ~Deck
Purpose: To delete all card objects inside the deck object
Parameters: None
Return Value: None
Algorithm: Delete all card objects stored in the deck
Assistance Received: None
********************************************************************* */
Deck::~Deck()
{
	for (int i = 0; i < mdeck.size(); i++)
	{
		delete mdeck[i];
	}
}

/* *********************************************************************
Function Name: createNewDeck
Purpose: To create a fresh new deck and shuffle it
Parameters: None
Return Value: None
Local Variables: 
		faces [], a string array containg all possible faces
		suits [], a string array containg all possible suits
Algorithm:	
		1. Iterate twice and on each iteration, for each face and suite value, create a new card and push it to the mDeck.
		2. Shuffle the deck
Assistance Received: None
********************************************************************* */
void Deck::createNewDeck()
{
	string faces[] = { "9","X","J","Q","K","A" };
	string suits[] = { "S","H","D","C" };

	mTopCardPos = 0;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < (sizeof(suits) / sizeof(suits[0])); j++) {

			for (int k = 0; k < (sizeof(faces) / sizeof(faces[0])); k++)
			{
				mdeck.push_back(new Card(faces[k], suits[j]));
			}
		}
	}

	shuffleDeck();
}

/* *********************************************************************
Function Name: shuffleDeck
Purpose: To shuffle a deck of cards
Parameters: None
Return Value: None
Local Variables:
		seed, an unsigned holding current time
Algorithm:
		1.Shuffle the vector of cards - mDeck
Assistance Received: None
********************************************************************* */
void Deck::shuffleDeck()
{
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(mdeck.begin(), mdeck.end(), default_random_engine(seed));
}

/* *********************************************************************
Function Name: drawCard
Purpose: To get the next card from the deck
Parameters: None
Return Value: drawnCard, a pointer to the card drawn from the deck 
Local Variables: None
Algorithm:
		1. Access the next card in the deck.
		2. Increment the index of the next card in the deck.
		3. Return the accessed value from Step 1.
Assistance Received: None
********************************************************************* */
Card* Deck::drawCard()
{
	
	Card* drawnCard = mdeck[mTopCardPos];
	mTopCardPos++;
	return drawnCard;
}


/* *********************************************************************
Function Name: loadDeck
Purpose: To load a deck from a string retrieved from a config file
Parameters: pile, a string containing cards in the deck
Return Value: None
Local Variables: ss, an istringstream object with a copy of pile as content
				 card, string which holds each individual string(card value) from pile
Algorithm:
		1. Read each value from the string until there are no more
		2. For each value, retrieve the face and suit and create a new Card.
		3. Push the card to the mDeck vector
Assistance Received: None
********************************************************************* */
void Deck::loadDeck(string pile)
{
	istringstream ss(pile);
	if (!pile.empty())
	{
		string card;
		while (ss >> card)
		{
			string face(1, card[0]);
			string suit(1, card[1]);

			mdeck.push_back(new Card(face, suit));
		}
	}

}

/* *********************************************************************
Function Name: displayStockPile
Purpose: To display stock pile to the console
Parameters: None
Return Value: None
Local Variables: None
Algorithm:
		1. For each card in mdeck, print its face and suit
Assistance Received: None
********************************************************************* */
void Deck::displayStockPile()
{
	for (int i = mTopCardPos; i < mdeck.size(); i++)
	{
		cout << mdeck[i]->getFace() << mdeck[i]->getSuit() << " ";
	}
	cout << endl;
}