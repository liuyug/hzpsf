#include "rawfont.h"

#include <sstream>

RawFont::RawFont(string fontName):fontbase(fontName)
{

}
RawFont::~RawFont()
{
    m_fontFile.close();
    //dtor
}
bool RawFont::Initialize(string fontName)
{
    m_psfOk=false;
    m_fontName=fontName;
    m_fontFile.open(m_fontName.c_str(),ios::in | ios::out);
    if(m_fontFile.is_open()) {
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












