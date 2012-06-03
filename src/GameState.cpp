/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include <borka/InputManager.h>
#include <borka/GraphicManager.h>
#include <borka/LevelManager.h>
#include <borka/Application.h>
#include <borka/DebugLog.h>
#include <borka/Utilities.h>

#include "CharacterManager.h"
#include "TextManager.h"
#include "Npc.h"
#include "Player.h"
#include "GameState.h"
#include "InputHandler.h"

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

    TextManager::LoadFont( "Averia-Regular" );

    bork::DLog::AdjustIndent( -1 );
    bork::DLog::Out( "GameState", "Init", "End" );
    return true;
}

// TODO: TEMP!  THIS IS A MESS, DON'T MAKE YOUR MAIN LIKE THIS!
bool GameState::MainLoop()
{
    bork::DLog::Out( "GameState", "MainLoop", "Begin game loop" );
    bork::DLog::AdjustIndent( 1 );
    // TODO: TEMP
    sf::Clock clock;
    float totalElapsedTime = 0;

    while ( bork::Application::IsOpened() )
    {
        InputHandler::CheckInput();

        // TODO: Right now TextManager Update has to be called before CharacterManager's, because
        // TextManager's Update clears out the temporaries. Remove this "order" dependency
        TextManager::Update();
        CharacterManager::Update();

        // Get draw offset
        // TODO: TEMP: Clean up
        m_screenOffset.x = (CharacterManager::GetPlayer().X() + (CharacterManager::GetPlayer().W()/2) - (bork::Application::ScreenWidth()/2) );
        m_screenOffset.y = (CharacterManager::GetPlayer().Y() + (CharacterManager::GetPlayer().H()/2) - (bork::Application::ScreenHeight()/2) );
        bork::Renderer::UpdateOffset( m_screenOffset );

        // Push items onto renderer queue
        bork::LevelManager::PushDrawables( bork::Vector2f(
            (CharacterManager::GetPlayer().X() + (CharacterManager::GetPlayer().W()/2) ),
            (CharacterManager::GetPlayer().Y() + (CharacterManager::GetPlayer().H()/2) ) ) );
        CharacterManager::PushDrawables();
        TextManager::PushDrawables();

        bork::Renderer::Draw();

        float framerate = 1.f / clock.GetElapsedTime();
        totalElapsedTime += clock.GetElapsedTime();
        clock.Reset();
        bork::DLog::Out( "GameState", "MainLoop", "FrameRate is: " + bork::FloatToString( framerate ) );
    }

    bork::DLog::AdjustIndent( -1 );
    bork::DLog::Out( "GameState", "MainLoop", "Return from game loop with \"true\"" );
    return true;
}

