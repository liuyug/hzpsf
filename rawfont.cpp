#include "rawfont.h"

RawFont::RawFont(wxString fontName)
{
    Initialize(fontName);
}
RawFont::~RawFont()
{
    //dtor
}
bool RawFont::Initialize(wxString fontName)
{
    m_psfOk=false;
    m_fontName=fontName;
    m_psfOk=m_fontFile.Open(m_fontName,wxFile::read_write);
    if(m_psfOk==false) return m_psfOk;

    m_psfOk=true;
    m_headersize=0;

    m_charsize = 16;
    m_height = m_charsize;
    m_width = 8;
    m_length = m_fontFile.Length()/m_charsize;
    return m_psfOk;
}
wxString RawFont::GetFontInformation()
{
    wxString fontInfo;
    fontInfo<<
        wxT("\nHeader Size:")<<m_headersize<<
        wxT("\nLength:")<<m_length<<
        wxT("\nChar size:")<<m_charsize<<
        wxT("\nHeight:")<<m_height<<
        wxT("\nWidth:")<<m_width;
    return fontInfo;
}

unsigned char * RawFont::GetFontPattern(unsigned int charCode,int Count)
{
    wxFileOffset fPos;
    fPos=m_headersize+charCode*m_charsize;
    unsigned char *fontPattern=new unsigned char[m_charsize*Count];

    m_fontFile.Seek(fPos);
    m_fontFile.Read(fontPattern,m_charsize*Count);

    return fontPattern;
}














