/* Rawr Rinth v1, May 2012, Rachel J. Morris - www.moosader.com */

#ifndef _TEXTMANAGER
#define _TEXTMANAGER

#include <borka/DrawableString.h>
#include <borka/Font.h>

#include <vector>
#include <string>

class TextManager
{
    public:
    static void AddPersistentText( bork::TextSpecs& specs );
    static void AddTemporaryText( bork::TextSpecs& specs ); // Push directly to renderer

    static void PushDrawables();
    static void Update();

    static void LoadFont( const std::string& fontname );

    protected:
    static std::vector<bork::DrawableString> m_lstPersistentStrings;
    static std::vector<bork::DrawableString> m_lstTemporaryStrings;
    static bork::Font m_font;
};

#endif


