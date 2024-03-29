#include "Player.h"

// true if the player played a card, otherwise - false
bool Player::play(Card& current)
{
	if (current.is_legal(m_selection))
	{
		this->num_of_cards--;
		return true;
	}

	return false;
}

/*
*	Set player name.
*	Params:
*		name - player name
*/
void Player::setName(std::string name)
{
	this->name = name;
}

/*
*	Set all player's cards.
*	Params:
*		&cards - vector of cards that were generated by Game class, assigned to the player.
*/
void Player::setCards(const std::vector<Card>& cards)
{
	// clear old cards.
	// needed when the player drop or takes card
	std::vector<Card>().swap(m_cards);

	// refill player's cards list
	for (int i = 0; i < cards.size(); i++)
	{
		m_cards.push_back(cards[i]);
	}

	num_of_cards = m_cards.size(); // set new number of cards the player holds
}

/*
*	Return player's cards.
*	Return:
*		vector of player's cards
*/
const std::vector<Card>& Player::getPlayerCards()
{
	if(m_cards.size() > 0)
		return m_cards;
}

// Operator<< overload, for easy player display
std::ostream& operator << (std::ostream &os, const Player& p)
{
	os << p.name << ", your turn - \n"  << "Your cards: ";
	std::vector<Card> cards = p.m_cards;
	for (int i = 0; i < cards.size(); i++)
	{
		os << "(" << (i + 1) << ")" << cards[i] << " ";
	}
	os << "";

	return os;
}

// Remove the played card from player's cards
void Player::dropCard(int selection)
{
	m_cards.erase(m_cards.begin() + (selection - 1));
}