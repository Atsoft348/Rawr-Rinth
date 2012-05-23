/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#ifndef _GAMESTATE
#define _GAMESTATE

// Borka headers
#include <borka/State.h>
#include <borka/Vector2f.h>
#include <borka/Window.h>

class GameState : public bork::State
{
    public:
    bool Init( bork::Window* window );
    bool MainLoop();
    private:
    bork::Vector2f m_screenOffset;
};

#endif


