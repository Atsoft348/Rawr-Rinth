/* Borka 2D game framework, May 2012, Rachel J. Morris - www.moosader.com - zlib license */

#include <borka/LevelManager.h>
#include <borka/DebugLog.h>
#include <borka/Utilities.h>

#include "Character.h"

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
        Coordinates( newCoords );
    }
}

void Character::SetGoal( const Entity& item )
{
    bork::DLog::Out( "Character", "SetGoal", "Set entity \"" + m_sId + "\" goal to \"" + item.m_sId + "\"", 1 );
    m_goal.coord.x = item.X();
    m_goal.coord.y = item.Y();
    m_goal.name = item.m_sId;
}

void Character::MoveTowardGoal()
{
    bork::DLog::Out( "Character", "MoveTowardGoal", "Move toward goal \""
        + m_goal.name + "\" at "
        + bork::IntToString( m_goal.coord.x ) + ", " + bork::IntToString( m_goal.coord.y ) );
    if ( m_goal.coord.x < m_coordinates.x )
    {
        Move( LEFT );
    }
    else if ( m_goal.coord.x > m_coordinates.x )
    {
        Move( RIGHT );
    }

    if ( m_goal.coord.y < m_coordinates.y )
    {
        Move( UP );
    }
    else if ( m_goal.coord.y > m_coordinates.y )
    {
        Move( DOWN );
    }
}

void Character::Update()
{
}

void Character::AddExp( int amount )
{
    m_stats.totalExp += amount;
    // Check for level-up
}

}

