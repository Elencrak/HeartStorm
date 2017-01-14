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

		shared_ptr<Board> GetBoard();

		int GetHash();

		Player(int ID);
		~Player();

	private:
		Deck* playerDeck;
		Hand* playerHand;
		std::shared_ptr<Board> playerBoard;
	};
}

