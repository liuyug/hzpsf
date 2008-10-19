#ifndef PSFONT_H
#define PSFONT_H

#define PSF1_MAGIC0     0x36
#define PSF1_MAGIC1     0x04
#define PSF1_MAGIC      0x0436L
#define PSF1_MODE512    0x01
#define PSF1_MODEHASTAB 0x02
#define PSF1_MODEHASSEQ 0x04
#define PSF1_MAXMODE    0x05

#define PSF1_SEPARATOR  0xFFFF
#define PSF1_STARTSEQ   0xFFFE

#define PSF2_MAGIC0     0x72
#define PSF2_MAGIC1     0xb5
#define PSF2_MAGIC2     0x4a
#define PSF2_MAGIC3     0x86
#define PSF2_MAGIC      0x864ab572L
/* bits used in flags */
#define PSF2_HAS_UNICODE_TABLE 0x01

/* max version recognized so far */
#define PSF2_MAXVERSION 0

/* UTF8 separators */
#define PSF2_SEPARATOR  0xFF
#define PSF2_STARTSEQ   0xFE

#include <wx/file.h>
class PSFont
{
public:
    PSFont(wxString fontName);
    virtual ~PSFont();
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
    //unsigned char m_magic[4];
    unsigned int  m_magic;
    unsigned int  m_version;
    unsigned int  m_headersize;
    unsigned int  m_flags;
    unsigned int  m_length;
    unsigned int  m_charsize;
    unsigned int  m_height;
    unsigned int  m_width;
};

#endif // PSFONT_H
