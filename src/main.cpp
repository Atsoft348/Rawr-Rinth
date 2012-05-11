/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "borka/src/Application.h"
#include "GameState.h"
#include "borka/src/StateManager.h"

int main()
{
    bork::Application::Initialize( "Pickin' Rawr Icecream", 640, 480 );

    GameState gameState;
    gameState.Init( &bork::Application::RenderWindow() );
    bork::StateManager::AddState( "Game", &gameState, true );

    gameState.MainLoop();

    return 0;
}

