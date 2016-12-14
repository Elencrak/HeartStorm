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
		~Deck();
	private:
		std::vector<Card*> cards;
	};
}

