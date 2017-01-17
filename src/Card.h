#pragma once
namespace JojoBen
{

	class Card
	{
	public:
		int CardId;

		static Card* MakeCard();
		static Card* MakeCard(int attack, int defence);
		static Card* MakeCard(int valuePoints);
		int attack;
		int defence;

		std::string ToString();
		void TakeDamage(int value);
		~Card();
	private:
		Card(int atk, int def);
		Card();
	};

}

