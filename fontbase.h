#ifndef FONTBASE_H
#define FONTBASE_H

#include<string>
#include<fstream>
using namespace std;
class fontbase
{
public:
    fontbase(string fontName);
    virtual ~fontbase();
    virtual bool Initialize(string fontName);
    bool IsOk() {return m_psfOk; };
    string GetFontName() { return m_fontName; };
    unsigned int GetFontLength(){ return m_length;};
    unsigned int GetFontCharSize(){ return m_charsize;};
    unsigned int GetFontHeight(){ return m_height;};
    unsigned int GetFontWidth(){ return m_width;};

    virtual string GetFontInformation();
    unsigned char * GetFontPattern(unsigned int charCode,int Count = 1);
    long long GetFileLength();
protected:
    string  m_fontName;
    fstream m_fontFile;
    bool    m_psfOk;
    unsigned int  m_magic;
    unsigned int  m_version;
    unsigned int  m_headersize;
    unsigned int  m_flags;
    unsigned int  m_length;
    unsigned int  m_charsize;
    unsigned int  m_height;
    unsigned int  m_width;
};

#endif // FONTBASE_H
