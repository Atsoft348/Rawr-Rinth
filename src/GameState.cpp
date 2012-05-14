/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "GameState.h"
#include "borka/src/LevelManager.h"
#include "borka/src/GraphicManager.h"
#include "borka/src/Application.h"
#include "borka/src/Renderer.h"
#include "borka/src/InputManager.h"
#include "Character.h"

// TODO: TEMP!!
#include <iostream>

bool GameState::Init( sf::RenderWindow* window )
{
    bork::Renderer::Init( window );
    bork::InputManager::Init( window );
    m_ptrWindow = window;
    return true;
}

bool GameState::MainLoop()
{
    int tilesetIdx = bork::GraphicManager::AddGraphic( "temp-tileset", ".png" );
    int rawrIdx = bork::GraphicManager::AddGraphic( "player-rawr", ".png" );

    bork::LevelManager::SetCurrentMap(
        bork::LevelManager::LoadMap( "content/maps/allgrass.map", bork::GraphicManager::GetGraphic( tilesetIdx ) ) );

    Character rawr;
    rawr.BindImage( bork::GraphicManager::GetGraphic( rawrIdx ) );
    rawr.SetCoordinates( 128, 350 );
    rawr.SetDimensions( 64, 64 );
    rawr.UpdateSheetCoordinates( 0, 0, 64, 64 );

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
            // TODO: Improve input handling
            // Player movement
            if ( lstActions[i] == bork::PLAYER_RUN )
            {
                rawr.ToggleRun();
            }

            if ( lstActions[i] == bork::PLAYER_LEFT )
            {
                rawr.Move( LEFT );
            }
            else if ( lstActions[i] == bork::PLAYER_RIGHT )
            {
                rawr.Move( RIGHT );
            }
            if ( lstActions[i] == bork::PLAYER_UP )
            {
                rawr.Move( UP );
            }
            else if ( lstActions[i] == bork::PLAYER_DOWN )
            {
                rawr.Move( DOWN );
            }
        }

        // Get draw offset
        // TODO: TEMP: Clean up
        // Not needed in Pickin' Rawr Sticks
        m_screenOffsetX = 0;//(rawr.X() + (rawr.W()/2) - (bork::Application::ScreenWidth()/2) );
        m_screenOffsetY = 16;//(rawr.Y() + (rawr.H()/2) - (bork::Application::ScreenHeight()/2) );
        rawr.UpdateOffset( m_screenOffsetX, m_screenOffsetY );

        // Push items onto renderer queue

        bork::LevelManager::PushDrawables( rawr.X(), rawr.Y(), m_screenOffsetX, m_screenOffsetY );
        bork::Renderer::PushDrawable( rawr );
        bork::Renderer::Draw();

        float framerate = 1.f / clock.GetElapsedTime();
        totalElapsedTime += clock.GetElapsedTime();
        clock.Reset();
    }
    return true;
}

