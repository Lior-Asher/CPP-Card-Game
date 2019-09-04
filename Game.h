#ifndef GAME_H
#define GAME_H
#include <string>
#include "Player.h"

enum playDir { clockwise, counter_clockwise }; // game direction

class Game {
private:
	//private members and functions
	std::vector<Player*> m_players; // players
	bool hasWinner;
	Card current; // card at the top of the deck
	int m_nPlayers; // number of players
	int m_nCards; // number of cards each player dealt at the beginning of the game
	int ttp; // who's turn to play
	playDir dir; // game direction

private:
	// copy constructor
	Game(const Game& other) {}
	
	// assignment constructor
	Game& operator=(const Game& other) { return *this; }

	// play the game and return the winner
	const Player& playGame(); 

	// check if the player's card selection is valid
	bool isLegitCardSelection(Player& p, int selection);

public:
	std::vector<Card> setPlayerCards(int nCards);
public:
	// default constructor
	Game() : hasWinner(false), ttp(0), dir(clockwise){}

	// destructor
	~Game()
	{		
		for (int i = 0; i < m_players.size(); i++)
		{
			delete m_players[i];
		}
	}

	//public members and functions
	void start();

	// add player
	void addPlayer(std::string pName, int nCards, std::vector<Player*>& players);
	
	// return vector containing pointers to all players
	std::vector<Player*> getAllPlayers();

	// return the card at the top of the deck of cards
	Card& getCurrent() { return current; }
};
#endif