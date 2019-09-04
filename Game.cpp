#include "Game.h"

// game start function
void Game::start()
{
	std::string playerName = "";

	do
	{
		std::cout << "How many players?" << std::endl;
		std::cin >> m_nPlayers;

		std::cout << "How many cards?" << std::endl;
		std::cin >> m_nCards;

	} while (m_nPlayers < 1 || m_nCards < 1); // check positive number of players and cards

	for (int i = 0; i < m_nPlayers; i++)
	{

		int pIndex = (i + 1);
		std::cout << "player number " << pIndex << " name?" << std::endl;
		std::cin >> playerName;

		addPlayer(playerName, m_nCards, m_players);
	}

	playGame();
}

// function that manages the game
const Player& Game::playGame()
{
	// deal cards for the players
	for (int i = 0; i < m_players.size(); i++)
	{
		std::vector<Card> pCards = setPlayerCards(m_nCards);
		m_players[i]->setCards(pCards);
	}

	current = Card::generate_card(); // top of the deck of cards

	int cardSelectionIndex; // player selects an index of his cards array
	Player* p;
	int steps = 0; // number of steps to next player (STOP: +2, +: +0, etc.)
	bool playAgain = false; // play another turn, in case of '+'

	// main game loop, runs as long there is no winner.
	while (!hasWinner)
	{
		p = m_players[ttp]; // player at "Turn To Play" index

		std::cout << "current: " << current << std::endl; // display the current card at the top of the deck
		std::cout << *p << std::endl; // display player name and cards
		
		do
		{
			// convert card index selection into an actual card
			std::vector<Card> cards = p->getPlayerCards();
			std::cin >> cardSelectionIndex;

			// Check selection if is in range of player's cards.
			// If the selection is out of bounds of the cards the player has,
			// the player takes a card and turn is passed to the next player.
			if (!isLegitCardSelection(*p, cardSelectionIndex))
			{
				// player has no card to play, takes card
				std::vector<Card> cards = p->getPlayerCards();
				cards.push_back(Card::generate_card());
				p->setCards(cards);

				// check game direction and advance to next player accordingly
				if (dir == clockwise)
				{
					ttp = (ttp + 1) % m_nPlayers;
				}
				else // dir == counter_clockwise
				{
					ttp = (ttp - 1) % m_nPlayers;
				}

				steps = -1; // pass the turn
			}
			else
			{
				Card c = cards[cardSelectionIndex - 1]; // card at the selected index

				p->setCardSelection(c); // update the card the player selected

				// check if the card selected by the player can be placed over the current card
				if (p->play(current))
				{
					current = c; // put player's card at the top of the deck of cards
					p->setDeckCurrentCard(current); // update the player which card is the current top card
					p->dropCard(cardSelectionIndex); // remove the card from the player's cards

					// check if the player still has cards to play
					if (p->getCardsCount() > 0)
					{
						switch (current.get_sign())
						{
						case sign::PLUS: // player plays another turn
							steps = 0;
							playAgain = true;
							break;
						case sign::CD: // change game direction and advance to next player
							if (dir == clockwise)
								dir = counter_clockwise;
							else
								dir = clockwise;
							steps = 1;
							break;
						case sign::STOP: // jump over the next player
							steps = 2;
							break;
						default: // numbers only, advance to next player
							steps = 1;
							break;
						}

						// check game direction to determine which is player plays next,
						// in a circular manner
						if (dir == clockwise)
						{
							ttp = (ttp + steps) % m_nPlayers;
						}
						else // dir == counter_clockwise
						{
							ttp = (ttp - steps) % m_nPlayers;

							// (ttp - steps) % m_nPlayers did not work like (ttp + steps) % m_nPlayers as expected.
							// make sure we don't over flow
							if (ttp == (-1))
							{
								ttp = m_nPlayers - 1;
							}

							if (ttp == (-2))
							{
								ttp = m_nPlayers - 2;
							}
						}
					}
					else // player has no more cards, wins the game
					{
						hasWinner = true;
						std::cout << p->getName() << " wins!" << std::endl;
						return *p;
					}
				}
				else // player card selecion is not legal, takes another card and turn moves to next player.
				{
					std::cout << "You can't put " << c << " on " << current << std::endl;
					steps = 0; // play another turn
				}
			}
		} while (steps == 0 && playAgain == false);
	}
}

/*
*	Check if player's card selection is in range of their cards
*	Params: 
*		&p - the player that plays
*		selection - index of the card the player selected.
*	Returns: 
*		True if selection is legal, else false
*/
bool Game::isLegitCardSelection(Player& p, int selection)
{
	// check index of card selection is in range
	if (selection > 0 && selection <= p.getCardsCount())
	{
		return true;
	}

	return false;
}

// return all players
std::vector<Player*> Game::getAllPlayers()
{
	return m_players;
}

/*
*	Add player to the list.
*	Params:
*		pName - player's name
*		m_nCards - number of cards
*		players - players list referencs
*/
void Game::addPlayer(std::string pName, int m_nCards, std::vector<Player*>& players)
{
	Player* p = new Player(pName, m_nCards);
	players.push_back(p);
}

/*
*	Set player's cards
*	Params:
*		nCards - number of cards
*/
std::vector<Card> Game::setPlayerCards(int nCards)
{
	std::vector<Card> cards;
	for (int i = 0; i < nCards; i++)
	{
		cards.push_back(Card::generate_card());
	}

	return cards;
}
