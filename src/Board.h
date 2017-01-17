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

		void EraseCard(int cardIndex);
		void ExhaustCard(int cardIndex);
		int FreeNumber();
		void RestoreCards();
		
		int GetHash();

		std::string ToString();

		//Getter
		vector<Card*> GetPlayedCard();

		void AttackCard(int target);
	private:
		vector<Card*> PlayedCard;
	};
}
