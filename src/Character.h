/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#ifndef _CHARACTER
#define _CHARACTER

#include "borka/src/Entity.h"

enum DIRECTION { UP, DOWN, LEFT, RIGHT };

class Character : public bork::Entity
{
    public:
        Character();
        void Move( DIRECTION dir );
        void ToggleRun();
    private:
        bool m_isRunning;
};

#endif



