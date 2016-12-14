#include "stdafx.h"
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
		for (int i = 0; i < 20; i++)
		{
			cards.push_back(Card::MakeCard());
		}
	}

	Deck::~Deck()
	{
		for each (Card* c in cards)
		{
			delete c;
		}
		cards.clear();
	}
}

