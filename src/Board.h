#pragma once
#include "Card.h"
using namespace std;

class Card;

namespace JojoBen
{
	class Board
	{
	public:
		int OwnerBoard;

		Board();
		~Board();
		
		void Initialize();
		void PlayCard(Card* cardToPlay);
		
		//void ChooseAttackers();

		//void ChooseDefend();
		
		int GetHash();

		std::string ToString();

		//Getter
		vector<Card*> GetPlayedCard();

		void AttackCard(int target);
	private:
		vector<Card*> PlayedCard;
	};
}
