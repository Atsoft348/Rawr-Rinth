/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "Player.h"

Player::Player()
{
    m_speed = 5;
    m_regionShape.Color( sf::Color( 255, 0, 0, 255 ) );
}

void Player::Update()
{
    Character::Update();
}
