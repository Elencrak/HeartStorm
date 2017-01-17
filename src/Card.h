#pragma once
namespace JojoBen
{

	class Card
	{
	public:
		int CardId;	
		int attack;
		int defence;

		static Card* MakeCard();
		static Card* MakeCard(int attack, int defence);
		static Card* MakeCard(int valuePoints);

		std::string ToString();
		void TakeDamage(int value);
		bool IsDead();

		~Card();
	private:
		bool isDead;
		Card(int atk, int def);
		Card();
	};

}

