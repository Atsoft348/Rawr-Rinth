/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "Character.h"

#ifndef _NPC
#define _NPC

class Npc : public bork::Character
{
    public:
    Npc();
    void Update();
};

#endif
