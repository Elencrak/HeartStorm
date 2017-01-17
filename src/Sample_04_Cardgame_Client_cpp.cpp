// Sample_04_Cardgame_Client_cpp.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "stormancer.h"
#include <iostream>
#include "Online/AuthenticationPlugin.h"
#include "Online/MatchmakingPlugin.h"
#include "Online/TurnByTurnPlugin.h"
#include "Online/GameSession.h"
#include "Game.h"
#include "Card.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>

using namespace JojoBen;

int ApplyTransaction(Stormancer::UpdateDto t, shared_ptr<Game> currentGame)
{
	if (t.cmd == "start")
	{		
		currentGame->Initialize(t.json_args()[L"seed"].as_integer());	
	}
	else if (t.cmd == "PlayCard")
	{
		int playerId = currentGame->playerTurn;
		int cardIndex = t.json_args()[L"Choice"].as_integer();
		cout << cardIndex;
		currentGame->GetPlayer(playerId).get()->PlayCard(cardIndex);
	}
	else if (t.cmd == "Pick")
	{
		int playerId = currentGame->playerTurn;
		currentGame->GetPlayer(playerId).get()->Draw();
	}
	else if (t.cmd == "AttackCard")
	{
		int playerId = currentGame->playerTurn;
		int cardIndex = t.json_args()[L"CardID"].as_integer();		
		int targetPlayer = t.json_args()[L"TargetPlayer"].as_integer();
		int targetCardIndex = t.json_args()[L"TargetCardIndex"].as_integer();
		currentGame->AttackCard(playerId, cardIndex, targetPlayer, targetCardIndex);
		auto playedCardTarget = currentGame->GetPlayer(targetPlayer)->GetBoard();
		currentGame->GetPlayer(playerId)->GetBoard().get()->ExhaustCard(cardIndex);
		if (playedCardTarget->GetPlayedCard()[targetCardIndex]->IsDead())
		{
			playedCardTarget->EraseCard(targetCardIndex);
		}
		auto playedCardPlayer = currentGame->GetPlayer(playerId)->GetBoard();
		if (playedCardPlayer->GetPlayedCard()[cardIndex]->IsDead())
		{
			playedCardPlayer->EraseCard(cardIndex);
		}
	}
	else if (t.cmd == "AttackPlayer")
	{
		cout << "attack player" << endl;
		int cardIndex = t.json_args()[L"CardID"].as_integer();
		int targetPlayer = t.json_args()[L"TargetPlayer"].as_integer();
		int damage = currentGame->GetPlayer(currentGame->playerTurn).get()->GetBoard().get()->GetPlayedCard()[cardIndex]->attack;
		currentGame->GetPlayer(targetPlayer)->TakeDamage(damage);
		currentGame->GetPlayer(currentGame->playerTurn)->GetBoard().get()->ExhaustCard(cardIndex);
		if (currentGame->GetPlayer(targetPlayer)->LifePoint <= 0)
		{
			cout << "Player " << currentGame->playerTurn << " win " << endl;
			currentGame->running = false;
		}
	}
	else if (t.cmd == "EndTurn")
	{
		currentGame->EndTurn();		
	}
	// A la fin il faut générer le hash pour le status du jeu
	return currentGame->GetGameHash();
}


int main(int argc, char *argv[])
{

	//test
	int localPlayer;

	srand(time(NULL));
	int result = rand();
	std::string login = std::to_string(result);

	// Save the login
	cout << "Enter login : " << endl;
	cin >> login;

	if (argc >= 2)
	{
		login = std::string(argv[1]);
	}
	//Create network client
	auto config = Stormancer::Configuration::create("http://api.stormancer.com", "ad912dff-cec9-0fb6-78f8-652d4c093508", "sample-04-cardgame");
	config->addPlugin(new Stormancer::AuthenticationPlugin()); //Adds Authentication
	config->addPlugin(new Stormancer::MatchmakingPlugin()); //Adds matchmaking & gamesession APIs
	config->addPlugin(new Stormancer::TurnByTurnPlugin());

	auto client = Stormancer::Client::createClient(config);

	auto auth = client->dependencyResolver()->resolve<Stormancer::IAuthenticationService>();
	std::cout << "Authenticating as '" << login << "'...";
	auto scene = auth->steamLogin(login).get();
	std::cout << "DONE" << std::endl;

	//Connect to the matchmaking scene
	auto matchmakingScene = auth->getPrivateScene("matchmaking-fast").get();
	matchmakingScene.lock()->connect().get();

	auto matchmaking = matchmakingScene.lock()->dependencyResolver()->resolve<Stormancer::MatchmakingService>();

	///Configure a task_completion_event which will fire when a game is found.
	auto tce = pplx::task_completion_event<Stormancer::MatchmakingResponse>{};
	matchmaking->onMatchFound([tce](Stormancer::MatchmakingResponse response)
	{

		tce.set(response);

	});

	matchmaking->findMatch("matchmaking-sample");

	std::cout << "waiting for game...";
	Stormancer::MatchmakingResponse mmResponse = pplx::create_task(tce).get();
	std::cout << "FOUND" << std::endl;

	Stormancer::ScenePtr game_scene = auth->getPrivateScene(mmResponse.gameId).get();
	
	//Create game
	// il faut que je set tous le player id;
	shared_ptr<Game> currentGame = make_shared<Game>(2);

	auto transactionBroker = game_scene.lock()->dependencyResolver()->resolve<Stormancer::TurnByTurnService>();
	bool running = true;
	transactionBroker->onDesyncErrorCallback([&running](std::string error)
	{
		std::cout << "A desynchronization error occured. Details : " << error << std::endl;
		running = false;
	});
	transactionBroker->onUpdateGameCallback([&currentGame](Stormancer::UpdateDto update)
	{

		auto newHash = ApplyTransaction(update, currentGame);
		//std::cout << "game state updated : " << currentGame << std::endl;
		return newHash; //Returns the new hash to the server for validation
	});
	transactionBroker->onReplayTLog([&currentGame,&running](std::vector<Stormancer::TransactionLogItem> transactions)
	{
		std::cout << "Replay existing transaction log...";
		for (auto t : transactions)
		{
			auto newHash = ApplyTransaction(t.transactionCommand, currentGame);
			if (t.hashAvailable && t.resultHash != newHash)
			{
				std::cout << "Desynchronization while playing Transaction log. Expected "<<t.resultHash << " obtained "<< newHash << std::endl;
				std::string v;
				std::cin >> v;
				running = false;
				break;
			}
		}
	});

	std::cout << "Connecting to game...";
	auto gameSession = game_scene.lock()->dependencyResolver()->resolve<Stormancer::GameSessionService>();

	gameSession->connect().get();//Connect to the game session

	gameSession->ready();//Inform the server we are ready to play
	gameSession->waitServerReady().get();//
	std::cout << "CONNECTED" << std::endl;

	
	// Initialization
	int seed = 123456789;
	int n;

	if (auth->GetUsername() == mmResponse.team1.at(0).pseudo)
	{
		localPlayer = 0;
	}
	else
	{
		localPlayer = 1;
	}

	cout << auth->userId() << endl;

	currentGame->running = true;

	while (currentGame->running)
	{		
		if (currentGame->playerTurn == localPlayer)
		{
			// INITIALIZATION
			int otherPlayer = currentGame->playerTurn + 1;
			otherPlayer = otherPlayer % 2;
			
			//Pick card
			auto json = web::json::value();
			json[L"PlayerId"] = currentGame->playerTurn;
			try
			{
				auto t = transactionBroker->submitTransaction(auth->userId(), "Pick", json);
				t.get();
			}
			catch (std::exception& ex)
			{
				std::cout << ex.what();
			}
			

			// Display hand and board			
			cout << currentGame->GetPlayer(currentGame->playerTurn).get()->GetHand()->ToString() << endl;

			cout << "--------------------- My BOARD ---------------------\n" << endl;
			cout << "--------------------- Player PV " << currentGame->GetPlayer(currentGame->playerTurn).get()->LifePoint << " ---------------------\n" << endl;
			cout << currentGame->GetPlayer(currentGame->playerTurn).get()->GetBoard()->ToString() << endl;		

			cout << "--------------------- Other BOARD ---------------------\n" << endl;
			cout << "--------------------- Player PV " << currentGame->GetPlayer(otherPlayer).get()->LifePoint << " ---------------------\n" << endl;
			cout << currentGame->GetPlayer(otherPlayer).get()->GetBoard()->ToString() << endl;

			// Play card
			int cardID;	
			cout << "------------------- Play card -------------------" << endl;
			cin >> cardID;
			cout << endl;

			if (cardID == 666)
			{
				try
				{
					auto t = transactionBroker->submitTransaction(auth->userId(), "EndTurn", json);
					t.get();
					cout << "------------------- Wait for other player -------------------" << endl;
				}
				catch (std::exception& ex)
				{
					std::cout << ex.what();
				}
				continue;
			}

			auto jsonPlayCard = web::json::value();
			jsonPlayCard[L"Choice"] = cardID - 1;
			jsonPlayCard[L"Player"] = currentGame->playerTurn;
			try
			{
				auto t = transactionBroker->submitTransaction(auth->userId(), "PlayCard", jsonPlayCard);
				t.get();
			}
			catch (std::exception& ex)
			{
				std::cout << ex.what();
			}
			// Display boards after playing card
			cout << "--------------------- My BOARD---------------------\n" << endl;
			cout << "--------------------- Player PV " << currentGame->GetPlayer(currentGame->playerTurn).get()->LifePoint << " ---------------------\n" << endl;
			cout << currentGame->GetPlayer(currentGame->playerTurn).get()->GetBoard()->ToString() << endl;			
			
			cout << "--------------------- Other BOARD ---------------------\n" << endl;		
			cout << "--------------------- Player PV " << currentGame->GetPlayer(otherPlayer).get()->LifePoint << " ---------------------\n" << endl;
			cout << currentGame->GetPlayer(otherPlayer).get()->GetBoard()->ToString() << endl;

			replayCard:
			// Attack phase
			if (currentGame->GetPlayer(currentGame->playerTurn).get()->GetBoard()->GetPlayedCard().size() != 0 && currentGame->GetPlayer(currentGame->playerTurn).get()->GetBoard()->FreeNumber() != 0)
			{
				auto jsonAttack = web::json::value();
				cout << "------------------- Select Card to use -------------------" << endl;
				cout << "--------------------- My BOARD---------------------\n" << endl;
				cout << "--------------------- Player PV " << currentGame->GetPlayer(currentGame->playerTurn).get()->LifePoint << " ---------------------\n" << endl;
				cout << currentGame->GetPlayer(currentGame->playerTurn).get()->GetBoard()->ToString() << endl;
				cin >> cardID;
				int boardSizePlayer = currentGame->GetPlayer(currentGame->playerTurn).get()->GetBoard()->GetPlayedCard().size();
				if (cardID <= 0 || cardID > boardSizePlayer)
				{
					cout << "input invalide " << endl;
					goto replayCard;
				}
				if (currentGame->GetPlayer(currentGame->playerTurn).get()->GetBoard()->GetPlayedCard().at(cardID - 1)->exhausted)
				{
					cout << "carte épuisee " << endl;
					goto replayCard;
				}
				if (cardID == 666)
				{
					try
					{
						auto t = transactionBroker->submitTransaction(auth->userId(), "EndTurn", json);
						t.get();
						cout << "------------------- Wait for other player -------------------" << endl;
					}
					catch (std::exception& ex)
					{
						std::cout << ex.what();
					}
					continue;
				}

				jsonAttack[L"CardID"] = cardID - 1;
				jsonAttack[L"TargetPlayer"] = otherPlayer;
				int cardToAttack = 0;
				if (currentGame->GetPlayer(otherPlayer).get()->GetBoard()->GetPlayedCard().size() != 0 && currentGame->GetPlayer(otherPlayer).get()->GetBoard()->FreeNumber() != 0)
				{
					cout << "------------------- Select Card to attack -------------------" << endl;
					cout << "--------------------- Other BOARD ---------------------\n" << endl;
					cout << "--------------------- Player PV " << currentGame->GetPlayer(otherPlayer).get()->LifePoint << " ---------------------\n" << endl;
					cout << currentGame->GetPlayer(otherPlayer).get()->GetBoard()->ToString() << endl;
					cin >> cardToAttack;
					cout << endl;
					int boardSize = currentGame->GetPlayer(otherPlayer).get()->GetBoard()->GetPlayedCard().size();
					if (cardToAttack <= 0 || cardToAttack > boardSize)
					{
						cout << "input invalide " << endl;
						goto replayCard;
					}
					if (cardToAttack == 666)
					{
						try
						{
							auto t = transactionBroker->submitTransaction(auth->userId(), "EndTurn", json);
							t.get();
							cout << "------------------- Wait for other player -------------------" << endl;
						}
						catch (std::exception& ex)
						{
							std::cout << ex.what();
						}
						continue;
					}

					jsonAttack[L"TargetCardIndex"] = cardToAttack - 1;

					try
					{
						auto t = transactionBroker->submitTransaction(auth->userId(), "AttackCard", jsonAttack);
						t.get();
					}
					catch (std::exception& ex)
					{
						std::cout << ex.what();
					}

				}
				else
				{
					try
					{
						auto t = transactionBroker->submitTransaction(auth->userId(), "AttackPlayer", jsonAttack);
						t.get();
					}
					catch (std::exception& ex)
					{
						std::cout << ex.what();
					}
				}
				goto replayCard;
			}
			try
			{
				auto t = transactionBroker->submitTransaction(auth->userId(), "EndTurn", json);
				t.get();
				cout << "------------------- Wait for other player -------------------" << endl;
			}
			catch (std::exception& ex)
			{
				std::cout << ex.what();
			}
		}			
	}

	std::cout << "disconnecting...";
	client->disconnect().get();
	std::cout << "DONE" << std::endl;
	system("pause");
	return 0;
}



