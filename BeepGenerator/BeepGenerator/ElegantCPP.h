#pragma once

#include <regex>
#include <string>
#include <thread>
#include <ctime>
#include <cstring>
#include <fstream>
#include <streambuf>
#include <string_view>
#include <iostream>
#include <sstream>

namespace ElegantCPP {

	//type define starts

	using Int16 = short;
	using UInt16 = unsigned short;
	using Int32 = int;
	using UInt32 = unsigned int;
	using Int64 = long long;
	using UInt64 = unsigned long long;

	using Float = float;
	using Double = double;

	using Boolean = bool;
	using Void = void;
	using Size = size_t;

	using Thread = std::thread;
	using Clock = std::clock_t;
	using Time = std::time_t;

#ifdef UNICODE

#define NoSync std::wios::sync_with_stdio(false)

	using IOS = std::wios;

	using Char = wchar_t;
	using String = std::wstring;
	using SStream = std::wstringstream;
	using ISStream = std::wistringstream;
	using OSStream = std::wostringstream;
	using IOStream = std::wiostream;
	using IStream = std::wistream;
	using OStream = std::wostream;
	using FStream = std::wfstream;
	using IFStream = std::wifstream;
	using OFStream = std::wofstream;
	using StringBuf = std::wstringbuf;
	using StringView = std::wstring_view;

	using Regex = std::wregex;

#else

#define NoSync std::ios::sync_with_stdio(false)

	using IOS = std::ios;

	using Char = char;
	using String = std::string;
	using SStream = std::stringstream;
	using ISStream = std::istringstream;
	using OSStream = std::ostringstream;
	using IOStream = std::iostream;
	using IStream = std::istream;
	using OStream = std::ostream;
	using FStream = std::fstream;
	using IFStream = std::ifstream;
	using OFStream = std::ofstream;
	using StringBuf = std::stringbuf;
	using StringView = std::string_view;

	using Regex = std::regex;

#endif //UNICODE

	//type define ends

	//keyword define starts

#define var   auto
#define VThis (*this)
#define cast  static_cast

#define implicit
#define unsafe

#define Abstract      __declspec(novtable)
#define MInterface    __interface
#define CInterface    class

#define ForceInline   __forceinline
#define ASM           __asm
#define Super         __super

#define StdCall       __stdcall
#define CDeclare      __cdecl
#define FastCall      __fastcall

	//keyword define ends

	//declspec define starts

#define DLLImport     __declspec(dllimport)
#define DLLExport     __declspec(dllexport)
#define NoInline      __declspec(noinline)
#define UUID(a)       __declspec(uuid(a))
#define Property(...) __declspec(property(__VA_ARGS__))

	//declspec define ends

	//function define starts

#ifdef UNICODE

#define Console(a)     _wsystem(a)

#define StrCpy(a,b)    wcscpy(a,b)
#define StrNCpy(a,b,c) wcsncpy(a,b,c)
#define StrCat(a,b)    wcscat(a,b)
#define StrNCat(a,b,c) wcsncat(a,b,c)
#define StrXFrm(a,b,c) wcsxfrm(a,b,c)

#define StrLen(a)      wcslen(a)
#define StrCmp(a,b)    wcscmp(a,b)
#define StrNCmp(a,b,c) wcsncmp(a,b,c)
#define StrColl(a,b)   wcscoll(a,b)
#define StrChr(...)    wcschr(__VA_ARGS__)
#define StrRChr(...)   wcsrchr(__VA_ARGS__)
#define StrSpn(a,b)    wcsspn(a,b)
#define StrCSpn(a,b)   wcscspn(a,b)
#define StrPBrk(...)   wcspbrk(__VA_ARGS__)
#define StrStr(...)    wcsstr(__VA_ARGS__)
#define StrTok(...)    wcstok(__VA_ARGS__)

#else

#define Console(a)     system(a)

#define StrCpy(a,b)    strcpy(a,b)
#define StrNCpy(a,b,c) strncpy(a,b,c)
#define StrCat(a,b)    strcat(a,b)
#define StrNCat(a,b,c) strncat(a,b,c)
#define StrXFrm(a,b,c) strxfrm(a,b,c)

#define StrLen(a)      strlen(a)
#define StrCmp(a,b)    strcmp(a,b)
#define StrNCmp(a,b,c) strncmp(a,b,c)
#define StrColl(a,b)   strcoll(a,b)
#define StrChr(...)    strchr(__VA_ARGS__)
#define StrRChr(...)   strrchr(__VA_ARGS__)
#define StrSpn(a,b)    strspn(a,b)
#define StrCSpn(a,b)   strcspn(a,b)
#define StrPBrk(...)   strpbrk(__VA_ARGS__)
#define StrStr(...)    strstr(__VA_ARGS__)
#define StrTok(...)    strtok(__VA_ARGS__)

#endif // UNICODE

	constexpr UInt64 prime = 0x100000001B3ull;
	constexpr UInt64 basis = 0xCBF29CE484222325ull;

	template <typename T>
	constexpr UInt64 constGetHash(const T* str)
	{
		UInt64 ret{ basis };
		while (*str) {
			ret ^= *str;
			ret *= prime;
			str += 1;
		}
		return ret;
	}

	template <typename T>
	UInt64 getHash(const T* str)
	{
		UInt64 ret{ basis };
		while (*str) {
			ret ^= *str;
			ret *= prime;
			str += 1;
		}
		return ret;
	}

#define StrSwitch(str)  switch(ElegantCPP::getHash(str.c_str()))
#define CStrSwitch(str) switch(ElegantCPP::getHash(str))
#define StrCase(str)    ElegantCPP::constGetHash(str)

	template <typename IN, typename OUT>
	OUT SStreamConvert(IN a) {
		SStream ss;
		ss << a;
		OUT b;
		ss >> b;
		return b;
	}

	//function define ends
}
