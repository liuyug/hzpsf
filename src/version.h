#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "22";
	static const char MONTH[] = "12";
	static const char YEAR[] = "2008";
	static const double UBUNTU_VERSION_STYLE = 8.12;
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 0;
	static const long BUILD = 2;
	static const long REVISION = 100;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 9;
	#define RC_FILEVERSION 1,0,2,100
	#define RC_FILEVERSION_STRING "1, 0, 2, 100\0"
	static const char FULLVERSION_STRING[] = "1.0.2.100";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 0;
	

}
#endif //VERSION_H
