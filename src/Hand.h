#pragma once
#include "Card.h"
#include <Vector>

namespace JojoBen
{

	class Hand
	{
	public:
		void AddCard(Card* card);
		void RemoveCard(Card* card);
		int Count();
		Card* GetCard(int index);
		Hand();
		~Hand();
		std::string ToString();
		int GetHash();

	private:
		std::vector<Card*> cards;
	};
}

