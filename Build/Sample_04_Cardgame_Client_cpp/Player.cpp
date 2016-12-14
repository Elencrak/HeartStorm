#include "stdafx.h"
#include "Player.h"

namespace JojoBen
{
	void Player::Initialize(std::shared_ptr<Board> board)
	{
		playerBoard = board;
	}

	void Player::Draw()
	{
		playerHand->add(playerDeck->Draw());
	}

	void Player::PlayCard(Card * card)
	{

	}

	Player::Player()
	{

	}


	Player::~Player()
	{

	}
}
