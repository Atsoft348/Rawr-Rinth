/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#include <borka/DebugLog.h>

#include "CharacterManager.h"
#include "TextManager.h"

std::vector<bork::DrawableString> TextManager::m_lstPersistentStrings;
std::vector<bork::DrawableString> TextManager::m_lstTemporaryStrings;
bork::Font TextManager::m_font;

void TextManager::AddPersistentText( bork::TextSpecs& specs )
{
    bork::DLog::Out( "TextManager", "AddPersistentText", "Add text \"" + specs.text + "\"" );
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
    bork::DLog::Out( "TextManager", "Update", "Update Strings; size is: " + bork::IntToString( m_lstPersistentStrings.size() ) );
    bork::DLog::AdjustIndent( 1 );
    for ( std::vector<bork::DrawableString>::iterator strIt = m_lstPersistentStrings.begin();
        strIt < m_lstPersistentStrings.end(); ++strIt )
    {
        bork::DLog::Out( "TextManager", "Update", "Update string \"" + strIt->Text() + "\"" );
        bork::DLog::AdjustIndent( 1 );
        strIt->Update();
        if ( strIt->Expired() )
        {
            bork::DLog::Out( "TextManager", "Update", "Item is flagged for delete" );
            m_lstPersistentStrings.erase( strIt );
        }
        bork::DLog::AdjustIndent( -1 );
    }
    bork::DLog::AdjustIndent( -1 );
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

void TextManager::AddItemGrabText( const std::string& text, bork::Vector2f coords )
{
    bork::Color shadowColor( 0, 0, 0, 255 );
    bork::Behavior behave = bork::MOVE_FLOAT_UP;
    // Shadow
    bork::TextSpecs txtShadow;
    txtShadow.Init( text, bork::Vector2f( coords.x + 26 + 1, coords.y + 1 ), 20, shadowColor, behave, true );
    AddPersistentText( txtShadow );
    txtShadow.Init( text, bork::Vector2f( coords.x + 26 + 1, coords.y - 1 ), 20, shadowColor, behave, true );
    AddPersistentText( txtShadow );
    txtShadow.Init( text, bork::Vector2f( coords.x + 26 - 1, coords.y - 1 ), 20, shadowColor, behave, true );
    AddPersistentText( txtShadow );
    txtShadow.Init( text, bork::Vector2f( coords.x + 26 - 1, coords.y + 1 ), 20, shadowColor, behave, true );
    AddPersistentText( txtShadow );

    // Text
    bork::TextSpecs txtItemGrab( text, bork::Vector2f( coords.x + 26, coords.y ), 20, bork::Color( 255, 255, 0, 255 ), behave, true );
    AddPersistentText( txtItemGrab );
}

void TextManager::AddPlayerDamageText( int amount, bork::Vector2f coords )
{
    bork::Color shadowColor( 0, 0, 0, 255 );
    bork::Behavior behave = bork::MOVE_BOUNCY_DOWN;
    // Shadow
    bork::TextSpecs txtShadow;
    txtShadow.Init( bork::IntToString( amount ), bork::Vector2f( coords.x + 26 + 1, coords.y + 1 ), 25, shadowColor, behave, true );
    AddPersistentText( txtShadow );
    txtShadow.Init( bork::IntToString( amount ), bork::Vector2f( coords.x + 26 + 1, coords.y - 1 ), 25, shadowColor, behave, true );
    AddPersistentText( txtShadow );
    txtShadow.Init( bork::IntToString( amount ), bork::Vector2f( coords.x + 26 - 1, coords.y - 1 ), 25, shadowColor, behave, true );
    AddPersistentText( txtShadow );
    txtShadow.Init( bork::IntToString( amount ), bork::Vector2f( coords.x + 26 - 1, coords.y + 1 ), 25, shadowColor, behave, true );
    AddPersistentText( txtShadow );

    // Text
    bork::TextSpecs txtDamage(
        bork::IntToString( amount ),
        bork::Vector2f( coords.x + 26, coords.y ), 25, bork::Color( 255, 0, 0, 255 ), behave, true );
    AddPersistentText( txtDamage );
}

void TextManager::AddEnemyDamageText( int amount, bork::Vector2f coords )
{
    bork::Color shadowColor( 0, 0, 0, 255 );
    bork::Behavior behave = bork::MOVE_BOUNCY_DOWN;
    // Shadow
    bork::TextSpecs txtShadow;
    txtShadow.Init( bork::IntToString( amount ), bork::Vector2f( coords.x + 26 + 1, coords.y + 1 ), 25, shadowColor, behave, true );
    AddPersistentText( txtShadow );
    txtShadow.Init( bork::IntToString( amount ), bork::Vector2f( coords.x + 26 + 1, coords.y - 1 ), 25, shadowColor, behave, true );
    AddPersistentText( txtShadow );
    txtShadow.Init( bork::IntToString( amount ), bork::Vector2f( coords.x + 26 - 1, coords.y - 1 ), 25, shadowColor, behave, true );
    AddPersistentText( txtShadow );
    txtShadow.Init( bork::IntToString( amount ), bork::Vector2f( coords.x + 26 - 1, coords.y + 1 ), 25, shadowColor, behave, true );
    AddPersistentText( txtShadow );

    // Text
    bork::TextSpecs txtDamage(
        bork::IntToString( amount ),
        bork::Vector2f( coords.x + 26, coords.y ), 25, bork::Color( 0, 255, 0, 255 ), behave, true );
    AddPersistentText( txtDamage );
}
