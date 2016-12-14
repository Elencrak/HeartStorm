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

	}


	Deck::~Deck()
	{
	}
}
