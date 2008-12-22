#include<iostream>
#include<cstdio>
#include<string>


#include<boost/program_options.hpp>

#include"psfont.h"
#include"rawfont.h"
#include"rawhzfont.h"
#include"version.h"

using namespace std;
namespace po = boost::program_options;

int Translate(string & line,string &asciiTable,string & hzTable,unsigned char baseChar)
{
    string hz;
    string::size_type pos;
    if(line.length()<2) return 0;

    for(unsigned int i=0;i<line.length()-1;i++){
        if((line[i]&0xff)>=0xA1&&(line[i+1]&0xff)>=0xA1){  // chinese
            pos=0;
            hz=line.substr(i,2);
            while(1){
                pos=hzTable.find(hz,pos);
                if(pos==string::npos) { // add new chinese
                    pos=hzTable.length();
                    hzTable+=hz;
                    break;
                }
                if(pos%2==1) {
                    pos++;
                    continue;      // find
                }
                break;
            }
            if(pos>128) continue;  // 汉字字数过多，继续执行，统计汉字总个数
            line.replace(i,2,asciiTable.substr(baseChar+pos,2));
            i++;
        }
    }
    return 0;
}
int main(int argc,char *argv[])
{

    string englishFont,chineseFont,consoleFont;
    string inputFile,outputFile;
    string prog_info="HZPSF "+string(AutoVersion::FULLVERSION_STRING)+"\nCopyright (c) 2008 Liu Yugang "+ \
    string(AutoVersion::YEAR)+"-"+string(AutoVersion::MONTH)+"-"+string(AutoVersion::DATE)+"\n\n";
    cout<<prog_info;
    try{
        string usage="Usage: HZPSF <options>\n";

        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "this message")
            ("english-font,e", po::value<string>(), "input english font(f16 or psf)")
            ("chinese-font,z", po::value<string>(), "input chinese font(chinese dot font)")
            ("console-font,c", po::value<string>(), "output console font(f16 or psf)")
            ("input-file,i", po::value<string>(), "input config file")
            ("output-file,o", po::value<string>(), "output config file")
            ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            cerr <<usage;
            cerr << desc << "\n";
            return 1;
        }

        if (vm.count("english-font")) englishFont=vm["english-font"].as<string>(); //cout << "english-font:"<<vm["english-font"].as<string>() << endl;
        if (vm.count("chinese-font")) chineseFont=vm["chinese-font"].as<string>(); //cout << "chinese-font:"<<vm["chinese-font"].as<string>() << endl;
        if (vm.count("console-font")) consoleFont=vm["console-font"].as<string>();
        if (vm.count("input-file")) inputFile=vm["input-file"].as<string>(); //cout << "input-file:"<<vm["input-file"].as<string>() << endl;
        if (vm.count("output-file")) outputFile=vm["output-file"].as<string>(); //cout << "output-file:"<<vm["output-file"].as<string>() << endl;
        // debug:
//        englishFont="fonts\\greek.f16";
//        chineseFont="fonts\\hzk16";
//        consoleFont="hzfont.psf";
//        inputFile="slax_zh.cfg";
//        outputFile="slax.cfg";
        //
        if (englishFont.empty()||chineseFont.empty()||inputFile.empty()||outputFile.empty()||consoleFont.empty()){
            cerr <<usage<<endl;
            cerr << desc << "\n";
            return 1;
        }
    }catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }catch(...) {
        cerr << "Exception of unknown type!\n";
        return 1;
    }
    string ascii;
    for(int k=0;k<256;k++)
        ascii+=k;
    // translate config file
    ifstream inFile(inputFile.c_str(),ios::in);
    if(!inFile.is_open()) {
        cerr<<"Can't open input file:"<<inputFile<<endl;
        return 1;
    }
    ofstream outFile(outputFile.c_str(),ios::out|ios::trunc);
    if(!outFile.is_open()) {
        cerr<<"Can't open output file:"<<outputFile<<endl;
        return 1;
    }
    string line;
    string hzTable;
    unsigned char baseChar=128;
    int linenum=0;
//    debug:
//    line="MENU LABEL Memtest 内存测试";
//    cout<<"Line "<<linenum<<":"<<line<<endl;
//    Translate(line,ascii,hzTable,baseChar);
//    cout<<"Line "<<linenum<<":"<<line<<endl;
//    return 1;

    while(getline(inFile,line)){
        linenum++;
        cout<<"Line "<<linenum<<":"<<line<<endl;
        Translate(line,ascii,hzTable,baseChar);
        outFile<<line<<endl;
        cout<<"Line "<<linenum<<":"<<line<<endl;
    }

    cout<<"Chinese table:"<<hzTable<<endl;
    cout<<"Chinese words number:"<<hzTable.length()/2<<endl;
    if(hzTable.length()>128){
        cerr<<"Chinese words are more than 64 ! Quit..."<<endl;
        return 1;
    }
    inFile.close();
    outFile.close();
    // make console font

    fontbase * enFont,*conFont;
    string ext=englishFont.substr(englishFont.rfind(".")+1);
    if(ext=="psf"||ext=="PSF"){
        enFont=new PSFont();
    }else
    if(ext=="f16"||ext=="F16"){
        enFont=new RawFont();
    }else {
        enFont=new RawFont();
        cout<<englishFont<<":Use default type f16!"<<endl;
        //cerr<<englishFont<<":Unknown font type!"<<endl;
        //return 1;
    }
    ext=consoleFont.substr(consoleFont.rfind(".")+1);
    if(ext=="psf"||ext=="PSF"){
        conFont=new PSFont();
    }else
    if(ext=="f16"||ext=="F16"){
        conFont=new RawFont();
    }else {
        conFont=new RawFont();
        cout<<consoleFont<<":Use default type f16!"<<endl;
        //cerr<<consoleFont<<":Unknown font type!"<<endl;
        //return 1;
    }

    enFont->Initialize(englishFont);
    RawHzFont zhFont;
    zhFont.Initialize(chineseFont);

    conFont->Create(consoleFont);
    conFont->PutHeader();
    conFont->PutFontPattern(enFont->GetFontPattern(0,128),128);
    conFont->PutFontPattern(zhFont.GetFontPattern(hzTable.c_str(),hzTable.length()/2,true),hzTable.length());
    int k=256-baseChar-hzTable.length();
    conFont->PutFontPattern(enFont->GetFontPattern(baseChar+hzTable.length(),k),k);
    cout<<"Output config file:"<<outputFile<<endl;
    cout<<"Output console font:"<<consoleFont<<endl;
    cout<<"Make console font and config file successfully!"<<endl;
    delete conFont;
    delete enFont;
    return 0;
}
