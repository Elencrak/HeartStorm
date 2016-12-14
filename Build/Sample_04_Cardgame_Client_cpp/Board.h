#pragma once
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
		
		void ChooseAttackers();

		void ChooseDefend();
		//Getter
		vector<Card*> GetPlayedCard();
	private:
		vector<Card*> PlayedCard;
	};
}

