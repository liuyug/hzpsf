#ifndef RAWFONT_H
#define RAWFONT_H

#include"fontbase.h"
#include<string>
#include<fstream>
using namespace std;


class RawFont:public fontbase
{
public:
    RawFont(string fontName);
    virtual ~RawFont();
    bool Initialize(string fontName);

protected:
private:

};

#endif // RAWFONT_H
