/* Borka 2D game framework, May 2012, Rachel J. Morris - www.moosader.com - zlib license */

#include <borka/LevelManager.h>
#include <borka/DebugLog.h>
#include <borka/Utilities.h>

#include "Character.h"
#include "CharacterManager.h"

Character::Character()
{
    m_score = 0;
    m_stats.hp = 50;
    m_stats.level = 1;
    m_stats.attackPower = 5;
    m_stats.totalExp = 0;
    m_stats.getHurtCooldown = 0;
    m_isDead = false;
}

void Character::Move( DIRECTION dir )
{
    if ( !m_isDead )
    {
        // Check to see if moving in that direction will cause a collision.
        // If not, the move the character.
        bork::Vector2f newCoords = m_coordinates;

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

        if ( !bork::LevelManager::CheckCollision( newCoords, m_dimensions ) &&
            !CharacterManager::CheckCollision( newCoords, m_dimensions, m_sId ) )
        {
            // TODO: Reference to CharacterManager, circular dependency :(
            Coordinates( newCoords );
        }
    }
}

bool Character::GetHit( int opponentAtk )
{
    bool attackSuccessful = false;
    if ( m_stats.getHurtCooldown <= 0 )
    {
//        m_stats.hp -= opponentAtk;
        m_stats.getHurtCooldown = 20;
        attackSuccessful = true;
    }

    if ( m_stats.hp <= 0 )
    {
        // Dead
        m_isDead = true;
    }
    return attackSuccessful;
}

void Character::SetGoal( const Entity& item )
{
    m_goal.coord.x = item.X();
    m_goal.coord.y = item.Y();
    m_goal.name = item.m_sId;
}

void Character::MoveTowardGoal()
{
    if ( !m_isDead )
    {
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
}

void Character::Update()
{
    if ( !m_isDead )
    {
        if ( m_stats.getHurtCooldown > 0 )
        {
            m_stats.getHurtCooldown -= 1.0;
        }
    }
}

void Character::AddExp( int amount )
{
    m_stats.totalExp += amount;
    // Check for level-up
}

int Character::GetHP()
{
    return m_stats.hp;
}

int Character::GetAtk()
{
    if ( m_isDead )
    {
        return 0;
    }
    return m_stats.attackPower;
}

int Character::GetExp()
{
    return m_stats.totalExp;
}

int Character::GetLevel()
{
    return m_stats.level;
}

bool Character::IsAttackableCollision( const Entity& object )
{
    // Expand range of attackability
    if ( bork::GetDistance( m_coordinates, object.Coordinates() ) <= 64 )
    {
        return true;
    }
    return false;
}

