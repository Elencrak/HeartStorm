#include "stdafx.h"
#include "Game.h"

namespace JojoBen {
	Game::Game(int numberPlayer)
	{		
		NumberPlayer = numberPlayer;
	}


	Game::~Game()
	{
	}

	void Game::Initialize(int Seed)
	{
		SeedForGame = Seed;
		for (int i = 0; i < NumberPlayer; i++)
		{
			shared_ptr<Board> currentPlayerBoard;
			currentPlayerBoard = make_shared<Board>();
			
			shared_ptr<Player> currentPlayer;
			currentPlayer = make_shared<Player>();
			currentPlayer->Initialize(currentPlayerBoard, Seed);

			PlayersBoard.push_back(currentPlayerBoard);
			Players.push_back(currentPlayer);
		}
	}
}
