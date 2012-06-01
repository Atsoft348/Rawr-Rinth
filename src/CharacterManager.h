/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#ifndef _CHARACTERMANAGER
#define _CHARACTERMANAGER

#include <borka/Item.h>

#include "Npc.h"
#include "Player.h"

#include <vector>
#include <string>

// TODO: Add common "Manager" template class.
// TODO: Handle Characters vs. bork::Items vs. etc. better.
class CharacterManager
{
    public:
    static void Init();
    static Npc& GetNpc( const std::string& sId );
    static Npc& GetNpc( int nId );
    static int AddNpc( Npc& character, const std::string& name );

    static Player& GetPlayer() { return m_player; }
    static void UpdatePlayer( Player player ) { m_player = player; }
    static void PlayerAttack();

    static bork::Item& GetItem( const std::string& sId );
    static bork::Item& GetItem( int nId );
    static int AddItem( bork::Item& item, const std::string& name );

    static void PushDrawables();
    static void Update();
    static void LoadEntities( const std::string& npcFilePath, const std::string& itemFilePath );
    static void UpdateEntityOffsets( const bork::Vector2f& offset );

    protected:
    static Player m_player;
    static std::vector<Npc> m_lstNpcs;
    static std::vector<bork::Item> m_lstItems;
};

#endif

