#include "stdafx.h"
#include "Player.h"

namespace JojoBen
{
	void Player::Initialize(std::shared_ptr<Board> board, int seed)
	{
		playerBoard = board;
		std::srand(seed);
		playerDeck = new Deck();

	}

	void Player::Draw()
	{
		if(!playerDeck->isEmpty())
			playerHand->AddCard(playerDeck->Draw());
	}

	void Player::PlayCard(Card * card)
	{

	}

	Player::Player()
	{

	}


	Player::~Player()
	{
		delete playerDeck;
		delete playerHand;
	}
}
