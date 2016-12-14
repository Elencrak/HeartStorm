#pragma once
#include "Card.h";

using namespace std;

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

		//Getter
		vector<Card*> GetPlayedCard();
	private:
		vector<Card*> PlayedCard;
	};
}

