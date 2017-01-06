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
			currentPlayer->Initialize(currentPlayerBoard);

			PlayersBoard.push_back(currentPlayerBoard);
			Players.push_back(currentPlayer);
		}
	}

	int Game::GetGameHash()
	{
		
	}
	
	int Game::GetBoardsHash() 
	{
		int result = 0;
		for (int i = 0; i < PlayersBoard.size(); i++)
		{
			result = 31 * result + PlayersBoard[i]->GetHash();
		}
	}

	int Game::GetPlayerHash()
	{
		int result = 0;
		for (int i = 0; i < Players.size(); i++)
		{
			result = 31 * result + Players[i]->GetHash();
		}
	}
}
