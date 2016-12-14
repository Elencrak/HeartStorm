#include "stdafx.h"
#include "Card.h"

namespace JojoBen
{
	Card::Card(int atk, int def)
	{
		attack = atk;
		defence = def;
	}

	Card::Card()
	{
		attack = 0;
		defence = 0;
	}


	Card * Card::MakeCard()
	{
		int valuePoints = 10;
		return nullptr;
	}

	Card * Card::MakeCard(int attack, int defence)
	{
		return nullptr;
	}

	Card * Card::MakeCard(int valuePoints)
	{
		return nullptr;
	}

	Card::~Card()
	{

	}
}
