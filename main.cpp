#include <iostream>

#include"psfont.h"
#include"rawfont.h"
#include"rawhzfont.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
//    PSFont psf;
//    psf.Initialize("Linux16.psf");
//    cout<<psf.GetFontInformation()<<endl;

    RawFont raw;
    raw.Initialize("asc16.raw");
    RawHzFont hzRaw;
    hzRaw.Initialize("hzk16");
    RawFont myraw;
    myraw.Create("myraw.raw");

    int count=0;
    myraw.PutFontPattern(raw.GetFontPattern(0,130),130);
    count+=128;
    myraw.PutFontPattern(hzRaw.GetFontPattern("我爱北京天安门\
    我爱北京天安门\
    我爱北京天安门\
    我爱北京天安门\
    我爱北京天安门\
    我爱北京天安门\
    我爱北京天安门\
    我爱北京天安门\
    我爱北京天安门\
    ",63),126);
    cout<<"char:";
    for(int i=count;i<count+126;i++)
        printf("%c",i);
    cout<<"||"<<endl;



    return 0;
}
