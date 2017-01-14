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
		//SeedForGame = Seed;
		SeedForGame = 0; // For Debug
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

	int Game::GetGameHash()
	{
		//TODO : Implements
		return 0;
	}
	
	int Game::GetBoardsHash() 
	{
		int result = 0;
		for (int i = 0; i < PlayersBoard.size(); i++)
		{
			result = 31 * result + PlayersBoard[i]->GetHash();
		}
		return result;
	}

	/*int Game::GetPlayerHash()
	{
		int result = 0;
		for (int i = 0; i < Players.size(); i++)
		{
			result = 31 * result + Players[i]->GetHash();
		}
		//TODO : implements
		return 0;
	}*/
}
