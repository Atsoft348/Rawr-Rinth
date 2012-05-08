/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "borka/src/Application.h"
#include "GameState.h"
#include "borka/src/StateManager.h"

int main()
{
    bork::Application::Initialize( "Rawr Rinth", 640, 480 );

    GameState gameState;
    gameState.Init( &bork::Application::RenderWindow() );
    bork::StateManager::AddState( "Game", &gameState, true );

    gameState.MainLoop();

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
