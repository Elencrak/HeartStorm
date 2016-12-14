#pragma once
#include "Card.h"
#include <Vector>

namespace JojoBen
{

	class Hand
	{
	public:
		void AddCard(Card* card);
		Hand();
		~Hand();
	private:
		std::vector<Card*> cards;
	};
}

