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

#include"fontbase.h"
#include<string>
#include<fstream>
using namespace std;

class PSFont:public fontbase
{
public:
    PSFont();
    PSFont(string fontName);
    virtual ~PSFont();
private:
    bool do_init();
    bool do_create();
    bool do_putheader();
protected:
private:

};

#endif // PSFONT_H
