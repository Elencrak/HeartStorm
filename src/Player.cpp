#include "stdafx.h"
#include "Player.h"

namespace JojoBen
{

	Player::Player(int _ID)
	{
		ID = _ID;
		playerDeck = new Deck();
		playerHand = new Hand();

		for (int i = 0; i < 7; i++) 
		{
			this->Draw();
		}
	}

	Player::~Player()
	{
		delete playerDeck;
		delete playerHand;
	}

	void Player::Initialize(std::shared_ptr<Board> board, int seed)
	{
		srand(seed);
		playerBoard = board;
	}

	void Player::Draw()
	{
		if(!playerDeck->isEmpty())
			playerHand->AddCard(playerDeck->Draw());
	}

	void Player::PlayCard(int index)
	{
		if (index > playerHand->Count())
			std::cout << "There is no " << index << "th card" << std::endl;
		else
		{
			Card* card = playerHand->GetCard(index);
			playerBoard->PlayCard(card);
			playerHand->RemoveCard(card);
		}
	}

	void Player::SetNetworkID(std::string _netID)
	{
		netID = _netID;
	}

	std::string Player::GetNetworkID()
	{
		return netID;
	}

	std::shared_ptr<JojoBen::Board> Player::GetBoard()
	{
		return playerBoard;
	}

	int Player::GetHash()
	{
		int result = 0;
		//Todo faire le hash pour le player
		return 0;

	}
}
