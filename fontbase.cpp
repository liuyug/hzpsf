#include "fontbase.h"
#include <sstream>
#include <iostream>

fontbase::fontbase()
{
    m_psfOk=false;
}
fontbase::fontbase(string fontName)
{
    m_fontName=fontName;
    //Initialize(fontName);
}

fontbase::~fontbase()
{
    m_fontFile.close();
    if(m_fontPattern!=NULL) delete m_fontPattern;
}
bool fontbase::Initialize(string fontName)
{
    m_fontPattern=NULL;
    m_psfOk=false;
    m_version=0;
    m_headersize=0;
    m_flags = 0;
    m_length = 0;
    m_charsize = 0;
    m_height = 0;
    m_width = 0;
    m_fontName=fontName;
    return do_init();
}
bool fontbase::Create(string fontName)
{
    m_fontPattern=NULL;
    m_psfOk=false;
    m_version=0;
    m_headersize=0;
    m_flags = 0;
    m_length = 0;
    m_charsize = 0;
    m_height = 0;
    m_width = 0;
    m_fontName=fontName;
    return do_create();
}
string fontbase::GetFontInformation()
{
    ostringstream fontInfo;
    if(m_psfOk==false) return string("Invalid font file:")+m_fontName;
    fontInfo<<"Font:"<<m_fontName<<
        ("\nVersion:")<<m_version<<
        ("\nHeader Size:")<<m_headersize<<
        ("\nFlags:")<<m_flags<<
        ("\nLength:")<<m_length<<
        ("\nChar size:")<<m_charsize<<
        ("\nHeight:")<<m_height<<
        ("\nWidth:")<<m_width;
    return fontInfo.str();
}
bool   fontbase::PutHeaderInformation()
{
    return do_putheader();
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
unsigned char * fontbase::GetFontPattern(int charCode,int Count)
{
    ios::pos_type pos;
    pos=m_headersize+charCode*m_charsize;
    if(m_fontPattern!=NULL) delete m_fontPattern;
    m_fontPattern=new unsigned char[m_charsize*Count];
    m_fontFile.seekg(pos);
    m_fontFile.read((char*)m_fontPattern,m_charsize*Count);

    return m_fontPattern;
}
unsigned char * fontbase::GetFontPattern(char *hzCode,int Count)
{
    ios::pos_type pos;
    if(m_fontPattern!=NULL) delete m_fontPattern;
    m_fontPattern=new unsigned char[m_charsize*Count];
    unsigned char *m_fontPatterntemp=new unsigned char[m_charsize];

    for(int i=0;i<Count;i++){
        pos=m_headersize+(((hzCode[i*2+0]&0xff)-0xA1)*94+(hzCode[i*2+1]&0xff)-0xA1)*m_charsize;
        m_fontFile.seekg(pos);
        m_fontFile.read((char*)m_fontPatterntemp,m_charsize);
        for(unsigned int j=0,k=0;j<m_charsize;j+=2,k++){
            *(m_fontPattern+i*m_charsize+k)=*(m_fontPatterntemp+j);
            *(m_fontPattern+i*m_charsize+16+k)=*(m_fontPatterntemp+j+1);
        }
    }
    delete m_fontPatterntemp;
    return m_fontPattern;
}
bool fontbase::SkipChar(int skip)
{
    m_fontFile.seekg(skip*m_charsize,ios::cur);
}

bool fontbase::PutFontPattern(unsigned char *charPattern,int Count)
{
    m_fontFile.write((char*)charPattern,m_charsize*Count);
    return true;
}





