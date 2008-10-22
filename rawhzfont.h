#ifndef RAWHZFONT_H
#define RAWHZFONT_H

#include "fontbase.h"

#include<string>
#include<fstream>
using namespace std;

class RawHzFont:public fontbase
{
public:
    RawHzFont();
    RawHzFont(string fontName);
    virtual ~RawHzFont();

protected:

private:
    bool do_init() ;
    bool do_create() ;
    bool do_putheader() ;
};

#endif // RAWHZFONT_H
