/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include <borka/Entity.h>
#include <borka/Renderer.h>
#include <borka/DebugLog.h>
#include <borka/GraphicManager.h>
#include <borka/Utilities.h>

#include "CharacterManager.h"

std::vector<Npc> CharacterManager::m_lstNpcs;
std::vector<bork::Item> CharacterManager::m_lstItems;
Player CharacterManager::m_player;

void CharacterManager::Init()
{
}

int CharacterManager::AddNpc( Npc& character, const std::string& name )
{
    bork::DLog::Out( "CharacterManager", "AddNpc", "Adding new NPC \"" + name + "\"" );
    bork::DLog::AdjustIndent( 1 );
    bork::DLog::Out( "CharacterManager", "AddNpc", "Coordinates: " + bork::IntToString( character.X() ) + ", " + bork::IntToString( character.Y() ) );
    character.m_sId = name;
    character.m_nId = m_lstNpcs.size();
    m_lstNpcs.push_back( character );
    bork::DLog::AdjustIndent( -1 );
    bork::DLog::Out( "CharacterManager", "AddNpc", "End" );
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

void CharacterManager::UpdateEntityOffsets( const bork::Vector2f& offset )
{
    for ( unsigned int i = 0; i < m_lstItems.size(); i++ )
    {
        m_lstItems[i].Offset( offset );
    }
    for ( unsigned int i = 0; i < m_lstNpcs.size(); i++ )
    {
        m_lstNpcs[i].Offset( offset );
    }
}

Npc& CharacterManager::GetNpc( int nId )
{
    return m_lstNpcs[nId];
}

int CharacterManager::AddItem( bork::Item& item, const std::string& name )
{
    bork::DLog::Out( "CharacterManager", "AddItem", "Adding new Item \"" + name + "\"" );
    bork::DLog::AdjustIndent( 1 );
    bork::DLog::Out( "CharacterManager", "AddItem", "Coordinates: " + bork::IntToString( item.X() ) + ", " + bork::IntToString( item.Y() ) );
    item.m_sId = name;
    item.m_nId = m_lstItems.size();
    m_lstItems.push_back( item );
    bork::DLog::AdjustIndent( -1 );
    bork::DLog::Out( "CharacterManager", "AddItem", "End" );
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
    for ( unsigned int i = 0; i < m_lstItems.size(); i++ )
    {
        bork::Renderer::PushSprite( m_lstItems[i] );
    }
    for ( unsigned int i = 0; i < m_lstNpcs.size(); i++ )
    {
        bork::Renderer::PushSprite( m_lstNpcs[i] );
    }

    bork::Renderer::PushSprite( m_player );
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

void CharacterManager::LoadEntities( const std::string& npcFilePath, const std::string& itemFilePath )
{
    bork::DLog::Out( "CharacterManager", "LoadEntities", "Read files to load in Items and NPCs." );
    bork::DLog::AdjustIndent( 1 );

    int x, y;
    std::string type;
    std::string buffer;

    int npcCount = 0, itemCount = 0;

    // LOAD NPCS
    bork::DLog::Out( "CharacterManager", "LoadEntities", "Loading Entities from \"level-1.npcs\"" );
    std::ifstream npcFile;
    npcFile.open( npcFilePath.c_str() );

    bork::DLog::AdjustIndent( 1 );
    bork::DLog::Out( "CharacterManager", "LoadEntities", "Parse Npcs file..." );
    // TODO: Get rid of duplicated hax tokenizer code
    while ( npcFile >> buffer )
    {
        if ( buffer == "x" )
        {
            npcFile >> x;
        }
        else if ( buffer == "y" )
        {
            npcFile >> y;
        }
        else if ( buffer == "type" )
        {
            npcFile >> type;
        }
        else if ( buffer == "end" )
        {
            Npc newNpc;
            newNpc.Coordinates( bork::Vector2f( x, y ) );
            newNpc.BindImage( bork::GraphicManager::GetGraphic( type ) );
            newNpc.Dimensions( bork::Vector2f( 64, 64 ) );
            newNpc.SheetCoordinates( 0, 0, 64, 64 );
            AddNpc( newNpc, "npc-" + bork::IntToString( npcCount ) );
            npcCount++;
        }
    }

    bork::DLog::AdjustIndent( -1 );

    npcFile.close();

    // LOAD ITEMS
    bork::DLog::Out( "CharacterManager", "LoadEntities", "Loading Entities from \"level-1.items\"" );
    std::ifstream itemFile;
    itemFile.open( itemFilePath.c_str() );

    bork::DLog::AdjustIndent( 1 );
    bork::DLog::Out( "CharacterManager", "LoadEntities", "Parse Items file..." );
    while ( itemFile >> buffer )
    {
        if ( buffer == "x" )
        {
            itemFile >> x;
        }
        else if ( buffer == "y" )
        {
            itemFile >> y;
        }
        else if ( buffer == "type" )
        {
            itemFile >> type;
        }
        else if ( buffer == "end" )
        {
            bork::Item newItem;
            newItem.Coordinates( bork::Vector2f( x, y ) );
            newItem.BindImage( bork::GraphicManager::GetGraphic( type ) );
            newItem.Dimensions( bork::Vector2f( 64, 64 ) );
            newItem.SheetCoordinates( 0, 0, 64, 64 );
            AddItem( newItem, "item-" + bork::IntToString( itemCount ) );
            itemCount++;
        }
    }

    bork::DLog::AdjustIndent( -1 );
    itemFile.close();
    bork::DLog::AdjustIndent( -1 );
    bork::DLog::Out( "CharacterManager", "LoadEntities", "End" );
}


