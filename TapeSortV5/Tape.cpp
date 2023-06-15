#include "Tape.h"

void Tape::readConfiguration()
{
	std::ifstream configFile("Config.txt");
	if (configFile.is_open()) {
		std::string key;
		int value;
		while (configFile >> key >> value) {
			if (key == "delay_read") {
				delay_read_ = value;
			}
			else if (key == "delay_write") {
				delay_write_ = value;
			}
			else if (key == "delay_rewind") {
				delay_rewind_ = value;
			}
		}
		configFile.close();
	}
	else {
		throw;
	}
}

std::vector<int> Tape::read(const size_t& count) const
{
	std::ifstream inputFile(fileName);
	if (inputFile.is_open()) {
		std::vector<int> elements;
		std::string elementsSTR;
		size_t currCountElements = 0;
		while (currCountElements < count) {
			char c = static_cast<char>(inputFile.get());

			if (inputFile.eof()) {
				break;
			}

			if (c == ' ') {
				++currCountElements;
				elements.push_back(std::stoi(elementsSTR));
				elementsSTR.clear();
				continue;
			}
			elementsSTR += c;
			Sleep(delay_rewind_);
		}
		if (inputFile.eof() && !elementsSTR.empty()) {
			++currCountElements;
			elements.push_back(std::stoi(elementsSTR));
		}
		inputFile.close();

		if (elements.empty()) {
			throw Exc::EmptyTapeException();
		}
		return elements;
	}
	throw Exc::UnableToOpenFileException();
}

std::vector<int> Tape::readFull()const {
	try {
		return read(INT64_MAX);
	}
	catch (const std::exception&) {
		throw;
	}
}

int Tape::readFirstElement() const
{
	try {
		std::vector<int> elements = read(1);
		return elements[0];
	}
	catch (const std::exception&) {
		throw;
	}
}


void Tape::writeElements(const std::vector<int>& elements) {
	std::ofstream outputFile(fileName);
	if (outputFile.is_open()) {
		if (elements.empty()) {
			throw Exc::EmptyTapeException();
		}
		for (int i = 0; i < elements.size(); i++)
		{
			Sleep(delay_write_);
			outputFile << elements[i] << ' ';
		}
		outputFile.close();
	}
	else {
		throw Exc::UnableToOpenFileException();
	}
}

void Tape::eraseFirstElement()
{
	try
	{
		Sleep(delay_write_);
		std::vector<int> elements = readFull();
		elements.erase(elements.begin());
		writeElements(elements);
	}
	catch (const std::exception&)
	{
		throw;
	}
}

Tape::~Tape() = default;

