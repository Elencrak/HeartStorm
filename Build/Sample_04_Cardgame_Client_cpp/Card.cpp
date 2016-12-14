#include "stdafx.h"
#include "Card.h"
#include <random>

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
		return Card::MakeCard(10);
	}

	Card * Card::MakeCard(int attack, int defence)
	{
		return new Card(attack, defence);
	}

	Card * Card::MakeCard(int valuePoints)
	{
		Card* ret = new Card();
		ret->attack = std::rand() % valuePoints;
		ret->defence = valuePoints - ret->attack;
		return ret;
	}

	Card::~Card()
	{

	}
}
