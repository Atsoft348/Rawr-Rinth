/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "GameState.h"
#include "borka/src/LevelManager.h"
#include "borka/src/GraphicManager.h"
#include "borka/src/Application.h"
#include "Character.h"

bool GameState::Init( sf::RenderWindow* window )
{
    m_ptrWindow = window;
}

bool GameState::MainLoop()
{
    int tilesetIdx = bork::GraphicManager::AddGraphic( "temp-tileset", ".png" );
    int rawrIdx = bork::GraphicManager::AddGraphic( "player-rawr", ".png" );

    bork::LevelManager::SetCurrentMap(
        bork::LevelManager::LoadMap( "content/maps/level-1.map", bork::GraphicManager::GetGraphic( tilesetIdx ) ) );

    Character rawr;
    rawr.BindImage( bork::GraphicManager::GetGraphic( rawrIdx ), 1 );
    rawr.SetCoordinates( 128, 128 );
    rawr.SetSheetCoordinates( 0, 0, 64, 64 );

    sf::Shape backgroundColor =
        sf::Shape::Rectangle( 0, 0, 1280, 720, sf::Color( 200, 200, 255, 255 ) );

    while ( m_ptrWindow->IsOpened() )
    {
        sf::Event event;
        // TEMP: Write input handling class
        while ( m_ptrWindow->GetEvent( event ) )
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
        m_screenOffsetX = (rawr.X() + (rawr.W()/2) - (bork::Application::ScreenWidth()/2) );
        m_screenOffsetY = (rawr.Y() + (rawr.H()/2) - (bork::Application::ScreenHeight()/2) );

        m_ptrWindow->Draw( backgroundColor );
        bork::LevelManager::DrawCurrentMap( *m_ptrWindow, rawr.X(), rawr.Y(), m_screenOffsetX, m_screenOffsetY );
        m_ptrWindow->Draw( rawr.Sprite( m_screenOffsetX, m_screenOffsetY ) );
        m_ptrWindow->Display();
    }
}

