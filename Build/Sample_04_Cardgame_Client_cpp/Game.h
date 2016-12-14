#pragma once

#include <iostream>
#include <vector>

#include "Deck.h"
#include "Board.h"

using namespace std;

namespace JojoBen {
	class Game
	{
	public:
		Game();
		~Game();

	private:
		vector<Deck> PlayersDeck;
		vector<Board> BoardsPlayer;
		
	};
}

