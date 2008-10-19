#ifndef RAWFONT_H
#define RAWFONT_H

#include <wx/file.h>
class RawFont
{
public:
    RawFont(wxString fontName);
    virtual ~RawFont();
    bool Initialize(wxString fontName);
    bool IsOk() {return m_psfOk; };
    wxString GetFontName() { return m_fontName; };
    unsigned int GetFontLength(){ return m_length;};
    unsigned int GetFontCharSize(){ return m_charsize;};
    unsigned int GetFontHeight(){ return m_height;};
    unsigned int GetFontWidth(){ return m_width;};
    wxString GetFontInformation();
    unsigned char * GetFontPattern(unsigned int charCode,int Count = 1);
protected:
private:
    wxString m_fontName;
    wxFile   m_fontFile;
    bool     m_psfOk;
    unsigned int  m_headersize;
    unsigned int  m_length;
    unsigned int  m_charsize;
    unsigned int  m_height;
    unsigned int  m_width;
};

#endif // RAWFONT_H
