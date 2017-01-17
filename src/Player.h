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
		int LifePoint;

		void Initialize(std::shared_ptr<Board> board, int seed);

		void Draw();

		void PlayCard(int index);

		void SetNetworkID(std::string netID);

		std::string GetNetworkID();

		shared_ptr<Board> GetBoard();

		Hand* GetHand();

		int GetHash();

		void TakeDamage(int amount);

		Player(int ID);
		~Player();

	private:
		std::string netID;
		Deck* playerDeck;
		Hand* playerHand;
		std::shared_ptr<Board> playerBoard;
	};
}

