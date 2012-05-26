/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "Character.h"

#ifndef _PLAYER
#define _PLAYER

class Player : public bork::Character
{
    public:
    Player();
    void Update();
};

#endif
