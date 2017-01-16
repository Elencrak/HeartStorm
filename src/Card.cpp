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
		int attack = rand()%valuePoints;
		return new Card(attack, valuePoints - attack);
	}

	Card * Card::MakeCard(int attack, int defence)
	{
		return new Card(attack, defence);
	}

	Card * Card::MakeCard(int valuePoints)
	{
		int attack = rand() % valuePoints;
		return new Card(attack, valuePoints - attack);
	}

	void Card::TakeDamage(int value)
	{

	}

	Card::~Card()
	{

	}
}
