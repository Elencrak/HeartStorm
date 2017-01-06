#include "stdafx.h"
#include "Hand.h"
namespace JojoBen
{
	void Hand::AddCard(Card* card)
	{
		cards.push_back(card);
	}

	Hand::Hand()
	{
		cards = std::vector<Card*>();
	}

	Hand::~Hand()
	{
		for each (Card* c in cards)
		{
			delete c;
		}
		cards.clear();
	}
}
