#ifndef SOUNDS_H
#define SOUNDS_H
#include <string>

namespace sounds_h {

	int get_note_id(std::string);

	int get_length(int, int);

	int identify_and_get_sum(int, std::string);
}

#endif //SOUNDS_H