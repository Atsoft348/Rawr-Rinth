/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "Character.h"

void Character::Move( DIRECTION dir )
{
    float speed = 1; // TODO: TEMP
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


