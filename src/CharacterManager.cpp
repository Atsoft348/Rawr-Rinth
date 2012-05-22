/* Borka 2D game framework, May 2012, Rachel J. Morris - www.moosader.com, http://code.google.com/p/borka/ - zlib license */

#include "CharacterManager.h"

#include <iostream>

std::vector<Npc> CharacterManager::m_lstNpcs;
std::vector<bork::Item> CharacterManager::m_lstItems;
Player CharacterManager::m_player;

void CharacterManager::Init()
{
}

int CharacterManager::AddNpc( Npc& character, const std::string& name )
{
    character.m_sId = name;
    character.m_nId = m_lstNpcs.size();
    m_lstNpcs.push_back( character );
    return m_lstNpcs.size() - 1;
}

Npc& CharacterManager::GetNpc( const std::string& sId )
{
    for ( unsigned int i = 0; i < m_lstNpcs.size(); i++ )
    {
        if ( m_lstNpcs[i].m_sId == sId )
        {
            return m_lstNpcs[i];
        }
    }
    // TODO: Figure out a better way to handle no-image.
    // Or, default image could be "blank texture" Npc?
    return m_lstNpcs[0];
}

Npc& CharacterManager::GetNpc( int nId )
{
    return m_lstNpcs[nId];
}

int CharacterManager::AddItem( bork::Item& item, const std::string& name )
{
    item.m_sId = name;
    item.m_nId = m_lstItems.size();
    m_lstItems.push_back( item );
    return m_lstItems.size() - 1;
}

bork::Item& CharacterManager::GetItem( const std::string& sId )
{
    for ( unsigned int i = 0; i < m_lstItems.size(); i++ )
    {
        if ( m_lstItems[i].m_sId == sId )
        {
            return m_lstItems[i];
        }
    }
    // TODO: Figure out a better way to handle no-image.
    // Or, default image could be "blank texture" Character?
    return m_lstItems[0];
}

bork::Item& CharacterManager::GetItem( int nId )
{
    return m_lstItems[nId];
}

void CharacterManager::PushDrawables()
{
    for ( unsigned int i = 0; i < m_lstNpcs.size(); i++ )
    {
        bork::Renderer::PushDrawable( m_lstNpcs[i] );
    }

    for ( unsigned int i = 0; i < m_lstItems.size(); i++ )
    {
        bork::Renderer::PushDrawable( m_lstItems[i] );
    }

    bork::Renderer::PushDrawable( m_player );
}

void CharacterManager::Update()
{
    m_player.Update();
    if ( m_player.IsCollision( GetItem( "item" ) ) )
    {
        m_player.IncrementScore();
        GetItem( "item" ).GenerateCoordinates();
        GetNpc( "enemy" ).SetGoal( GetItem( "item" ) );
    }
    // Update characters - for NPC, this will move them toward goal.
    for ( unsigned int i = 0; i < m_lstNpcs.size(); i++ )
    {
        m_lstNpcs[i].Update();

        if ( m_lstNpcs[i].IsCollision( GetItem( "item" ) ) )
        {
            m_lstNpcs[i].IncrementScore();
            GetItem( "item" ).GenerateCoordinates();
            GetNpc( "enemy" ).SetGoal( GetItem( "item" ) );
        }
    }
}



