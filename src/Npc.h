/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "Character.h"

#ifndef _NPC
#define _NPC

class Npc : public Character
{
    public:
    Npc();
    Npc( int idx, const std::string& szIdx );
    void Update();
};

#endif
