/* Borka 2D game framework, May 2012, Rachel J. Morris - www.moosader.com - zlib license */

#ifndef _CHARACTER
#define _CHARACTER

#include <borka/Entity.h>

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

        void AddExp( int amount );

        Vector2f GetGoalCoordinates() { return m_goal.coord; }
        std::string GetGoalName() { return m_goal.name; }
    protected:
        float m_speed;
        int m_score;
        struct {
            Vector2f coord;
            std::string name;
        } m_goal;

        struct Stats
        {
            int hp;
            int attackPower;
            int runningStamina;
            int level;
            int totalExp;
        } m_stats;
};

}

#endif



