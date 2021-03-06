#include "stdafx.h"
#include "Hand.h"
namespace JojoBen
{
	void Hand::AddCard(Card* card)
	{
		cards.push_back(card);
	}

	void Hand::RemoveCard(Card * card)
	{
		for (auto it = cards.begin(); it != cards.end(); it++)
		{
			if ((*it) == card)
			{
				cards.erase(it);
				return;
			}
		}
	}

	std::string Hand::ToString()
	{
		std::string ret = "---------------------HAND---------------------\n";
		int index = 1;
		for each (Card* c in cards)
		{
			ret += std::to_string(index) + " : ";
			ret += c->ToString();
			ret += "\n";
			index++;
		}
		ret += "\n";
		return ret;
	}

	int Hand::Count()
	{
		return cards.size();
	}

	Card* Hand::GetCard(int index)
	{
		return cards[index];
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

	int Hand::GetHash()
	{
		int result = 0;
		for (auto c : cards)
		{
			result = 31 * result + c->CardId;
		}
		return result;
	}

}
