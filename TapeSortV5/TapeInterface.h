#pragma once
#include <vector>
#include <string>
class TapeInterface
{
public:
	const std::string fileName;
	TapeInterface(const std::string& fileName) : fileName(fileName) {}

	virtual std::vector<int> read(const size_t& count) const = 0;
	virtual std::vector<int> readFull() const = 0;
	virtual int readFirstElement() const = 0;

	virtual void writeElements(const std::vector<int>& elements) = 0;
	virtual void eraseFirstElement() = 0;

	virtual ~TapeInterface() = default;
};

