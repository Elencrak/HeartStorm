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
			currentPlayer = make_shared<Player>(i);
			currentPlayer->Initialize(currentPlayerBoard, Seed);

			PlayersBoard.push_back(currentPlayerBoard);
			Players.push_back(currentPlayer);
		}
	}

	void Game::EndTurn()
	{
		playerTurn++;
		playerTurn = playerTurn%NumberPlayer;
		for each (std::shared_ptr<Player> pl in Players)
		{
			pl->GetBoard().get()->RestoreCards();
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

	shared_ptr<Player> Game::GetPlayer(int ID)
	{
		return Players[ID];
	}

	void Game::AttackCard(int sourcePlayer, int sourceCard, int targetPlayer, int targetCard)
	{
		shared_ptr<Player> sourceP = GetPlayer(sourcePlayer);
		shared_ptr<Player> targetP = GetPlayer(targetPlayer);
		
		shared_ptr<Board> sourceBoard = sourceP->GetBoard();
		shared_ptr<Board> targetBoard = targetP->GetBoard();

		// Attack target
		targetBoard->GetPlayedCard()[targetCard]->TakeDamage(sourceBoard->GetPlayedCard()[sourceCard]->attack);

		// Contre attack
		sourceBoard->GetPlayedCard()[sourceCard]->TakeDamage(targetBoard->GetPlayedCard()[targetCard]->attack);
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
