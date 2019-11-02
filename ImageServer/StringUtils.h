#pragma once
#ifndef _StringUtils_
#define _StringUtils_

#include <string>  
#include <windows.h>  
using namespace std;
//Converting a WChar string to a Ansi string  
std::string WChar2Ansi(LPCWSTR pwszSrc);
inline string ws2s(wstring& inputws) { return WChar2Ansi(inputws.c_str()); }
std::wstring Ansi2WChar(LPCSTR pszSrc, int nLen);
inline std::wstring s2ws(const string& s) { return Ansi2WChar(s.c_str(), s.size()); }

#endif

