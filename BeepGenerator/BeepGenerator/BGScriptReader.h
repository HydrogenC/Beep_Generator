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
IFStream fin;
OFStream fout;

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


Command cmdList[] = {
	Command(String(L"el"), [&](String parms) {
		fout << L"\r\n";
	}),
	Command(String(L"pr"), [&](String parms) {
		fout << parms << "\r\n";
		wcout << L"Printed \"" << parms << L"\" to file. " << endl;
	}),
	Command(String(L"//"), [&](String parms) {
		return;
	}),
	Command(String(L"out"), [&](String parms) {
		outFile = parms;
		fout = OFStream(outFile);
		fout << L"# Generated by DBeepGenerator\r\n";
		wcout << L"Out file set to " << parms << ". " << endl;
	}),
		/*
		Command("bpm", function(string parms){
			uint bpm = to!ushort(parms);
			forthNoteLen = 60000 / bpm;
			writeln("BPM set to "~to!(string)(bpm)~". ");
		}),
		Command("sign", function(string parms){
			switch (parms) {
			case "C":
			case "a":
				break;
			case "C#":
			case "a#":
				regModify = [1, 1, 1, 1, 1, 1, 1];
				break;
			case "Db":
			case "bb":
				regModify = [0, -1, -1, 0, -1, -1, -1];
				break;
			case "D":
			case "b":
				regModify = [1, 0, 0, 1, 0, 0, 0];
				break;
			case "Eb":
			case "c":
				regModify = [0, 0, -1, 0, 0, -1, -1];
				break;
			case "E":
			case "c#":
				regModify = [1, 1, 0, 1, 1, 0, 0];
				break;
			case "F":
			case "d":
				regModify = [0, 0, 0, 0, 0, 0, -1];
				break;
			case "F#":
			case "d#":
				regModify = [1, 1, 1, 1, 1, 1, 0];
				break;
			case "G":
			case "e":
				regModify = [0, 0, 0, 1, 0, 0, 0];
				break;
			case "Ab":
			case "f":
				regModify = [0, -1, -1, 0, 0, -1, -1];
				break;
			case "A":
			case "f#":
				regModify = [1, 0, 0, 1, 1, 0, 0];
				break;
			case "Bb":
			case "g":
				regModify = [0, 0, -1, 0, 0, 0, -1];
				break;
			case "B":
			case "g#":
				regModify = [1, 1, 0, 1, 1, 1, 0];
				break;
			case "Cb":
			case "ab":
				regModify = [-1, -1, -1, -1, -1, -1, -1];
				break;
			default:
				break;
			}
			writeln("Sign changed to "~parms~". ");
		}),
		Command("note", function(string parms){
			string[] arguments = parms.split(' ');
			uint timeNote = identifyTime(arguments[0]);
			uint pitchIndex = identifyPitch(arguments[1]);
			std.file.append(outFile, "Beep("~to!(string)(hzTable[pitchIndex])~", "~to!(string)(timeNote)~");\r\n");
			writeln("Identified note: "~parms);
		}),
		Command("br", function(string parms){
			uint timeBr = identifyTime(parms);
			std.file.append(outFile, "Sleep("~to!(string)(timeBr)~");\r\n");
			writeln("Identified break: "~parms);
		})
		*/
};
