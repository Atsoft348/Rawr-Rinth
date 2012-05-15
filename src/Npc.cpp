/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "Npc.h"

Npc::Npc()
{
    m_score = 0;
    m_speed = 1;
    m_horiz = 0;
}

void Npc::DecideWhatToDo( const bork::Entity& goal )
{
    if ( m_horiz )
    {
        if ( goal.X() < m_coordinates.x )
        {
            Move( bork::LEFT );
        }
        else if ( goal.X() > m_coordinates.x )
        {
            Move( bork::RIGHT );
        }
    }
    else
    {

        if ( goal.Y() < m_coordinates.y )
        {
            Move( bork::UP );
        }
        else if ( goal.Y() > m_coordinates.y )
        {
            Move( bork::DOWN );
        }
    }

    m_horiz = !m_horiz;
}
