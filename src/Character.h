/* Borka 2D game framework, May 2012, Rachel J. Morris - www.moosader.com - zlib license */

#ifndef _CHARACTER
#define _CHARACTER

#include "Entity.h"

namespace bork
{

enum DIRECTION { UP, DOWN, LEFT, RIGHT };

class Character : public bork::Entity
{
    public:
        Character();
        virtual void Move( DIRECTION dir );
        virtual void Update();
        virtual void SetGoal( const Entity& item );
        virtual void MoveTowardGoal();

        int GetScore() { return m_score; }
        void IncrementScore() { m_score++; }
    protected:
        float m_speed;
        int m_score;
        Vector2f m_goalCoord;
};

}

#endif



