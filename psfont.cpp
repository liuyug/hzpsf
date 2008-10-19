#include "psfont.h"

#include <wx/msgdlg.h>

PSFont::PSFont(wxString fontName)
{
    Initialize(fontName);
}

PSFont::~PSFont()
{
    //dtor
}
bool PSFont::Initialize(wxString fontName)
{
    m_psfOk=false;
    m_fontName=fontName;
    m_psfOk=m_fontFile.Open(m_fontName,wxFile::read_write);
    if(m_psfOk==false) return m_psfOk;

    m_fontFile.Read(&m_magic,4);

    if((m_magic&0xffff)==PSF1_MAGIC) m_version=1;
    else if(m_magic==PSF2_MAGIC) m_version=2;
    else {
        return false;
    }
    m_psfOk=true;
    if(m_version==1){
        m_headersize=4;
		m_flags = (m_magic & 0x020000L) ? 1 : 0;  // PSF1_MODEHASTAB
		m_length = (m_magic & 0x010000L) ? 512 : 256;  // PSF1_MODE512
		m_charsize = ((m_magic >> 24) & 0xFF);
        m_height = m_charsize;
		m_width = 8;
    }
    if(m_version==2){
        int version ;
        m_fontFile.Read(&version,4);
        m_fontFile.Read(&m_headersize,4);
        m_fontFile.Read(&m_flags,4);
        m_fontFile.Read(&m_length,4);
        m_fontFile.Read(&m_charsize,4);
        m_fontFile.Read(&m_height,4);
        m_fontFile.Read(&m_width,4);
    }


    return m_psfOk;
}
wxString PSFont::GetFontInformation()
{
    wxString fontInfo;
    fontInfo<<wxT("Version:")<<m_version<<
        wxT("\nHeader Size:")<<m_headersize<<
        wxT("\nFlags:")<<m_flags<<
        wxT("\nLength:")<<m_length<<
        wxT("\nChar size:")<<m_charsize<<
        wxT("\nHeight:")<<m_height<<
        wxT("\nWidth:")<<m_width;
    return fontInfo;
}

unsigned char * PSFont::GetFontPattern(unsigned int charCode,int Count)
{
    wxFileOffset fPos;
    fPos=m_headersize+charCode*m_charsize;
    unsigned char *fontPattern=new unsigned char[m_charsize*Count];

    m_fontFile.Seek(fPos);
    m_fontFile.Read(fontPattern,m_charsize*Count);

    return fontPattern;
}














