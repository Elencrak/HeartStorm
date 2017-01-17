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
		int playerTurn = 0;
		Game(int numberPlayer);
		~Game();

		void Initialize(int seed);		

		void EndTurn();

		int GetGameHash();
		int GetBoardsHash();
		shared_ptr<Player> GetPlayer(int ID);

		void AttackCard(int sourcePlayer, int sourceCard, int targetPlayer, int targetCard);

	private:
		int NumberPlayer;
		int SeedForGame;
		vector<shared_ptr<Board>> PlayersBoard;
		vector<shared_ptr<Player>> Players;
	};
}

