#include "stdafx.h"
#include "Board.h"

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

	std::vector<Card*> Board::GetPlayedCard()
	{
		return PlayedCard;
	}
}