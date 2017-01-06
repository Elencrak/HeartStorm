#include "stdafx.h"
#include "Deck.h"

namespace JojoBen
{
	Card * Deck::Draw()
	{
		Card* ret = cards.back();
		cards.pop_back();
		return ret;
	}

	bool Deck::isEmpty()
	{
		return cards.empty();
	}

	Deck::Deck()
	{
		cards = std::vector<Card*>(deckSize);
	}


	Deck::Deck(int size)
	{
		deckSize = size;
		cards = std::vector<Card*>(deckSize);
	}

	int Deck::GetHash()
	{
		int result = 0;
		for (auto c : cards)
		{
			result = 31 * result + c->CardId;
		}
		return result;
	}

	Deck::~Deck()
	{
		for (std::vector< Card* >::iterator it = cards.begin(); it != cards.end(); ++it)
		{
			delete (*it);
		}
		cards.clear();
	}
}
