#pragma once
namespace JojoBen
{

	class Card
	{
	public:
		static Card* MakeCard();
		static Card* MakeCard(int attack, int defence);
		static Card* MakeCard(int valuePoints);
		int attack;
		int defence;

		~Card();
	private:
		Card(int atk, int def);
		Card();
	};

}

