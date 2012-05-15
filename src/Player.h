/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include "borka/src/Character.h"

class Player : public bork::Character
{
    public:
    Player();
    // TODO: Temp
    void IncrementScore() { m_score++; }
    int GetScore() { return m_score; }
    private:
    int m_score;
};
