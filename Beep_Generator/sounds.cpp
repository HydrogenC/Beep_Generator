#include "sounds.h"
#include "stdafx.h"

namespace sounds_h {
	int get_note_id(std::string f) {
		if (f == "do") {
			return 0;
		}
		else if (f == "do#") {
			return 1;
		}
		else if (f == "re") {
			return 2;
		}
		else if (f == "re#") {
			return 3;
		}
		else if (f == "mi") {
			return 4;
		}
		else if (f == "fa") {
			return 5;
		}
		else if (f == "fa#") {
			return 6;
		}
		else if (f == "so") {
			return 7;
		}
		else if (f == "so#") {
			return 8;
		}
		else if (f == "la") {
			return 9;
		}
		else if (f == "la#") {
			return 10;
		}
		else if (f == "si") {
			return 11;
		}
		else {
			return -1;
		}
	}

	int get_length(int fnote_length, int note) {
		switch (note) {
		case 128:
			return fnote_length / 32;
			break;
		case 64:
			return fnote_length / 16;
			break;
		case 32:
			return fnote_length / 8;
			break;
		case 16:
			return fnote_length / 4;
			break;
		case 8:
			return fnote_length / 2;
			break;
		case 4:
			return fnote_length;
			break;
		case 2:
			return fnote_length * 2;
			break;
		case 1:
			return fnote_length * 4;
			break;
		default:
			return -1;
			break;
		}
	}

	int identify_and_get_sum(int fnote_length, std::string ide) {
		int hyphen_index = 0, sum = 0;
		for (unsigned int i = 1; i<ide.length(); i += 1) {
			if (ide[i] == '-') {
				if (hyphen_index == 0) {
					hyphen_index = 1;
					sum += get_length(fnote_length, atoi(ide.substr(0, i).c_str()));
				}
				else {
					sum += get_length(fnote_length, atoi(ide.substr(hyphen_index + 1, i - hyphen_index - 1).c_str()));
				}
			}
			if (i == (ide.length() - 1) && hyphen_index != 0) {
				sum += get_length(fnote_length, atoi(ide.substr(hyphen_index + 1).c_str()));
			}
		}
		if (hyphen_index == 0) {
			return get_length(fnote_length, atoi(ide.c_str()));
		}
		else {
			return sum;
		}
	}
}