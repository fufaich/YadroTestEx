#include "TapeSort.h"

void TapeSort::sort(Tape& input, Tape& output, int countInTape)
{
	int n = separateTape(input, countInTape);
	sortTmpTapes(input, n);
	splitTmpTapes(input, output, n);
}

int TapeSort::separateTape(Tape& input, int countInTape)
{
	std::ifstream inputFile(input.fileName);
	if (inputFile.is_open()) {
		int tmpTapesCount = 0;
		std::string numberInString;
		while (!inputFile.eof()) {
			++tmpTapesCount;
			int currentTempTapeSize = 0;
			std::ofstream outputFile(std::to_string(tmpTapesCount) + std::string("TMP") + input.fileName);
			while (currentTempTapeSize < countInTape) {
				char c = static_cast<char>(inputFile.get());

				if (c == ' ' || c == '\n') {
					++currentTempTapeSize;
					outputFile << numberInString << ' ';
					numberInString.clear();
					continue;
				}

				if (inputFile.eof()) {
					++currentTempTapeSize;
					outputFile << numberInString;
					numberInString.clear();
					break;
				}


				numberInString += c;
			}
			outputFile.close();
		}
		inputFile.close();
		return tmpTapesCount;
	}
	return -1;
}

void TapeSort::sortTmpTapes(Tape& input, int countTapes)
{
	try {
		for (int i = 0; i < countTapes; ++i) {
			std::string fileName(std::to_string(i + 1) + std::string("TMP") + input.fileName);
			Tape tmpTape(fileName);

			std::vector<int> elements = tmpTape.readFull();
			if (!elements.empty()) {
				std::sort(elements.begin(), elements.end());

				tmpTape.writeElements(elements);
			}
		}
	}
	catch (const std::exception&) {
		throw;
	}
}


void TapeSort::splitTmpTapes(Tape& input, Tape& output, int countTapes)
{
	using index = int;
	using element = int;

	std::unordered_map<index, element> firstElements;
	std::ofstream outputFile(output.fileName);
	for (int i = 0; i < countTapes; ++i) {
		std::string fileName(std::to_string(i + 1) + std::string("TMP") + input.fileName);
		Tape tmpTape(fileName);
		

		try {
			firstElements.emplace(i, tmpTape.readFirstElement());
		}
		catch (const std::exception&) {
			throw;
		}
	}

	while (true) {
		index indexMin = -1;
		element minFirstElem;
		for (const auto& elem : firstElements) {
			if (indexMin == -1) {
				indexMin = elem.first;
				minFirstElem = elem.second;
			}
			else {
				if (elem.second < minFirstElem) {
					indexMin = elem.first;
					minFirstElem = elem.second;
				}
			}
		}
		if (indexMin == -1) {
			outputFile.close();
			break;
		}

		outputFile << minFirstElem << ' ';

		std::string fileName(std::to_string(indexMin + 1) + std::string("TMP") + input.fileName);
		Tape EraseTape = Tape(fileName);
		
		try {
			EraseTape.eraseFirstElement();
			firstElements[indexMin] = EraseTape.readFirstElement();
		}
		catch (const Exc::EmptyTapeException&) {
			firstElements.erase(indexMin);
		}
		catch (const std::exception&) {
			outputFile.close();
			throw;
		}

	}


}

