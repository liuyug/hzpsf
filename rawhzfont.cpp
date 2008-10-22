#include "rawhzfont.h"
#include <sstream>

RawHzFont::RawHzFont()
{
    m_psfOk=false;
}
RawHzFont::RawHzFont(string fontName)
{
    m_fontName=fontName;
}
RawHzFont::~RawHzFont()
{
    m_fontFile.close();
}
bool RawHzFont::do_init()
{
    m_fontFile.open(m_fontName.c_str(),ios::in|ios::binary);
    if(!m_fontFile.is_open()) {
        return m_psfOk;
    }
    m_version=0;
    m_flags=0;
    m_psfOk=true;
    m_headersize=0;

    m_charsize = 32;
    m_height = 16;
    m_width = 16;
    m_length = GetFileLength()/m_charsize;
    return m_psfOk;

}

bool RawHzFont::do_create()
{
    m_fontFile.open(m_fontName.c_str(),ios::out|ios::trunc|ios::binary);
    if(!m_fontFile.is_open()) {
        return m_psfOk;
    }
    m_version=0;
    m_flags=0;
    m_psfOk=true;
    m_headersize=0;

    m_charsize = 32;
    m_height = 16;
    m_width = 16;
    m_length = GetFileLength()/m_charsize;
    return m_psfOk;
}

bool RawHzFont::do_putheader()
{
    return true;
}



