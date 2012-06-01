/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include <borka/InputManager.h>
#include <borka/GraphicManager.h>
#include <borka/LevelManager.h>
#include <borka/Application.h>
#include <borka/DebugLog.h>
#include <borka/Utilities.h>

#include "CharacterManager.h"
#include "Npc.h"
#include "Player.h"
#include "GameState.h"

bool GameState::Init( bork::Window* window )
{
    bork::DLog::Out( "GameState", "Init", "Initializing game's Renderer, InputManager, Graphics, Levels, and Entitys." );
    bork::DLog::AdjustIndent( 1 );
    bork::Renderer::Init( window );
    bork::InputManager::Init( window );

    // TODO: TEMP, don't initialize this way.
    bork::DLog::Out( "GameState", "Init", "Load Graphics" );
    int tilesetIdx = bork::GraphicManager::AddGraphic( "drawn-tileset", ".png" );
    bork::GraphicManager::AddGraphic( "player-rawr", ".png" );
    bork::GraphicManager::AddGraphic( "enemy-kitty", ".png" );
    bork::GraphicManager::AddGraphic( "item-icecream", ".png" );

    bork::DLog::Out( "GameState", "Init", "Load Map" );
    bork::LevelManager::SetCurrentMap(
        bork::LevelManager::LoadMap( "content/maps/level-1.map", bork::GraphicManager::GetGraphic( tilesetIdx ) ) );

    CharacterManager::Init();
    bork::DLog::Out( "GameState", "Init", "Load Entities" );
    CharacterManager::LoadEntities( "content/maps/level-1.npcs", "content/maps/level-1.items" );

    bork::DLog::AdjustIndent( -1 );
    bork::DLog::Out( "GameState", "Init", "End" );
    return true;
}

// TODO: TEMP!  THIS IS A MESS, DON'T MAKE YOUR MAIN LIKE THIS!
// I will clean it up, I just want to get a Pickin' Sticks working!
bool GameState::MainLoop()
{
    bork::DLog::Out( "GameState", "MainLoop", "Begin game loop" );
    // TODO: TEMP
    sf::Clock clock;
    float totalElapsedTime = 0;

    while ( bork::Application::IsOpened() )
    {
        // TEMP: Write input handling class
        std::vector<bork::AppEvents> lstActions = bork::InputManager::GetEvents();

        for ( unsigned int i = 0; i < lstActions.size(); i++ )
        {
            if ( lstActions[i] == bork::APPLICATION_CLOSE )
                bork::Application::Close();
            if ( lstActions[i] == bork::DEBUG_NEW_ICECREAM )
                CharacterManager::GetItem( "item" ).GenerateCoordinates();
            // TODO: Improve input handling
            // Player movement
            if ( lstActions[i] == bork::PLAYER_LEFT )
            {
                CharacterManager::GetPlayer().Move( LEFT );
            }
            else if ( lstActions[i] == bork::PLAYER_RIGHT )
            {
                CharacterManager::GetPlayer().Move( RIGHT );
            }
            if ( lstActions[i] == bork::PLAYER_UP )
            {
                CharacterManager::GetPlayer().Move( UP );
            }
            else if ( lstActions[i] == bork::PLAYER_DOWN )
            {
                CharacterManager::GetPlayer().Move( DOWN );
            }
            if ( lstActions[i] == bork::PLAYER_ATTACK )
            {
                CharacterManager::PlayerAttack();
            }
        }

        CharacterManager::Update();

        // TODO: Clean! HUD Text

//        bork::Renderer::PushString( "Player HP: "    + bork::IntToString( CharacterManager::GetPlayer().GetHP() ),
//            bork::Vector2f( 0, 0 ) );
//        bork::Renderer::PushString( "Player ATK: "   + bork::IntToString( CharacterManager::GetPlayer().GetAtk() ),
//            bork::Vector2f( 0, 20 ) );
//        bork::Renderer::PushString( "Player EXP: "   + bork::IntToString( CharacterManager::GetPlayer().GetExp() ),
//            bork::Vector2f( 0, 40 ) );
//        bork::Renderer::PushString( "Player Level: " + bork::IntToString( CharacterManager::GetPlayer().GetLevel() ),
//            bork::Vector2f( 0, 60 ) );

        // Get draw offset
        // TODO: TEMP: Clean up
        // Not needed in Pickin' Rawr Sticks
        m_screenOffset.x = (CharacterManager::GetPlayer().X() + (CharacterManager::GetPlayer().W()/2) - (bork::Application::ScreenWidth()/2) );
        m_screenOffset.y = (CharacterManager::GetPlayer().Y() + (CharacterManager::GetPlayer().H()/2) - (bork::Application::ScreenHeight()/2) );
        bork::Renderer::UpdateOffset( bork::Vector2f( m_screenOffset.x, m_screenOffset.y ) );

        // Push items onto renderer queue
        bork::LevelManager::PushDrawables( bork::Vector2f(
            (CharacterManager::GetPlayer().X() + (CharacterManager::GetPlayer().W()/2) ),
            (CharacterManager::GetPlayer().Y() + (CharacterManager::GetPlayer().H()/2) ) ) );
        CharacterManager::PushDrawables();

        bork::Renderer::Draw();

        float framerate = 1.f / clock.GetElapsedTime();
        totalElapsedTime += clock.GetElapsedTime();
        clock.Reset();
    }

    bork::DLog::Out( "GameState", "MainLoop", "Return from game loop with \"true\"" );
    return true;
}

