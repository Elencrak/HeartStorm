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

		void Initialize(std::shared_ptr<Board> board);

		void Draw();

		void PlayCard(Card* card);

		Player();
		~Player();

	private:
		Deck* playerDeck;
		Hand* playerHand;
		std::shared_ptr<Board> playerBoard;
	};
}

