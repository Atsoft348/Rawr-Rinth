/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "GameState.h"
#include "borka/src/LevelManager.h"
#include "borka/src/GraphicManager.h"
#include "borka/src/Application.h"
#include "borka/src/Renderer.h"
#include "borka/src/InputManager.h"
#include "Character.h"

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

    while ( m_ptrWindow->IsOpened() )
    {
        sf::Event event;
        // TEMP: Write input handling class
        while ( bork::InputManager::GetEvent( event ) )
        {
            if ( event.Type == sf::Event::Closed )
            {
                m_ptrWindow->Close();
            }

            if ( ( event.Type == sf::Event::KeyPressed ) && ( event.Key.Code == sf::Key::Left ) )
            {
                rawr.Move( LEFT );
            }
            else if ( ( event.Type == sf::Event::KeyPressed ) && ( event.Key.Code == sf::Key::Right ) )
            {
                rawr.Move( RIGHT );
            }

            if ( ( event.Type == sf::Event::KeyPressed ) && ( event.Key.Code == sf::Key::Up ) )
            {
                rawr.Move( UP );
            }
            else if ( ( event.Type == sf::Event::KeyPressed ) && ( event.Key.Code == sf::Key::Down ) )
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
    }
}

