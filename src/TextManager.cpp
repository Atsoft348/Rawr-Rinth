/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include <borka/DebugLog.h>

#include "TextManager.h"

std::vector<bork::DrawableString> TextManager::m_lstPersistentStrings;
std::vector<bork::DrawableString> TextManager::m_lstTemporaryStrings;
bork::Font TextManager::m_font;

void TextManager::AddPersistentText( bork::TextSpecs& specs )
{
    bork::DLog::Out( "TextManager", "AddPersistentText", "Add new text \"" + specs.text + "\"" );
    bork::DrawableString newString( specs, m_font );
    m_lstPersistentStrings.push_back( newString );
}

void TextManager::AddTemporaryText( bork::TextSpecs& specs )
{
    bork::DLog::Out( "TextManager", "AddTemporaryText", "Add new text \"" + specs.text + "\"" );
    specs.behavior = bork::NO_MOVE;
    specs.offsetAffected = false;
    bork::DrawableString newString( specs, m_font );
    m_lstTemporaryStrings.push_back( newString );
}

void TextManager::PushDrawables()
{
    for ( unsigned int strIdx = 0; strIdx < m_lstPersistentStrings.size(); strIdx++ )
    {
        bork::DLog::Out( "TextManager", "PushDrawables", "Push persistent text " + bork::IntToString( strIdx ) );
        m_lstPersistentStrings[strIdx].PushToRenderer();
    }
    for ( unsigned int strIdx = 0; strIdx < m_lstTemporaryStrings.size(); strIdx++ )
    {
        bork::DLog::Out( "TextManager", "PushDrawables", "Push temporary text " + bork::IntToString( strIdx ) );
        m_lstTemporaryStrings[strIdx].PushToRenderer();
    }
}

void TextManager::Update()
{
    m_lstTemporaryStrings.clear();
    for ( unsigned int strIdx = 0; strIdx < m_lstPersistentStrings.size(); strIdx++ )
    {
        m_lstPersistentStrings[strIdx].Update();
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

