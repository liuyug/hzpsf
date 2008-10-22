#ifndef RAWFONT_H
#define RAWFONT_H

#include "fontbase.h"

#include<string>
#include<fstream>
#include<iostream>
using namespace std;

class RawFont: public fontbase
{
public:
    RawFont();
    RawFont(string fontName);
    virtual ~RawFont();
private:
    bool do_init();
    bool do_create();
    bool do_putheader();
protected:


};


#endif // RAWFONT_H
