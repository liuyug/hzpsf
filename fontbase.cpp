#include "fontbase.h"
#include <sstream>

fontbase::fontbase(string fontName)
{
    Initialize(fontName);
}

fontbase::~fontbase()
{
    m_fontFile.close();
}
bool fontbase::Initialize(string fontName)
{
    m_psfOk=false;
    m_fontName=fontName;
    return m_psfOk;
}
string fontbase::GetFontInformation()
{
    ostringstream fontInfo;
    fontInfo<<("Version:")<<m_version<<
        ("\nHeader Size:")<<m_headersize<<
        ("\nFlags:")<<m_flags<<
        ("\nLength:")<<m_length<<
        ("\nChar size:")<<m_charsize<<
        ("\nHeight:")<<m_height<<
        ("\nWidth:")<<m_width;
    return fontInfo.str();
}

long long fontbase::GetFileLength()
{
    ios::pos_type pos1,pos2;
    pos1=m_fontFile.tellg();
    m_fontFile.seekg(0,ios::end);
    pos2=m_fontFile.tellg();
    m_fontFile.seekg(pos1);
    return pos2;
}
unsigned char * fontbase::GetFontPattern(unsigned int charCode,int Count)
{
    ios::pos_type pos;
    pos=m_headersize+charCode*m_charsize;
    unsigned char *fontPattern=new unsigned char[m_charsize*Count];

    m_fontFile.seekg(pos);
    m_fontFile.read((char*)fontPattern,m_charsize*Count);

    return fontPattern;
}
