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

		void Initialize();		

	private:
		int NumberPlayer;
		vector<shared_ptr<Board>> PlayersBoard;
		vector<shared_ptr<Player>> Players;
	};
}

