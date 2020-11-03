/*
************************************************************
* Name:  Nitesh Parajuli                                   *
* Project:  Project 1 Pinochle C++				           *
* Class:  CMPS366 OPL				                       *
* Date:  09/29/2020				                           *
************************************************************
*/

#include"pch.h"
#include "Player.h"

/* *********************************************************************
Function Name: Player
Purpose: To construct a player object
Parameters:
Return Value: None
Algorithm: 
Assistance Received: None
********************************************************************* */

Player::Player()
{
	mPlayerRoundScore = 0;
	mPlayerTotalScore = 0;
	quitGame = false;
}

/* *********************************************************************
Function Name: printHandCards
Purpose: To display cards in hand pile to console
Parameters:
Return Value: None
Local Variables: None
Algorithm: Loop through mHandPile vector and display the card
Assistance Received: None
********************************************************************* */
void Player::printHandCards()
{
	for (int i = 0; i < mHandPile.size(); i++)
	{
		cout << mHandPile[i]->getFace() << mHandPile[i]->getSuit() << " ";
	}
	cout << endl;
}

/* *********************************************************************
Function Name: printCapturePile
Purpose: To display cards in capture pile to console
Parameters:
Return Value: None
Local Variables: None
Algorithm: Loop through mCapturePile vector and display the card
Assistance Received: None
********************************************************************* */
void Player::printCapturePile()
{
	for (int i = 0; i < mCapturePile.size(); i++)
	{
		cout << mCapturePile[i]->getFace() << mCapturePile[i]->getSuit()<<" ";
	}
	cout << endl;
}

/* *********************************************************************
Function Name: dealSingleCard
Purpose: To add new cards from the stock pile to mHandPile and mPlayablePile
Parameters:
Return Value: None
Local Variables: None
Algorithm: Push newly drawn card to hand pile and playable pile
Assistance Received: None
********************************************************************* */
void Player::dealSingleCard(Card* card)
{
	mHandPile.push_back(card);
	mPlayablePile.push_back(card);
}

/* *********************************************************************
Function Name: clearPilesandScores
Purpose: To reset all piles and scores for a new round
Parameters:
Return Value: None
Local Variables: None
Algorithm: Clear all piles and reset round score
Assistance Received: None
********************************************************************* */
void Player::clearPilesandScores()
{
	this->mHandPile.clear();
	this->meldMap.clear();
	this->mPlayablePile.clear();
	this->mCapturePile.clear();
	this->activeMelds.clear();
	this->mPlayerRoundScore = 0;
}

/* *********************************************************************
Function Name: updateMeldMap
Purpose: To add new meld card to meldMap with meldType and remove the card from hand pile
Parameters:
	1. card - pointer to card object that needs to be added to meldmap and removed from hand pile
	2. meldType - string, the name of the meld
Return Value: None
Local Variables: None
Algorithm:
	1. Add the new meld card in meldMap and link it to meldType
	2. Remove the meld card from hand pile
Assistance Received: None
********************************************************************* */
void Player::updateMeldMap(Card* card, string meldType)
{
	(this->meldMap[card]).push_back(meldType);
	this->mHandPile.erase(remove(this->mHandPile.begin(), this->mHandPile.end(), card), this->mHandPile.end());

}

/* *********************************************************************
Function Name: getActiveMeld
Purpose: To display a string containing all valid active melds to the console or to save it to file.
Parameters:
Return Value: 
	returnVal -string, a string containing all melds (comma separated) displayed as per project's requirement
Local Variables: 
	mapIndex - int, a reference integer representing the current key in the map
Algorithm:
	1. Iterate through the activeMelds map
	2. For each iteration,
		1. Display the cards linked to the meld
		2. Add '*' if the card is being used for more than one active meld
Assistance Received: None
********************************************************************* */
string Player::getActiveMeld()
{
	string returnVal = "";
	map<string, vector<vector<Card*>>>::iterator it;
	int mapIndex = 0;
	for (it= activeMelds.begin();it!=activeMelds.end();it++)
	{
		mapIndex++;
		for (int i = 0; i < it->second.size(); i++)
		{
			for (int j = 0; j < it->second[i].size(); j++)
			{
				if (it->second[i][j]->getActiveMeldNums() > 1)
				{
					returnVal += it->second[i][j]->getFace();
					returnVal += it->second[i][j]->getSuit();
					returnVal += "* ";
				}
				else
				{
					returnVal += it->second[i][j]->getFace();
					returnVal += it->second[i][j]->getSuit();
					returnVal += " ";
				}
			}
			if (mapIndex < activeMelds.size())
			{
				returnVal += ", ";
			}
			else if(i != it->second.size()-1)
			{
				returnVal += ", ";
			}
			else
			{
				continue;
			}
		}
	}
	return returnVal;
}

/* *********************************************************************
Function Name: displayPlayerStats
Purpose: To display a player's hand pile, capture pile, active melds, and scores to the console
Parameters:
Return Value:
Local Variables:
Algorithm: Use respective utility functions to display required stats to the screen
Assistance Received: None
********************************************************************* */
void Player::displayPlayerStats()
{
	cout << "\tHand: ";
	this->printHandCards();
	cout << "\tCapture Pile: ";
	this->printCapturePile();
	cout << "\tMeld: ";
	cout<<this->getActiveMeld()<<endl;
	cout << "\tRound Score: " << this->getPlayerRoundScore() << endl;
	cout << "\tTotal Score: " << this->getPlayerTotalScore() << endl << endl;
}

/* *********************************************************************
Function Name: validateMeldCards
Purpose: To check if a set of cards can yield a legit meld and award points accordingly
Parameters:
	meldCards - vector containing a set of cards supplied by the player for the meld
Return Value:
	meldPoints - int, the points rewarded for the meld
Local Variables:
	hasANewMeldCard - bool, a flag which checks if at least one new card has been used for the meld
	playerMeldMap -map, player's current meld map which stores the cards used by the player for melds so far with the meld names linked to it
	reUsedCards - bool, a flag which checks if any cards supplied has already been used for a meld with same name
	cardValues - vector, a vector containing the string representation of the cards used for the meld
	meldType - string, the meld that is generated by the supplied card
Algorithm: 
	1. For each card
		1. Loop through player's meld map and check if the card has already been used for a meld.
		2. If at least one new card is found,
			3. Get the which meld is yielded by the set of supplied cards
			4. Iterate through the player's meld map and check if any of the supplied card has already been used for the same meld name
				5. If not, assign appropriate meld points.
				6. If yes, break and assign 0 meld points.	
		3. Else, break and assign 0 meldPoints.
		4. Return meldPoints
Assistance Received: None
********************************************************************* */
int Player::validateMeldCards(vector<Card*> meldCards)
{

	if (meldCards.size() > 0)
	{
		bool hasANewMeldCard = false;
		map<Card*, vector<string>> playerMeldMap = this->getMeldMap();

		for (int k = 0; k < meldCards.size(); k++)
		{
			map<Card*, vector<string>>::iterator it;
			it = playerMeldMap.find(meldCards[k]);
			if (it == playerMeldMap.end())
			{
				hasANewMeldCard = true;
				break;
			}
		}

		int meldPoints = 0;
		bool reUsedCards = false;

		if (hasANewMeldCard)
		{
			vector<string> cardValues;
			for (int i = 0; i < meldCards.size(); i++)
			{
				cardValues.push_back(meldCards[i]->getFace() + meldCards[i]->getSuit());
			}
			char trumpSuit = trumpCard->getSuit()[0];
			string meldType = getMeldType(cardValues,trumpSuit);

			if (meldType != "None")
			{
				for (int i = 0; i < meldCards.size(); i++)
				{
					map<Card*, vector<string>>::iterator it;
					it = playerMeldMap.find(meldCards[i]);
					if (it != playerMeldMap.end())
					{
						vector<string>::iterator vecIt;
						vecIt = find((it->second).begin(), (it->second).end(), meldType);
						if (vecIt != (it->second).end())
						{
							//cout << "One of your cards has already been used for the same meld. No points earned" << endl;
							reUsedCards = true;
							meldPoints = 0;
							break;
						}
					}
				}

				if (!reUsedCards)
				{
					meldPoints = getMeldPoints(meldType);

					//cout << "A " << meldType << " meld" << endl;
					
				}
			}
			else
			{
				//cout << "No possible melds with the given cards. You didn't earn any points." << endl;
				meldPoints = 0;
			}

			return meldPoints;

		}
		else
		{
			//cout << "All cards supplied have already been used for a meld. Moving on." << endl;
			meldPoints = 0;
		}

		//this->updatePlayerScore(meldPoints);
		
	}

	return 0;

}

/* *********************************************************************
Function Name: getMeldType
Purpose: To get the meld type based on cards supplied
Parameters:
	meldCards - vector containing a set of string representations of the supplied cards
	trumpSuit - char, the trump suit 
Return Value:
	meldType - string, the name of the meld yielded
Local Variables:
	numCards - int, number of cards supplied by the user
Algorithm: 
	1. Identify the number of cards being used for the meld.
	2. Based on the number of cards, check if they can yield a meld based on game's requirement
		3. If yes, set the meld type
		4. If not, set meldType to None
	5. If not, set meldType to None
	6. Return meldType
Assistance Received: None
********************************************************************* */
string Player::getMeldType(vector<string> meldCards, char trumpSuit)
{
	int numCards = meldCards.size();
	string meldType = "";
	//char trumpSuit = trumpCard->getSuit()[0];


	if (numCards == 1)
	{
		if (meldCards[0][0] == '9' && meldCards[0][1] == trumpSuit)
		{
			meldType = "Dix";
		}
		else
		{
			//cout << "No possible melds with the given cards. You didn't earn any points." << endl;
			meldType = "None";
		}
	}
	else if (numCards == 2)
	{
		int i = 0;

		if ((meldCards[i][0] == 'J' && meldCards[i][1] == 'D') && (meldCards[i + 1][0] == 'Q' && meldCards[i + 1][1] == 'S'))
		{
			//cout << "A Pinochle meld. You've earned 40 points" << endl;
			meldType = "Pinochle";
		}
		else if ((meldCards[i][0] == 'Q' && meldCards[i][1] == 'S') && (meldCards[i + 1][0] == 'J' && meldCards[i + 1][1] == 'D'))
		{
			//cout << "A Pinochle meld. You've earned 40 points" << endl;
			meldType = "Pinochle";
		}
		else if ((meldCards[i][0] == 'K' && meldCards[i][1] == trumpSuit) && (meldCards[i + 1][0] == 'Q' && meldCards[i+1][1] == trumpSuit))
		{
			//cout << "A royal marriage. You've earned 40 points" << endl;
			meldType = "RoyalMarriage";
		}
		else if ((meldCards[i][0] == 'Q' && meldCards[i][1] == trumpSuit) && (meldCards[i + 1][0] == 'K' && meldCards[i + 1][1] == trumpSuit))
		{
			//cout << "A royal marriage. You've earned 40 points" << endl;
			meldType = "RoyalMarriage";
		}
		else if ((meldCards[i][1] == meldCards[i + 1][1]) &&
			(meldCards[i][0] == 'K' || meldCards[i][0] == 'Q') &&
			(meldCards[i + 1][0] == 'Q' || meldCards[i + 1][0] == 'K') &&
			(meldCards[i][0] != meldCards[i + 1][0]))
		{
			//cout << "A marriage. You've earned 20 points" << endl;
			meldType = "Marriage";
		}
		else
		{
			//cout << "No possible melds with the given cards. You didn't earn any points." << endl;
			meldType = "None";
		}
	}
	else if (numCards == 4)
	{
		bool isSameFace = true;
		bool isUniqueSuit = true;
		char cardFace = meldCards[0][0];

		if (cardFace == 'J' || cardFace == 'Q' || cardFace == 'K' || cardFace == 'A')
		{
			for (int i = 1; i < numCards; i++)
			{
				if (meldCards[i][0] != cardFace)
				{
					//cout << "None" << endl;
					isSameFace = false;
					meldType = "None";
					break;
				}
			}


			for (int i = 0; i < numCards - 1; i++)
			{
				for (int j = i + 1; j < numCards; j++)
				{
					if (meldCards[i][1] == meldCards[j][1])
					{
						//cout << "No possible melds with the given cards. You didn't earn any points." << endl;
						isUniqueSuit = false;
						meldType = "None";
						break;
					}
				}
			}

			if (isSameFace && isUniqueSuit)
			{
				if (cardFace == 'J')
				{
					//cout << "Four Jacks meld! You've earned 40 points." << endl;
					meldType = "FourJacks";
				}
				else if (cardFace == 'Q')
				{
					//cout << "Four Queens meld! You've earned 60 points." << endl;
					meldType = "FourQueens";
				}
				else if (cardFace == 'K')
				{
					//cout << "Four Kings meld! You've earned 80 points." << endl;
					meldType = "FourKings";
				}
				else if (cardFace == 'A')
				{
					//cout << "Four Aces meld! You've earned 100 points." << endl;
					meldType = "FourAces";
				}
				else
				{
					//cout << "No possible melds with the given cards. You didn't earn any points." << endl;
					meldType = "None";

				}
			}

		}
		else
		{
			//cout << "No possible melds with the given cards. You didn't earn any points." << endl;
			meldType = "None";
		}
	}

	else if (numCards == 5)
	{
		bool isAllTrumpSuit = true;
		bool isAllLegitFlushCards = true;

		for (int i = 0; i < numCards; i++)
		{
			if (meldCards[i][1] != trumpSuit)
			{
				//cout << "No possible melds with the given cards. You didn't earn any points." << endl;
				isAllTrumpSuit = false;
				meldType = "None";
				break;
			}

		}


		for (int i = 0; i < numCards - 1; i++)
		{
			for (int j = i + 1; j < numCards; j++)
			{
				if ((meldCards[i][0] == meldCards[j][0]) || meldCards[i][0] == '9' || meldCards[j][0] == '9')
				{
					//cout << "No possible melds with the given cards. You didn't earn any points." << endl;
					isAllLegitFlushCards = false;
					meldType = "None";
					break;
				}
			}
		}

		if (isAllTrumpSuit && isAllLegitFlushCards)
		{
			//cout << "A flush meld! You've earned 100 points" << endl;
			meldType = "Flush";
		}
	}
	else
	{
		//cout << "No possible melds with the given cards. You didn't earn any points." << endl;
		meldType = "None";
	}



	return meldType;
}

/* *********************************************************************
Function Name: getMeldPoints
Purpose: To get the points for a meld
Parameters:
	meldCards - string, name of the meld
Return Value: meld points
Local Variables:
Algorithm: Return the points of a meld as per game's requirement
Assistance Received: None
********************************************************************* */
int Player::getMeldPoints(string meldType)
{
	if (meldType == "Dix")
	{
		return 10;
	}
	else if (meldType == "Marriage")
	{
		return 20;
	}
	else if (meldType == "Pinochle")
	{
		return 40;
	}
	else if (meldType == "RoyalMarriage")
	{
		return 40;
	}
	else if (meldType == "FourJacks")
	{
		return 40;
	}
	else if (meldType == "FourQueens")
	{
		return 60;
	}
	else if (meldType == "FourKings")
	{
		return 80;
	}
	else if (meldType == "FourAces")
	{
		return 100;
	}
	else if (meldType == "Flush")
	{
		return 150;
	}
	else
	{
		return 0;
	}

	return 0;
}

/* *********************************************************************
Function Name: totalPossibleMelds
Purpose: To get all possible melds from a set of cards
Parameters:
	cards - vector, a list of pointers to cards 
Return Value: 
	possibleMelds - map, a map with meld type as key, and a list of list of cards used for that meld type
Local Variables:
	returnPoints - int, the meld points returned for a set of cards
	referencedCard - vector, a utility vector to keep track of the referenced card
Algorithm: Return the points of a meld as per game's requirement
Assistance Received: None
********************************************************************* */
map<string, vector<vector<Card*>>> Player::totalPossibleMelds(vector<Card*> cards)
{
	int returnPoints=0;
	vector<bool> referencedCard;
	vector < vector<Card*>> combos;

	for (int i = 0; i < cards.size(); i++)
	{
		referencedCard.push_back(false);
	}

	for (int i = 1; i <= 5; i++) 
	{
		if (i != 3)
		{
			generateAllCardsCombo(combos, cards, i, 0, 0, referencedCard);
		}
	}

	map<string, vector<vector<Card*>>> possibleMelds;
	for (int j = 0; j < combos.size(); j++)
	{
		vector<string> cardValues;
		for (int i = 0; i < combos[j].size(); i++)
		{
			cardValues.push_back(combos[j][i]->getFace() + combos[j][i]->getSuit());
		}
		int meldPoint = validateMeldCards(combos[j]);

		if (meldPoint > 0)
		{
			char trumpSuit = trumpCard->getSuit()[0];
			string meldType = getMeldType(cardValues, trumpSuit);
			possibleMelds[meldType].push_back(combos[j]);
			//returnPoints += meldPoint;
		}

	}

	//system("pause");

	return possibleMelds;
}

/* *********************************************************************
Function Name: generateAllCardsCombo
Purpose: To genearate a list of all possible combination of certain number of cards
Parameters:
	combos - vector, vector storing all generated combinations
	cards - vector, pile of cards being used for the generating the combinations
	requiredLength - int, number of cards in the desired combination
	startIndex -int, the card with reference to which the combination is being generated
	currLength -int, the number of cards in the current combinaion
	referencedCard - vector, - a utility vector to keep track of which card has been referenced for the combination
Return Value: None
Local Variables:
	temp - vector, a vector storing the combinations which needs to be pushed to the combos
Algorithm: 
	1. check if current length is the desired length, if yes check which card has been referenced and push them in temp vector, and return.
	2. if current length exceeds desired length, return.
	3. if starting index is the last index in the pile, return.
	4. recursively call the function with a next index and for next length
	5. change the referencedCard value to indicate that the card is not longer the referenced card
	6. recursively call the function by for next index 
Assistance Received: None
********************************************************************* */
void Player::generateAllCardsCombo(vector<vector<Card*>>&combos, vector<Card*> cards, int requiredLength, int startIndex, int currLength, vector<bool> referencedCard)
{
	if (currLength > requiredLength)
	{
		return;
	}
	else if (currLength == requiredLength) 
	{
		vector<Card*> temp;
		for (int i = 0; i < cards.size(); i++) 
		{
			if (referencedCard[i] == true)
			{
				temp.push_back(cards[i]);
			}
		}

		combos.push_back(temp);
		return;
	}

	if (startIndex == cards.size())
	{
		return;
	}

	referencedCard[startIndex] = true;
	generateAllCardsCombo(combos, cards, requiredLength, startIndex + 1, currLength + 1, referencedCard);

	referencedCard[startIndex] = false;
	generateAllCardsCombo(combos, cards, requiredLength,startIndex + 1, currLength, referencedCard);

}

/* *********************************************************************
Function Name: bestChaseMove
Purpose: To get the a map storing indexes of the best card for a chase move as its index, and the expensiveness of the card as its value
Parameters:
	turninfo - an object of TurnInfo class which includes information about this turn
Return Value:
	winningMap - map, a map containing all winning indexes of playable pile as index and their calculated points as value
Local Variables:
	leadCard - a pointer to a card which stores lead card value
Algorithm: 
	1. Loop through the playable pile. For each card, check if it can win the lead card.
		2. If yes, 
			3. check if it's a trump card, 
				4. If yes, award card point value + 100, and store the card's index and points in the map
				5. If no, award card point value only, and store the card's index and points in the map
		6. If no,
			7. continue running the loop
	8. Return the w 
Assistance Received: None
********************************************************************* */
map<int, int> Player::bestChaseMove(TurnInfo* turnInfo)
{
	int mostInexpensiveIndex = 0;
	Card* leadCard = turnInfo->getLeadCard();
	map<int, int> winningMap;

	for (int i = 0; i < mPlayablePile.size(); i++)
	{
		if (mPlayablePile[i]->getSuit() == leadCard->getSuit() && leadCard->getSuit() == trumpCard->getSuit())
		{
			if (mPlayablePile[i]->convertFaceToPoints() > leadCard->convertFaceToPoints())
			{
				winningMap[i] = 100 + mPlayablePile[i]->convertFaceToPoints();
			}
		}
		else if (mPlayablePile[i]->getSuit() == leadCard->getSuit())
		{
			if (mPlayablePile[i]->convertFaceToPoints() > leadCard->convertFaceToPoints())
			{
				winningMap[i] = mPlayablePile[i]->convertFaceToPoints();
			}
		}
		else if (mPlayablePile[i]->getSuit() == trumpCard->getSuit())
		{
			winningMap[i] = 100 + mPlayablePile[i]->convertFaceToPoints();
		}
		else
		{
			continue;
		}
	}

	return winningMap;

}

/* *********************************************************************
Function Name: bestLeadMove
Purpose: To get the index of the best possible playable card after meld consideration
Parameters:
	turninfo - an object of TurnInfo class which includes information about this turn
Return Value: 
	bestPlayableCard - int, the index of the best playable card
Local Variables:
	maximumMeldPoints - int, the maximum possible meldpoints that could be saved when a card is played
	winningMap - map, a map containing all card indexes of playable pile as its index, and the meld points that will be left if that card is played
	checkCard - pointer to a card which is undergoing the checking process
	tempCheckVec - vector, a list of all remaining cards left in the pile after a card is played
	possibleMelds - map,  a map storing all possible valid melds and the cards used for that meld from tempCheckVec
	totalMeldPoints - int , sotres the meldPoints that could be generated from each meldtype of possibleMelds
Algorithm:
	1. Loop thorugh the pile to find the playability of each card, for each card,
		2. Create a temp vetor storing the remaining cards and find the meldpoints that the temp vector can yield
		3. compare the meldpoints with the maximum meld points so far and update if the current meldPoint is the maximum so far
		4. store the card and the meldpoints that could be generated if the card is played in winning map
	5. Loop through the winning map,
		6. For each iteration see if the linked points is maximum generated meldPoints for a card in the pile
		7. If yes, compare its expensiveness with the previous cards in the map and track the strongest playable card among such cards
		8. If not, do nothing.
	9. Return the strongest playable card
Assistance Received: None
********************************************************************* */
int Player::bestLeadMove(TurnInfo* turnInfo)
{
	int bestPlayableCard = 0;
	int maximumMeldPoints = 0;
	map<int, int> winningMap;


	for (int i = 0; i < mPlayablePile.size(); i++)
	{

		Card* checkCard = mPlayablePile[i];
		vector<Card*> tempCheckVec;

		for (int j = 0; j < mPlayablePile.size(); j++)
		{
			if (mPlayablePile[j] != checkCard)
			{
				tempCheckVec.push_back(mPlayablePile[j]);
			}

		}

		map<string, vector<vector<Card*>>> possibleMelds = totalPossibleMelds(tempCheckVec);
		int totalMeldPoints = 0;

		for (auto& i : possibleMelds)
		{
			string meldType = i.first;
			totalMeldPoints += i.second.size() * getMeldPoints(meldType);
		}

		if (maximumMeldPoints < totalMeldPoints)
		{
			maximumMeldPoints = totalMeldPoints;
		}
		winningMap[i] = totalMeldPoints;
	}

	bool checkBegin = false;
	for (auto& t : winningMap)
	{
		if (t.second == maximumMeldPoints)
		{
			if (checkBegin)
			{
				int prevPoint = mPlayablePile[bestPlayableCard]->convertFaceToPoints();
				if (mPlayablePile[bestPlayableCard]->getSuit() == trumpCard->getSuit())
				{
					prevPoint = 100 + prevPoint;
				}

				int thisPoint = mPlayablePile[t.first]->convertFaceToPoints();
				if (mPlayablePile[t.first]->getSuit() == trumpCard->getSuit())
				{
					thisPoint = 100 + thisPoint;
				}


				if (thisPoint > prevPoint)
				{
					bestPlayableCard = t.first;
				}
			}
			else
			{
				bestPlayableCard = t.first;
				checkBegin = true;
			}

		}
	}

	return bestPlayableCard;

}

/* *********************************************************************
Function Name: removePlayedCard
Purpose: To remove the played card from all piles that needs to get rid of it
Parameters:
	playedCard - a pointer to the played card
Return Value: None
Local Variables:
	found -bool, a flag indicating if the card is found in the active meld map
	removeVec - vector, a list of used in the meld which also includes the played card
Algorithm:
	1. Remove the card from playable pile if it exists
	2. Remove the card from hand pile if it exists
	3. Remove the card from meld pile if it exists
	4. Iterate through the active meld map, and for each meldType present in the meld map, see if the played card has been used for that meld type
		5. If yes, get the set of cards and remove played card from it and decrement activeMeldsUsedFor value. 
			6. Check if other cards in that set have been used for other melds, 
				7. If yes do not move them to hand pile but decrement its activeMeldsUsedFor value
				8. If not, move them to the handpile and decrement its activeMeldsUsedFor value
			9. Remove the set of cards from the active meld
		10. If not, continue the checking process for other meldtype.
	11. Remove the cards from meld map if it exists as we longer need to track its meld history.
Assistance Received: None
********************************************************************* */
void Player::removePlayedCard(Card* playedCard)
{
	this->mPlayablePile.erase(remove(this->mPlayablePile.begin(), this->mPlayablePile.end(), playedCard), this->mPlayablePile.end());
	this->mHandPile.erase(remove(this->mHandPile.begin(), this->mHandPile.end(), playedCard), this->mHandPile.end());
	this->mMeldPile.erase(remove(this->mMeldPile.begin(), this->mMeldPile.end(), playedCard), this->mMeldPile.end());
	map<string, vector<vector<Card*>>>::iterator it;

	for (it=activeMelds.begin();it!=activeMelds.end();)
	{
		bool found = false;
		for (int count1 = 0; count1 < it->second.size(); count1++)
		{
			for (int count2 = 0; count2 < it->second[count1].size(); count2++)
			{
				if (it->second[count1][count2] == playedCard)
				{
					found = true;
					playedCard->setActiveMeldNums(-1);
					break;
				}
			}
			if (found == true)
			{
				vector<Card*> removeVec = it->second[count1];
				removeVec.erase(remove(removeVec.begin(), removeVec.end(), playedCard), removeVec.end());
				for (int i = 0; i < removeVec.size(); i++)
				{
					if (removeVec[i]->getActiveMeldNums() == 1)
					{
						mHandPile.push_back(removeVec[i]);
						this->mMeldPile.erase(remove(this->mMeldPile.begin(), this->mMeldPile.end(), removeVec[i]), this->mMeldPile.end());
					}

					removeVec[i]->setActiveMeldNums(-1);

				}
				it->second.erase(it->second.begin() + count1);

				
			}
		}

		if (it->second.empty() == true)
		{
			it = activeMelds.erase(it);
		}

		else
		{
			it++;
		}

		


	}


	map<Card*, vector<string>>::iterator it1;
	it1 = this->meldMap.find(playedCard);
	if (it1 != this->meldMap.end())
	{
		this->meldMap.erase(it1);

	}
}

/* *********************************************************************
Function Name: savePlayersStats
Purpose: To save the current stats of the player to a save file
Parameters:
	saveFile - object of the ofstream class used to write to a file
Return Value: None
Local Variables:
Algorithm:
	Get all the stats that need to be saved, using accessor and utility functions and write them in a file in required format.
Assistance Received: None
********************************************************************* */
void Player::savePlayersStats(ofstream &saveFile)
{

	saveFile << "\tScore: " << this->getPlayerTotalScore() << " / " << this->getPlayerRoundScore() << "\n";
	saveFile << "\tHand: ";

	for (int i = 0; i < this->getHandPile().size(); i++)
	{
		saveFile << (this->getHandPile()[i])->getFace() << (this->getHandPile()[i]->getSuit()) << " ";
	}
	saveFile << "\n";
	saveFile << "\tCapture Pile: ";

	for (int i = 0; i < this->getCapturePile().size(); i++)
	{
		saveFile << (this->getCapturePile()[i])->getFace() << (this->getCapturePile()[i]->getSuit()) << " ";
	}
	saveFile << "\n";

	saveFile << "\tMelds: " << this->getActiveMeld() << "\n\n";
}

/* *********************************************************************
Function Name: loadScores
Purpose: To load player's round score and total score from a saved file
Parameters:
	score -string, the string which indicates player's scores in the saved file
Return Value: None
Local Variables:
	scores - vector, a vector which sotres total score and round score of the player
	ss - object of stringstream class used to read the score string in saved file
Algorithm:
	Parse the string and get round score and total score and store them in the scores vector
	Update the player's member variables holding the round scores and total scores by accessing scores from the vector
Assistance Received: None
********************************************************************* */
void Player::loadScores(string score)
{
	vector<int> scores;
	stringstream ss(score);

	for (int i; ss >> i;)
	{
		scores.push_back(i);
		while (ss.peek() == '/' || ss.peek() == ' ')
			ss.ignore();
	}

	this->mPlayerTotalScore = scores[0];
	this->mPlayerRoundScore = scores[1];

}

/* *********************************************************************
Function Name: loadHandPile
Purpose: To load player's hand pile
Parameters:
	pile -string, the string which indicates player's hand pile in the saved file
Return Value: None
Local Variables:
	ss - object of stringstream class used to read the pile string in saved file
Algorithm:
	Parse the pile string and get each card from it. For each Create a new card object for it and store its face and suit value, and push it to player's handPile and playablePile
Assistance Received: None
********************************************************************* */
void Player::loadHandPile(string pile)
{
	istringstream ss(pile);
	if (!pile.empty())
	{
		string card;
		while(ss>>card)
		{
			if (!card.empty())
			{
				string face(1, card[0]);
				string suit(1, card[1]);

				Card* newCard = new Card(face, suit);
				mHandPile.push_back(newCard);
				mPlayablePile.push_back(newCard);
			}

			

			
		} 
	}
}

/* *********************************************************************
Function Name: loadCapturePile
Purpose: To load player's capture pile
Parameters:
	pile -string, the string which indicates player's capture pile in the saved file
Return Value: None
Local Variables:
	ss - object of stringstream class used to read the pile string in saved file
Algorithm:
	Parse the pile string and get each card from it. For each create a new card object for it and store its face and suit value, and push it to player's capture pile.
Assistance Received: None
********************************************************************* */
void Player::loadCapturePile(string pile)
{
	istringstream ss(pile);
	if (!pile.empty())
	{
		string card;
		
			while (ss >> card)
			{
				if (!card.empty())
				{
				string face(1, card[0]);
				string suit(1, card[1]);

				mCapturePile.push_back(new Card(face, suit));
				}
			}
	}
}

/* *********************************************************************
Function Name: loadCapturePile
Purpose: To load player's meld pile, meld map, and activeMelds
Parameters:
	pile -string, the string which indicates player's melds in the saved file
	trumpSuit - char, the trump suit of the round
Return Value: None
Local Variables:
	repeatedCards - vector, a vector storing the cards with '*' value
	ss - object of stringstream class used to read the melds string in saved file
	tempMeldMap - map, a temp meld map which regularly updates itself and represents the player's meld map after final verification
	meldTrack - map, a map which holds the nth meld in the melds string in the saved file and links to it's meld type
	meldNum - int, the position of a meld in the melds string
Algorithm:
	1. Retrive each meld from melds by using the ',' delimitter, identify its meld Type based on the cards used in the meld, and store it's position within the melds string with its meldType in the meldTrack map
	2. Iterate through the melds string, for each meld in the melds string
		3. Split the meld string into its card values
		4. See if the card has an '*' linked to it.
			5. If not, create a new card object for it and push it to meld pile, tempMeldMap with its meld type.
			6. If yes, check the tempMeldMap to see if the card has already been used for a same meld name
				7. If yes, create a new card object for it and push it to meld pile, tempMeldMap with its meld type.
				8. If not, check if it has been used for any other meld names so far by referencing the repeatedMelds vector.
					9. If yes, do not create a new card for it as it might be the same card object. But update its tempMeldMap value to indicate its usage for a second meld.
					10. If not, create a new card object for it as it's the card's first appearance and push it to meld pile, tempMeldMap with its meld type, and repeatedCards vector.
		5. Update the player's active melds to store the meld type and the cards used in that meld type.
	6. Iterate through each card in the repeated card vector to check for correct meld assignments. For each card
		7. Reference the temp meld map and find the number of melds it has been used for.
		8. If the number is less than 2, get the card's face value. Reference the tempMeldMap and find the other card with the same face value.
		9. Find number of melds the the other card has been used for, if that's greater than 2, find the melds that card is linked to. 
		10 . Find a meld type that the current card in repeated card hasn't been used for. And link the current card to that meld. Update this information in tempMeldMap, and active melds.
	11. Copy the content of tempMeldMap to player's meldmap.
	12. Store the index values of tempMeldMap in meld pile, and playable pile.
	13. Update the activeMeldsUsed for value for each card using tempMeldMap.
		 
Assistance Received: None
********************************************************************* */
void Player::loadMeldPile(string pile, char trumpSuit)
{
	vector<Card*> repeatedCards;
	stringstream ss(pile);
	map<Card*, vector<string>> tempMeldMap;
	map<int, string> meldTrack;
	int meldNum = 0;

	while (ss.good())
	{
		string eachMeld;
		getline(ss, eachMeld, ',');
		while (!eachMeld.empty() && eachMeld[eachMeld.size() - 1] == ' ')
		{
			eachMeld.pop_back();
		}
		istringstream ss(eachMeld);
		if (!pile.empty())
		{
			vector<string> cards;
			string card;
			
			while (ss >> card)
			{
				if (card[card.size() - 1] == '*')
				{
					card.pop_back();
				}
				cards.push_back(card);
			}

			string meldType = getMeldType(cards,trumpSuit);
				
			meldTrack[meldNum] = meldType;
			meldNum++;
		
		}
	}

	meldNum = 0;
	stringstream ss2(pile);
	while (ss2.good())
	{
		string eachMeld;
		getline(ss2, eachMeld, ',');
		while (!eachMeld.empty() && eachMeld[eachMeld.size() - 1] == ' ')
		{
			eachMeld.pop_back();
		}
		istringstream ss(eachMeld);
		if (!pile.empty())
		{

			vector<string> cards;
			vector<Card*> thisMeldCards;
			string card;
			string thisMeld = meldTrack[meldNum];

			while (ss >> card)
			{
		
				if (card[card.size() - 1] == '*')
				{
					map<Card*, vector<string>>::iterator it;
					bool firstInstance = true;
					for (it = tempMeldMap.begin(); it != tempMeldMap.end(); it++)
					{
						char thisFace = it->first->getFace()[0];
						char thisSuit = it->first->getSuit()[0];

						if (thisFace == card[0] && thisSuit == card[1])
						{
							firstInstance = false;
							auto vecIt = find(it->second.begin(), it->second.end(), thisMeld);
							if (vecIt != it->second.end())
							{
								string face(1, card[0]);
								string suit(1, card[1]);
								Card* newCard = new Card(face, suit);
								tempMeldMap[newCard].push_back(thisMeld);
								thisMeldCards.push_back(newCard);
								repeatedCards.push_back(newCard);
								

							}
							else
							{
								tempMeldMap[it->first].push_back(thisMeld);
								thisMeldCards.push_back(it->first);
								auto repVecIt = find(repeatedCards.begin(), repeatedCards.end(), it->first);
								if (repVecIt == repeatedCards.end())
								{
									repeatedCards.push_back(it->first);
								}
							}

							break;
							
						}
						else
						{
							continue;
						}
						
					}
					if (firstInstance)
					{
						string face(1, card[0]);
						string suit(1, card[1]);
						Card* newCard = new Card(face, suit);
						tempMeldMap[newCard].push_back(thisMeld);
						thisMeldCards.push_back(newCard);
					}

				}
				else
				{
					string face(1, card[0]);
					string suit(1, card[1]);

					Card* newCard = new Card(face, suit);
					tempMeldMap[newCard].push_back(thisMeld);
					thisMeldCards.push_back(newCard);
				}

			}

			activeMelds[thisMeld].push_back(thisMeldCards);
			meldNum++;

		}

	}

	
	for (int i = 0; i < repeatedCards.size(); i++)
	{
		int numCards = tempMeldMap[repeatedCards[i]].size();

		if (numCards < 2)
		{
			string meldOne = tempMeldMap[repeatedCards[i]][0];
			string face = repeatedCards[i]->getFace();
			string suit = repeatedCards[i]->getSuit();

			for (auto it = tempMeldMap.begin(); it != tempMeldMap.end(); it++)
			{
				if (it->first != repeatedCards[i])
				{
					string mapCardFace = it->first->getFace();
					string mapCardSuit = it->first->getSuit();

					if (mapCardFace == face && mapCardSuit == suit)
					{
						if (it->second.size() > 2)
						{
							string meldTransfer;
							int j = 0;
							while (true)
							{
								if (it->second[j] != meldOne)
								{
									meldTransfer = it->second[j];
									break;
								}
								j++;
							}

							it->second.erase(remove(it->second.begin(), it->second.end(), meldTransfer), it->second.end());
							tempMeldMap[repeatedCards[i]].push_back(meldTransfer);

							for (int j = 0; j < activeMelds[meldTransfer].size(); j++)
							{
								auto vecIt = find(activeMelds[meldTransfer][j].begin(), activeMelds[meldTransfer][j].end(), it->first);
								if (vecIt != activeMelds[meldTransfer][j].end())
								{
									*vecIt = repeatedCards[i];
								}
							}

							break;
							
						}
					}

				}
			}
		}
	}



	meldMap.insert(tempMeldMap.begin(), tempMeldMap.end());
	for (auto it = tempMeldMap.begin(); it != tempMeldMap.end(); it++)
	{
		mMeldPile.push_back(it->first);
		mPlayablePile.push_back(it->first);
		it->first->setActiveMeldNums(it->second.size());
	}
	

}
