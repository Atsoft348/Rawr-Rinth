/* Borka 2D game framework, May 2012, Rachel J. Morris - www.moosader.com - zlib license */

#include <borka/Character.h>
#include <borka/LevelManager.h>

// TODO: remove IOSTREAM!!
#include <iostream>

namespace bork
{

Character::Character()
{
    m_score = 0;
}

void Character::Move( DIRECTION dir )
{
    // Check to see if moving in that direction will cause a collision.
    // If not, the move the character.
    Vector2f newCoords = m_coordinates;

    switch( dir )
    {
        case UP:
            newCoords.y = newCoords.y - m_speed;
        break;

        case DOWN:
            newCoords.y = newCoords.y + m_speed;
        break;

        case LEFT:
            newCoords.x = newCoords.x - m_speed;
        break;

        case RIGHT:
            newCoords.x = newCoords.x + m_speed;
        break;

        default:
        break;
    }

    if ( !bork::LevelManager::CheckCollision( newCoords, m_dimensions ) )
    {
        SetCoordinates( newCoords );
    }
}

void Character::SetGoal( const Entity& item )
{
    m_goalCoord.x = item.X();
    m_goalCoord.y = item.Y();
}

void Character::MoveTowardGoal()
{
    if ( m_goalCoord.x < m_coordinates.x )
    {
        Move( LEFT );
    }
    else if ( m_goalCoord.x > m_coordinates.x )
    {
        Move( RIGHT );
    }

    if ( m_goalCoord.y < m_coordinates.y )
    {
        Move( UP );
    }
    else if ( m_goalCoord.y > m_coordinates.y )
    {
        Move( DOWN );
    }
}

void Character::Update()
{
}

}

