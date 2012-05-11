/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "Character.h"

void Character::Move( DIRECTION dir )
{
    float speed = 10; // TODO: TEMP
    switch( dir )
    {
        case UP:
            m_sprite.SetY( Y() - speed );
        break;

        case DOWN:
            m_sprite.SetY( Y() + speed );
        break;

        case LEFT:
            m_sprite.SetX( X() - speed );
        break;

        case RIGHT:
            m_sprite.SetX( X() + speed );
        break;

        default:
        break;
    }
}


