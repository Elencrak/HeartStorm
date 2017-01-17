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
		if (attack - value <= 0)
		{	
			std::cout << "Card " << CardId << " is Dead" << std::endl;
			defence = 0;
		}
		else
		{
			defence - value;
			std::cout << "------ Card " << CardId << " have " << defence << "life point -----" << std::endl;
		}
	}

	bool Card::IsDead()
	{
		if (defence <= 0)
		{
			return true;
		}
		return false;
	}

	Card::~Card()
	{

	}
}
