#pragma once
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Board.h"
#include <memory>

namespace JojoBen
{

	class Player
	{
	public:

		int ID;

		void Initialize(std::shared_ptr<Board> board, int seed);

		void Draw();

		void PlayCard(int index);

		void SetNetworkID(std::string netID);

		std::string GetNetworkID();

		shared_ptr<Board> GetBoard();

		int GetHash();

		Player(int ID);
		~Player();

	private:
		std::string netID;
		Deck* playerDeck;
		Hand* playerHand;
		std::shared_ptr<Board> playerBoard;
	};
}

