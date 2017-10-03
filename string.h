#ifndef _STRING_H
#define _STRING_H

//C RUntime Header Files
#ifndef _TCHAR_INC_
#include<tchar.h>
#endif // !_TCHAR_INC_
#ifndef _STRING_
#include<string>
#endif // !_STRING_


//defines
#ifdef UNICODE
	#define tstring wstring
	#define TOSTRING(value) std::to_wstring(value);
#else
	#define tstring string
	#define TOSTRING(value) std::to_string(value)
#endif // !





#endif // !_STRING_H
