#ifndef FONTBASE_H
#define FONTBASE_H

#include<string>
#include<fstream>

using namespace std;



class fontbase
{
public:
    fontbase();
    fontbase(string fontName);
    virtual ~fontbase();
    bool Initialize(string fontName);
    bool Create(string fontName);

    bool IsOk() {return m_psfOk; };
    string GetFontName() { return m_fontName; };
    unsigned int GetFontLength(){ return m_length;};
    unsigned int GetFontCharSize(){ return m_charsize;};
    unsigned int GetFontHeight(){ return m_height;};
    unsigned int GetFontWidth(){ return m_width;};

    virtual string GetFontInformation();
    virtual bool   PutHeaderInformation();
    virtual unsigned char * GetFontPattern(int charCode,int Count = 1);
    virtual unsigned char * GetFontPattern(char *hzCode,int Count = 1);
    bool            PutFontPattern(unsigned char *charPattern,int Count = 1);
    bool            SkipChar(int skip);
    long long GetFileLength();
private:
    virtual bool do_init() = 0;
    virtual bool do_create() = 0;
    virtual bool do_putheader() = 0;
protected:
    unsigned char * m_fontPattern;
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
