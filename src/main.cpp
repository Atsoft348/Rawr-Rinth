/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com, http://code.google.com/p/rawr-rinth/ */

#include "borka/Application.h"
#include "borka/LevelManager.h"
#include "borka/GraphicManager.h"

int main()
{
    bork::Application::Initialize( "Rawr Rinth" );

    int tilesetIdx = bork::GraphicManager::AddGraphic( "temp-tileset", ".png" );
    int rawrIdx = bork::GraphicManager::AddGraphic( "player-rawr", ".png" );

    bork::LevelManager::SetCurrentMap(
        bork::LevelManager::LoadMap( "content/maps/level-1.map", bork::GraphicManager::GetGraphic( tilesetIdx ) ) );

    sf::Sprite rawr;
    sf::IntRect rawrRect;
    rawrRect.Left = 0;
    rawrRect.Top = 0;
    rawrRect.Right = 64;
    rawrRect.Bottom = 64;
    rawr.SetImage( bork::GraphicManager::GetGraphic( rawrIdx ).m_image );
    rawr.SetSubRect( rawrRect );
    rawr.SetX( 128 );
    rawr.SetY( 128 );

    while ( bork::Application::TempIsOpened() )
    {
        bork::Application::TempGetInput();
        bork::LevelManager::DrawCurrentMap( bork::Application::TempRenderWindow() );
        bork::Application::Draw( rawr );
        bork::Application::Display();
    }

    return 0;
}

/*
Copyright (C) 2012 Rachel J. Morris

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Rachel J. Morris RachelJMorris@gmail.com
*/
