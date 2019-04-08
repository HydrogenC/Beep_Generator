#pragma once
#include "ElegantCPP.h"
#include <functional>
#include <iostream>

using namespace ElegantCPP;
using namespace std;

const UInt32 hzTable[] = {
	27, 29, 31,
	33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62,
	65, 69, 73, 78, 82, 87, 92, 98, 104, 110, 117, 123,
	131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247,
	262, 277, 294, 311, 329, 349, 370, 392, 415, 440, 466, 494,
	523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988,
	1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,
	2093, 2217, 2349, 2489, 2637, 2794, 2960, 3135, 3322, 3520, 3729, 3951,
	4186
};

String sourceFile, outFile;
Int16 regModify[] = { 0, 0, 0, 0, 0, 0, 0 };
UInt16 forthNoteLen = 500;

class Command {
private:
	String token;
	function<void(String)> func;

public:
	Command(String token, function<void(String)> func) {
		VThis.token = token;
		VThis.func = func;
	}

	Boolean Execute(String parms) {
		try {
			func(parms);
			return true;
		}
		catch (String e) {
			wcout << e << endl;
			return false;
		}
	}

	String getToken() {
		return token;
	}

	Property(get = getToken) String Token;
};
