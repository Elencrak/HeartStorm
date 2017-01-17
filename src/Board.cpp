#include "stdafx.h"
#include "Board.h"
#include "Card.h"

namespace JojoBen 
{
	Board::Board()
	{
	}


	Board::~Board()
	{
	}

	void Board::Initialize()
	{

	}

	void Board::PlayCard(Card* cardToPlay)
	{
		PlayedCard.push_back(cardToPlay);
	}

	void Board::EraseCard(int cardIndex)
	{
		PlayedCard.erase(PlayedCard.begin() + cardIndex);
	}

	void Board::ExhaustCard(int cardIndex)
	{
		PlayedCard.at(cardIndex)->exhausted = true;
	}

	int Board::FreeNumber()
	{
		int ret = 0;
		for each (Card* c in PlayedCard)
		{
			if (!c->exhausted)
				ret++;
		}
		return ret;
	}

	void Board::RestoreCards()
	{
		for each (Card* c in PlayedCard)
		{
			c->exhausted = false;
		}
	}

	int Board::GetHash()
	{
		int result = 0;
		for (auto c : PlayedCard)
		{
			result = 31 * result + c->CardId;
		}

		return result;
	}

	std::string Board::ToString()
	{
		std::string ret = "";
		int index = 1; 
		for each (Card* c in PlayedCard)
		{
			ret += std::to_string(index);
			ret += c->ToString();
			ret += "\n";
			index++;
		}
		ret += "\n";
		return ret;
	}

	std::vector<Card*> Board::GetPlayedCard()
	{
		return PlayedCard;
	}
}