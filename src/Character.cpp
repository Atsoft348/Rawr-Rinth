/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "Character.h"

#include <iostream>

Character::Character()
{
    m_isRunning = false;
}

void Character::ToggleRun()
{
    m_isRunning = !m_isRunning;
}

void Character::Move( DIRECTION dir )
{
    float speed = 2;
    if ( m_isRunning )
    {
        speed = 4;
    }
    switch( dir )
    {
        case UP:
            SetCoordinates( X(), Y() - speed );
        break;

        case DOWN:
            SetCoordinates( X(), Y() + speed );
        break;

        case LEFT:
            SetCoordinates( X() - speed, Y() );
        break;

        case RIGHT:
            SetCoordinates( X() + speed, Y() );
        break;

        default:
        break;
    }
}


