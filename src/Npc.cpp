/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "Npc.h"

// TODO: Remove IOSTREAM!!
#include <iostream>

Npc::Npc()
{
    m_speed = 2;
}

void Npc::Update()
{
    MoveTowardGoal();
}

