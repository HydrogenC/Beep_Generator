#pragma once
#include "ElegantCPP.h"
#include <functional>
#include <iostream>
#include <array>
#include <vector>

using namespace ElegantCPP;
using namespace std;

extern const UInt32 hzTable[];
extern String sourceFile, outFile;
extern array<Int16, 7> regModify;;
extern UInt16 forthNoteLen;
extern IFStream fin;
extern OFStream fout;

vector<String> split(String source, Char seperator);

class Command {
private:
	String token;
	function<void(String)> func;

public:
	Command(String token, function<void(String)> func);

	Boolean Execute(String parms);

	String getToken();

	Property(get = getToken) String Token;
};

extern Command cmdList[];

UInt32 identifyTime(String time);
UInt32 identifyNoteLen(String noteType);
UInt32 identifyPitch(String pitch);