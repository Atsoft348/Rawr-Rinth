/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include <borka/Entity.h>
#include <borka/Renderer.h>
#include <borka/DebugLog.h>
#include <borka/GraphicManager.h>
#include <borka/Utilities.h>

#include "CharacterManager.h"
#include "TextManager.h"

std::vector<Npc> CharacterManager::m_lstNpcs;
std::vector<bork::Item> CharacterManager::m_lstItems;
Player CharacterManager::m_player;

void CharacterManager::Init()
{
    // TODO: Could cause problem if goal for an entity is set before that entity's coordinates are set.
    m_player.SetIds( 0, "player" );
    m_player.BindImage( bork::GraphicManager::GetGraphic( "player-rawr" ) );
    m_player.Coordinates( bork::Vector2f( 128, 256 ) );
    m_player.Dimensions( bork::Vector2f( 64, 64 ) );
    m_player.SheetCoordinates( 0, 0, 64, 64 );
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

void CharacterManager::PlayerAttack()
{
    if ( !m_player.IsDead() )
    {
        for ( unsigned int npcIdx = 0; npcIdx < m_lstNpcs.size(); npcIdx++ )
        {
            if ( !m_lstNpcs[npcIdx].IsDead() && m_player.IsAttackableCollision( m_lstNpcs[npcIdx] ) )
            {
                // Attack this enemy
                if ( m_lstNpcs[npcIdx].GetHit( m_player.GetAtk() ) )
                {
                    // Add floating text particle
                    TextManager::AddEnemyDamageText( m_player.GetAtk(), m_lstNpcs[npcIdx].Coordinates() );
                }

                if ( m_lstNpcs[npcIdx].IsDead() )
                {
                    m_player.AddExp( 10 );
                }
            }
        }
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
        m_lstItems[i].PushToRenderer();
    }
    for ( unsigned int i = 0; i < m_lstNpcs.size(); i++ )
    {
        if ( !m_lstNpcs[i].IsDead() )
        {
            m_lstNpcs[i].PushToRenderer();
//            bork::Renderer::PushString( bork::IntToString( m_lstNpcs[i].GetHP() ),
//                bork::Vector2f( m_lstNpcs[i].GetOffsetCoordinates().x + 20, m_lstNpcs[i].GetOffsetCoordinates().y - 16 ),
//                18, bork::Color( 255, 0, 0, 255 ) );
        }
    }

    if ( !m_player.IsDead() )
    {
//        bork::Renderer::PushString( bork::IntToString( m_player.GetHP() ),
//            bork::Vector2f( m_player.GetOffsetCoordinates().x + 20, m_player.GetOffsetCoordinates().y - 16 ),
//            18, bork::Color( 0, 100, 0, 255 ) );
        m_player.PushToRenderer();
    }
}

void CharacterManager::Update()
{
    m_player.Update();

    for ( unsigned int itemIdx = 0; itemIdx < m_lstItems.size(); itemIdx++ )
    {
        if ( m_player.IsCollision( m_lstItems[itemIdx] ) )
        {
            m_player.AddExp( 10 );
            m_lstItems[itemIdx].GenerateCoordinates();
            TextManager::AddItemGrabText( "+10", m_player.Coordinates() );
        }

        for ( unsigned int npcIdx = 0; npcIdx < m_lstNpcs.size(); npcIdx++ )
        {
            if ( m_lstNpcs[npcIdx].IsCollision( m_lstItems[itemIdx] ) )
            {
                m_lstNpcs[npcIdx].IncrementScore();
                m_lstItems[itemIdx].GenerateCoordinates();
            }
        }
    }

    bork::TextSpecs textSpecs;
    // Update characters - for NPC, this will move them toward goal.
    for ( unsigned int npcIdx = 0; npcIdx < m_lstNpcs.size(); npcIdx++ )
    {
        m_lstNpcs[npcIdx].Update();
        // Over-head readouts
        textSpecs.Init(
            bork::IntToString( m_lstNpcs[npcIdx].GetHP() ),
            bork::Vector2f( m_lstNpcs[npcIdx].X() + 26, m_lstNpcs[npcIdx].Y() - 32 ), 16, bork::Color( 255, 0, 0, 255 ), bork::NO_MOVE, true );
        TextManager::AddTemporaryText( textSpecs );

        // Enemy/Player Collision
        if ( !m_lstNpcs[npcIdx].IsDead() && m_lstNpcs[npcIdx].IsAttackableCollision( m_player ) )
        {
            // Attack Player
            if ( m_player.GetHit( m_lstNpcs[npcIdx].GetAtk() ) )
            {
                // Display floaty damage text
                TextManager::AddPlayerDamageText( m_lstNpcs[npcIdx].GetAtk(), m_player.Coordinates() );
            }
        }

        // Update goal
        if ( m_lstNpcs[npcIdx].GetGoalName() == "player" )
        {
            m_lstNpcs[npcIdx].SetGoal( GetPlayer() );
        }
    }

    // Over-head readouts
    textSpecs.Init(
        bork::IntToString( m_player.GetHP() ),
        bork::Vector2f( m_player.X() + 26, m_player.Y() - 32 ), 16, bork::Color( 100, 255, 100, 255 ), bork::NO_MOVE, true );
    TextManager::AddTemporaryText( textSpecs );

    // HUD Data
    textSpecs.Init(
        "Player HP: " + bork::IntToString( m_player.GetHP() ),
        bork::Vector2f( 0, 0 ), 20, bork::Color( 255, 255, 255, 255 ), bork::NO_MOVE, false );
    TextManager::AddTemporaryText( textSpecs );

    textSpecs.Init(
        "Player EXP: " + bork::IntToString( m_player.GetExp() ),
        bork::Vector2f( 0, 20 ), 20, bork::Color( 255, 255, 255, 255 ), bork::NO_MOVE, false );
    TextManager::AddTemporaryText( textSpecs );

    textSpecs.Init(
        "Player Level: " + bork::IntToString( m_player.GetLevel() ),
        bork::Vector2f( 0, 40 ), 20, bork::Color( 255, 255, 255, 255 ), bork::NO_MOVE, false );
    TextManager::AddTemporaryText( textSpecs );
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
            newNpc.SetIds( npcCount, "npc-" + bork::IntToString( npcCount ) );
            newNpc.Coordinates( bork::Vector2f( x, y ) );
            newNpc.BindImage( bork::GraphicManager::GetGraphic( type ) );
            newNpc.Dimensions( bork::Vector2f( 64, 64 ) );
            newNpc.SheetCoordinates( 0, 0, 64, 64 );
            newNpc.SetGoal( GetPlayer() );
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

bool CharacterManager::CheckCollision( const bork::Vector2f& coordinates, const bork::Vector2f& dimensions, const std::string& szId )
{
    // Check against player
    if ( szId != m_player.m_sId )
    {
        if ( m_player.IsCollision( coordinates, dimensions ) )
        {
            return true;
        }
    }

    // Check against npcs
    for ( int npcIdx = 0; npcIdx < m_lstNpcs.size(); npcIdx++ )
    {
        if ( szId != m_lstNpcs[npcIdx].m_sId )
        {
            if ( m_lstNpcs[npcIdx].IsCollision( coordinates, dimensions ) )
            {
                return true;
            }
        }
    }
    return false;
}

