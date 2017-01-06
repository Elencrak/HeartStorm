#pragma once

#include <iostream>
#include <vector>

#include "Deck.h"
#include "Board.h"
#include "Player.h"

using namespace std;

namespace JojoBen {
	class Game
	{
	public:
		Game(int numberPlayer);
		~Game();

		void Initialize(int seed);		

		void PlayCard(int CardToPlay, int TargetPlayer);
		void EndTurn();

	private:
		int NumberPlayer;
		int SeedForGame;
		vector<shared_ptr<Board>> PlayersBoard;
		vector<shared_ptr<Player>> Players;
	};
}

