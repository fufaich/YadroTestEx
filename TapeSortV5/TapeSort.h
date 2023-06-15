#pragma once
#include "Tape.h"
#include <algorithm>
#include <unordered_map>
class TapeSort
{
public:
	void sort(Tape& input, Tape& output, int countInTape);

private:
	int separateTape(Tape& input, int countInTape);
	void sortTmpTapes(Tape& input, int countTapes);
	void splitTmpTapes(Tape& input, Tape& output, int countTapes);
};

