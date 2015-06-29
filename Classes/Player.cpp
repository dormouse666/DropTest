//
//  Player.cpp
//  dormouseTest
//
//  Created by dormouse666 on 2015/06/30.
//
//

#include "Player.h"

USING_NS_CC;

bool Player::init()
{
    if (!Node::init()) {
        return false;
    }
    
    return true;
}

Player::Player()
: _spr(nullptr)
{
}

Player::~Player()
{
}

void Player::onEnter()
{
    Node::onEnter();
}

void Player::onExit()
{
    Node::onExit();
}
