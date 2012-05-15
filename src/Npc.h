/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "borka/src/Character.h"

class Npc : public bork::Character
{
    public:
    Npc();
    // TODO: Temp
    void IncrementScore() { m_score++; }
    int GetScore() { return m_score; }
    void DecideWhatToDo( const bork::Entity& goal );
    private:
    int m_score;
    // TODO: Temp
    bool m_horiz;
};
