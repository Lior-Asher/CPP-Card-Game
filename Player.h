#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"
#include <vector>
#include <string>

class Player {
private:
	std::string name; // player name
	int num_of_cards; // number of cards	
	std::vector<Card> m_cards; // vector of cards
	Card m_selection; // player's card selection (from their own cards)
	Card m_deckCurrent; // current card at the deck of cards

private:
	// copy player function used in operator= and copy constructor,
	// in order to avoid code duplication
	void playerCopy(const Player& other)
	{
		if (this != &other)
		{
			std::vector<Card> tmp;
			this->m_cards.swap(tmp);

			this->name = other.name;
			this->num_of_cards = other.num_of_cards;

			for (int i = 0; i < num_of_cards; i++)
			{
				m_cards.push_back(other.m_cards[i]);
			}
		}
	} 
public:
	// default constructor
	Player() {}

	Player(std::string pName, int nCards) : name(pName), num_of_cards(nCards) {}

	// copy constructor override
	Player(const Player& other)
	{
		playerCopy(other);
	}

	// assignment operator override
	Player& operator=(const Player& other)
	{
		playerCopy(other);

		return *this;
	}

	friend std::ostream& operator << (std::ostream &os, const Player& p);

	// destructor
	~Player(){}

	//public functions
	bool play(Card&);
	void setCards(const std::vector<Card>& cards);
	const std::vector<Card>& getPlayerCards();
	int getCardsCount() { return num_of_cards; }
	void setName(std::string name);
	std::string getName() { return name; }
	void setCardSelection(Card& selection) { m_selection = selection; } // so that the player will know the current card
	void setDeckCurrentCard(const Card& deckCurrent) { m_deckCurrent = deckCurrent;}
	void dropCard(int selection);

};
#endif