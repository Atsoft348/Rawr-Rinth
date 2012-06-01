/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "Npc.h"

// TODO: Remove IOSTREAM!!
#include <iostream>

Npc::Npc()
{
    m_speed = 0.5;
    m_stats.hp = 10;
}

void Npc::Update()
{
    Character::Update();
    MoveTowardGoal();
}

