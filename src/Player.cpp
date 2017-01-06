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

	void Player::PlayCard(Card * card)
	{
		playerBoard->PlayCard(card);
		playerHand->RemoveCard(card);
	}

	Player::Player()
	{
		playerDeck = new Deck(20);
		playerHand = new Hand();
	}


	Player::~Player()
	{
		delete playerDeck;
		delete playerHand;
	}
}
