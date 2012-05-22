/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#ifndef _GAMESTATE
#define _GAMESTATE

#include "borka/src/State.h"
#include "borka/src/Vector2f.h"
#include "borka/src/Window.h"

class GameState : public bork::State
{
    public:
    bool Init( bork::Window* window );
    bool MainLoop();
    private:
    bork::Vector2f m_screenOffset;
    bork::Window* m_ptrWindow;
};

#endif


