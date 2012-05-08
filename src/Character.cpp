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

/*
Copyright (C) 2012 Rachel J. Morris

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Rachel J. Morris RachelJMorris@gmail.com
*/


