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

	int Board::GetHash()
	{
		int result = 0;
		for (auto c : PlayedCard)
		{
			result = 31 * result + c->CardId;
		}

		return result;
	}

	std::vector<Card*> Board::GetPlayedCard()
	{
		return PlayedCard;
	}
}