/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "borka/src/LevelManager.h"
#include "borka/src/GraphicManager.h"
#include "borka/src/Application.h"
#include "borka/src/Renderer.h"
#include "borka/src/InputManager.h"
#include "borka/src/Item.h"
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
    return true;
}

// TODO: TEMP!  THIS IS A MESS, DON'T MAKE YOUR MAIN LIKE THIS!
// I will clean it up, I just want to get a Pickin' Sticks working!
bool GameState::MainLoop()
{
    // TODO: TEMP, don't initialize this way.
    int tilesetIdx = bork::GraphicManager::AddGraphic( "temp-tileset", ".png" );
    int rawrIdx = bork::GraphicManager::AddGraphic( "player-rawr", ".png" );
    int enemyIdx = bork::GraphicManager::AddGraphic( "enemy-kitty", ".png" );
    int itemIdx = bork::GraphicManager::AddGraphic( "item-icecream", ".png" );

    bork::LevelManager::SetCurrentMap(
        bork::LevelManager::LoadMap( "content/maps/allgrass.map", bork::GraphicManager::GetGraphic( tilesetIdx ) ) );

    Player rawr;
    rawr.BindImage( bork::GraphicManager::GetGraphic( rawrIdx ) );
    rawr.SetCoordinates( bork::Application::ScreenWidth() - 64, bork::Application::ScreenHeight() - 64 );
    rawr.SetDimensions( 64, 64 );
    rawr.UpdateSheetCoordinates( 0, 0, 64, 64 );

    Npc enemy;
    enemy.BindImage( bork::GraphicManager::GetGraphic( enemyIdx ) );
    enemy.SetCoordinates( 0, 0 );
    enemy.SetDimensions( 64, 64 );
    enemy.UpdateSheetCoordinates( 0, 0, 64, 64 );

    bork::Item item;
    item.BindImage( bork::GraphicManager::GetGraphic( itemIdx ) );
    item.GenerateCoordinates();
    item.SetDimensions( 64, 64 );
    item.UpdateSheetCoordinates( 0, 0, 64, 64 );

    sf::Font font;
    if ( !font.LoadFromFile( "content/fonts/Averia-Regular.ttf" ) )
    {
        std::cerr << "Error loading font" << std::endl;
    }

    // TODO: TEMP
    sf::Clock clock;
    float totalElapsedTime = 0;
    sf::String playerScore( "Player: ", font, 24 );
    playerScore.SetPosition( 0, bork::Application::ScreenHeight() - 30 );
    sf::String enemyScore( "Enemy: ", font, 24 );
    enemyScore.SetPosition( bork::Application::ScreenWidth() / 2,
        bork::Application::ScreenHeight() - 30 );

    while ( m_ptrWindow->IsOpened() )
    {
        // TEMP: Write input handling class
        std::vector<bork::AppEvents> lstActions = bork::InputManager::GetEvents();

        for ( unsigned int i = 0; i < lstActions.size(); i++ )
        {
            if ( lstActions[i] == bork::APPLICATION_CLOSE )
                m_ptrWindow->Close();
            // TODO: Improve input handling
            // Player movement
            if ( lstActions[i] == bork::PLAYER_LEFT )
            {
                rawr.Move( bork::LEFT );
            }
            else if ( lstActions[i] == bork::PLAYER_RIGHT )
            {
                rawr.Move( bork::RIGHT );
            }
            if ( lstActions[i] == bork::PLAYER_UP )
            {
                rawr.Move( bork::UP );
            }
            else if ( lstActions[i] == bork::PLAYER_DOWN )
            {
                rawr.Move( bork::DOWN );
            }
        }

        enemy.DecideWhatToDo( item );

        if ( rawr.IsCollision( item ) )
        {
            rawr.IncrementScore();
            item.GenerateCoordinates();
        }
        if ( enemy.IsCollision( item ) )
        {
            enemy.IncrementScore();
            item.GenerateCoordinates();
        }

        playerScore.SetText( "Player: " + IntToString( rawr.GetScore() ) );
        enemyScore.SetText( "Enemy: " + IntToString( enemy.GetScore() ) );

        // Get draw offset
        // TODO: TEMP: Clean up
        // Not needed in Pickin' Rawr Sticks
        m_screenOffsetX = 0;//(rawr.X() + (rawr.W()/2) - (bork::Application::ScreenWidth()/2) );
        m_screenOffsetY = 16;//(rawr.Y() + (rawr.H()/2) - (bork::Application::ScreenHeight()/2) );
        rawr.UpdateOffset( m_screenOffsetX, m_screenOffsetY );

        // Push items onto renderer queue

        bork::LevelManager::PushDrawables( rawr.X(), rawr.Y(), m_screenOffsetX, m_screenOffsetY );
        bork::Renderer::PushDrawable( rawr );
        bork::Renderer::PushDrawable( enemy );
        bork::Renderer::PushDrawable( item );
        bork::Renderer::PushString( playerScore );
        bork::Renderer::PushString( enemyScore );
        bork::Renderer::Draw();

        float framerate = 1.f / clock.GetElapsedTime();
        totalElapsedTime += clock.GetElapsedTime();
        clock.Reset();
    }
    return true;
}

