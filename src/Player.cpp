#include "stdafx.h"
#include "Player.h"

namespace JojoBen
{
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

	Player::Player(int _ID)
	{
		ID = _ID;
		playerDeck = new Deck();
		playerHand = new Hand();
	}


	Player::~Player()
	{
		delete playerDeck;
		delete playerHand;
	}
}
