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
		int targetCardIndex = t.json_args()[L"Target"].as_integer();
		int targetPlayer = t.json_args()[L"TargetPlayer"].as_integer();
		currentGame->playCard(playerId, cardIndex, targetPlayer, targetCardIndex);
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

	while (running)
	{		
		if (currentGame->playerTurn == localPlayer)
		{
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
			// Display hand

			currentGame->GetPlayer(currentGame->playerTurn).get()

			// Play card
			int cardID;
			int target;
			int cardToAttack;
			cout << "------------------- Play card -------------------" << endl;
			cin >> cardID;
			cout << "------------------- Select Player -------------------" << endl;
			cin >> cardToAttack;
			cout << "------------------- Select Card to attack -------------------" << endl;
			cin >> target;
			if (cardID != 0 && target != 0)
			{
				auto json = web::json::value();
				json[L"CardID"] = cardID;
				json[L"Target"] = target;
				json[L"TargetPlayer"] = cardToAttack;
				try
				{
					auto t = transactionBroker->submitTransaction(auth->userId(), "AttackCard", json);
					t.get();
				}
				catch (std::exception& ex)
				{
					std::cout << ex.what();
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
	}

	std::cout << "disconnecting...";
	client->disconnect().get();
	std::cout << "DONE" << std::endl;
	return 0;
}


