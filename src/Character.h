/* Borka 2D game framework, May 2012, Rachel J. Morris - www.moosader.com - zlib license */

#ifndef _CHARACTER
#define _CHARACTER

#include <borka/Entity.h>

enum DIRECTION { UP, DOWN, LEFT, RIGHT };

class Character : public bork::Entity
{
    public:
        Character();
        virtual void Move( DIRECTION dir );
        virtual void Update();
        virtual void SetGoal( const Entity& item );
        virtual void MoveTowardGoal();
        virtual bool IsAttackableCollision( const Entity& object );

        int GetScore() { return m_score; }
        void IncrementScore() { m_score++; }

        void AddExp( int amount );
        int GetHP();
        int GetAtk();
        int GetExp();
        int GetLevel();
        bool GetHit( int opponentAtk );
        bool IsDead() { return m_isDead; }

        bork::Vector2f GetGoalCoordinates() { return m_goal.coord; }
        std::string GetGoalName() { return m_goal.name; }
    protected:
        float m_speed;
        int m_score;
        bool m_isDead;

        struct {
            bork::Vector2f coord;
            std::string name;
        } m_goal;

        struct Stats
        {
            int hp;
            int attackPower;
            int runningStamina;
            int level;
            int totalExp;
            float getHurtCooldown; // When this is > 0, you can't get hurt until it cools back down
        } m_stats;
};

#endif



