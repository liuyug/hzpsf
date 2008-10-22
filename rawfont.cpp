#include "rawfont.h"

#include <sstream>
RawFont::RawFont():fontbase()
{

}
RawFont::RawFont(string fontName):fontbase(fontName)
{
    Initialize(fontName);
}
RawFont::~RawFont()
{
    m_fontFile.close();
    //dtor
}
bool RawFont::do_init()
{
    m_fontFile.open(m_fontName.c_str(),ios::in | ios::binary );
    if(!m_fontFile.is_open()) {
        return m_psfOk;
    }
    m_version=0;
    m_flags=0;
    m_psfOk=true;
    m_headersize=0;

    m_charsize = 16;
    m_height = m_charsize;
    m_width = 8;
    m_length = GetFileLength()/m_charsize;
    return m_psfOk;
}

bool RawFont::do_create()
{
    m_fontFile.open(m_fontName.c_str(),ios::out|ios::trunc|ios::binary );
    if(!m_fontFile.is_open()) {
        return m_psfOk;
    }
    m_version=0;
    m_flags=0;
    m_psfOk=true;
    m_headersize=0;

    m_charsize = 16;
    m_height = 16;
    m_width = 8;
    m_length = 256;
    return m_psfOk;
}

bool RawFont::do_putheader()
{
    return true;
}








