#pragma once
#include "Card.h"
#include <vector>

namespace JojoBen {
	class Deck
	{
	public:
		Card* Draw();
		bool isEmpty();
		Deck();
		Deck(int size);
		~Deck();
	private:
		int deckSize = 20;
		std::vector<Card*> cards;
	};
}

