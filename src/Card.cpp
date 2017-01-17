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

	std::string Card::ToString()
	{
		std::string ret = "Attack : ";
		ret += std::to_string(attack);
		ret += " defence: ";
		ret += std::to_string(defence);
		ret += " exhausted : ";
		ret += std::to_string(exhausted);
		return ret;
	}

	void Card::TakeDamage(int value)
	{
		if (defence - value <= 0)
		{	
			std::cout << "Card " << std::to_string(CardId) << " is Dead" << std::endl;
			defence = 0;			
		}
		else
		{
			defence -= value;
			std::cout << "------ Card " << std::to_string(CardId) << " have " << std::to_string(defence) << "life point -----" << std::endl;
		}
	}

	bool Card::IsDead()
	{
		return defence <= 0;	
	}

	Card::~Card()
	{

	}
}
