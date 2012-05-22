/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "borka/src/LevelManager.h"
#include "borka/src/GraphicManager.h"
#include "borka/src/Application.h"
#include "borka/src/Renderer.h"
#include "borka/src/InputManager.h"
#include "borka/src/Item.h"
#include "CharacterManager.h"
#include "Npc.h"
#include "Player.h"
#include "GameState.h"

// TODO: TEMP!!
#include <iostream>
#include <sstream>

// TODO: Temp
std::string IntToString( int num )
{
    std::stringstream ss;
    ss << num;
    return ss.str();
}

bool GameState::Init( sf::RenderWindow* window )
{
    bork::Renderer::Init( window );
    bork::InputManager::Init( window );
    m_ptrWindow = window;

    // TODO: TEMP, don't initialize this way.
    int tilesetIdx = bork::GraphicManager::AddGraphic( "temp-tileset", ".png" );
    int rawrIdx = bork::GraphicManager::AddGraphic( "player-rawr", ".png" );
    int enemyIdx = bork::GraphicManager::AddGraphic( "enemy-kitty", ".png" );
    int itemIdx = bork::GraphicManager::AddGraphic( "item-icecream", ".png" );

    bork::LevelManager::SetCurrentMap(
        bork::LevelManager::LoadMap( "content/maps/level-1.map", bork::GraphicManager::GetGraphic( tilesetIdx ) ) );

    // TODO: Load entities via config file
    Player rawr;
    rawr.BindImage( bork::GraphicManager::GetGraphic( rawrIdx ) );
    rawr.SetCoordinates( 128, 256 );
    rawr.SetDimensions( 64, 64 );
    rawr.UpdateSheetCoordinates( 0, 0, 64, 64 );
    CharacterManager::UpdatePlayer( rawr );

    Npc enemy;
    enemy.BindImage( bork::GraphicManager::GetGraphic( enemyIdx ) );
    enemy.SetCoordinates( 256, 256 );
    enemy.SetDimensions( 64, 64 );
    enemy.UpdateSheetCoordinates( 0, 0, 64, 64 );
    CharacterManager::AddNpc( enemy, "enemy" );

    bork::Item item;
    item.BindImage( bork::GraphicManager::GetGraphic( itemIdx ) );
    item.GenerateCoordinates();
    item.SetDimensions( 64, 64 );
    item.UpdateSheetCoordinates( 0, 0, 64, 64 );
    CharacterManager::AddItem( item, "item" );

    CharacterManager::GetNpc( "enemy" ).SetGoal( CharacterManager::GetItem( "item" ) );

    return true;
}

// TODO: TEMP!  THIS IS A MESS, DON'T MAKE YOUR MAIN LIKE THIS!
// I will clean it up, I just want to get a Pickin' Sticks working!
bool GameState::MainLoop()
{
    // TODO: TEMP
    sf::Clock clock;
    float totalElapsedTime = 0;

    while ( m_ptrWindow->IsOpened() )
    {
        // TEMP: Write input handling class
        std::vector<bork::AppEvents> lstActions = bork::InputManager::GetEvents();

        for ( unsigned int i = 0; i < lstActions.size(); i++ )
        {
            if ( lstActions[i] == bork::APPLICATION_CLOSE )
                m_ptrWindow->Close();
            if ( lstActions[i] == bork::DEBUG_NEW_ICECREAM )
                CharacterManager::GetItem( "item" ).GenerateCoordinates();
            // TODO: Improve input handling
            // Player movement
            if ( lstActions[i] == bork::PLAYER_LEFT )
            {
                CharacterManager::GetPlayer().Move( bork::LEFT );
            }
            else if ( lstActions[i] == bork::PLAYER_RIGHT )
            {
                CharacterManager::GetPlayer().Move( bork::RIGHT );
            }
            if ( lstActions[i] == bork::PLAYER_UP )
            {
                CharacterManager::GetPlayer().Move( bork::UP );
            }
            else if ( lstActions[i] == bork::PLAYER_DOWN )
            {
                CharacterManager::GetPlayer().Move( bork::DOWN );
            }
        }

        CharacterManager::Update();

        // HUD Text
        bork::Renderer::PushString( "Player: " + IntToString( CharacterManager::GetPlayer().GetScore() ),
            bork::Vector2f( 0, 450 ) );
        bork::Renderer::PushString( "Enemy: " + IntToString( CharacterManager::GetNpc( "enemy" ).GetScore() ),
            bork::Vector2f( 320, 450 ) );

        // Get draw offset
        // TODO: TEMP: Clean up
        // Not needed in Pickin' Rawr Sticks
        m_screenOffset.x = (CharacterManager::GetPlayer().X() + (CharacterManager::GetPlayer().W()/2) - (bork::Application::ScreenWidth()/2) );
        m_screenOffset.y = (CharacterManager::GetPlayer().Y() + (CharacterManager::GetPlayer().H()/2) - (bork::Application::ScreenHeight()/2) );
        CharacterManager::GetPlayer().UpdateOffset( m_screenOffset );
        CharacterManager::GetNpc( "enemy" ).UpdateOffset( m_screenOffset );
        CharacterManager::GetItem( "item" ).UpdateOffset( m_screenOffset );

        // Push items onto renderer queue
        bork::LevelManager::PushDrawables( bork::Vector2f( bork::Application::ScreenWidth()/2, bork::Application::ScreenHeight()/2 ), m_screenOffset );
        CharacterManager::PushDrawables();
        bork::Renderer::Draw();

        float framerate = 1.f / clock.GetElapsedTime();
        totalElapsedTime += clock.GetElapsedTime();
        clock.Reset();
    }
    return true;
}

