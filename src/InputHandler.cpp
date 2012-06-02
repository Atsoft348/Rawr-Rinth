/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include <borka/InputManager.h>
#include <borka/Application.h>

#include "InputHandler.h"
#include "CharacterManager.h"

void InputHandler::CheckInput()
{
    std::vector<bork::AppEvents> lstActions = bork::InputManager::GetEvents();

    for ( unsigned int i = 0; i < lstActions.size(); i++ )
    {
        // System Commands ************************************************
        if ( lstActions[i] == bork::APPLICATION_CLOSE )
            bork::Application::Close();
        // Player movement ************************************************
        if ( lstActions[i] == bork::PLAYER_LEFT )
        {
            CharacterManager::GetPlayer().Move( LEFT );
        }
        else if ( lstActions[i] == bork::PLAYER_RIGHT )
        {
            CharacterManager::GetPlayer().Move( RIGHT );
        }
        if ( lstActions[i] == bork::PLAYER_UP )
        {
            CharacterManager::GetPlayer().Move( UP );
        }
        else if ( lstActions[i] == bork::PLAYER_DOWN )
        {
            CharacterManager::GetPlayer().Move( DOWN );
        }
        if ( lstActions[i] == bork::PLAYER_ATTACK )
        {
            CharacterManager::PlayerAttack();
        }
    }
}
