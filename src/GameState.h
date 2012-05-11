/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#ifndef _GAMESTATE
#define _GAMESTATE

#include "borka/src/State.h"

class GameState : public bork::State
{
    public:
    bool Init( sf::RenderWindow* window );
    bool MainLoop();
    private:
    int m_screenOffsetX, m_screenOffsetY;
};

#endif


