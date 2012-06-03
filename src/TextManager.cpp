/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include <borka/DebugLog.h>

#include "CharacterManager.h"
#include "TextManager.h"

std::vector<bork::DrawableString> TextManager::m_lstPersistentStrings;
std::vector<bork::DrawableString> TextManager::m_lstTemporaryStrings;
bork::Font TextManager::m_font;

void TextManager::AddPersistentText( bork::TextSpecs& specs )
{
    if ( specs.behavior == bork::MOVE_BOUNCY_DOWN )
    {
        specs.expireTime = 40;
    }
    else if ( specs.behavior == bork::MOVE_WAVE_UP )
    {
        specs.expireTime = 50;
    }
    else if ( specs.behavior == bork::MOVE_FLOAT_UP )
    {
        specs.expireTime = 50;
    }

    bork::DrawableString newString( specs, m_font );
    m_lstPersistentStrings.push_back( newString );
}

void TextManager::AddTemporaryText( bork::TextSpecs& specs )
{
    specs.behavior = bork::NO_MOVE;
    bork::DrawableString newString( specs, m_font );
    m_lstTemporaryStrings.push_back( newString );
}

void TextManager::PushDrawables()
{
    for ( unsigned int strIdx = 0; strIdx < m_lstPersistentStrings.size(); strIdx++ )
    {
        m_lstPersistentStrings[strIdx].PushToRenderer();
    }
    for ( unsigned int strIdx = 0; strIdx < m_lstTemporaryStrings.size(); strIdx++ )
    {
        m_lstTemporaryStrings[strIdx].PushToRenderer();
    }
}

void TextManager::Update()
{
    m_lstTemporaryStrings.clear();

    // I'm not a fan of iterators because they're so verbose.
    for ( std::vector<bork::DrawableString>::iterator strIt = m_lstPersistentStrings.begin();
        strIt < m_lstPersistentStrings.end(); ++strIt )
    {
        strIt->Update();
        if ( strIt->Expired() )
        {
            m_lstPersistentStrings.erase( strIt );
        }
    }
}

void TextManager::LoadFont( const std::string& fontname )
{
    std::string fontPath = "content/fonts/" + fontname + ".ttf";
    bork::DLog::Out( "TextManager", "LoadFont", "Loading font \"" + fontPath + "\"" );
    if ( !m_font.LoadFromFile( fontPath ) )
    {
        bork::DLog::Err( "TextManager", "LoadFont", "Error loading \"" + fontPath + "\"" );
    }
}

