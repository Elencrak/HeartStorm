#include "stdafx.h"
#include "Deck.h"

namespace JojoBen
{
	Deck::Deck()
	{
		cards = std::vector<Card*>(deckSize);
		for (int i = 0; i < deckSize; i++)
		{
			cards.at(i) = (Card::MakeCard());
		}
	}

	Deck::Deck(int size)
	{
		deckSize = size;
		cards = std::vector<Card*>(deckSize);
		for (int i = 0; i < deckSize; i++)
		{
			cards.at(i) = (Card::MakeCard());
		}
	}

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
