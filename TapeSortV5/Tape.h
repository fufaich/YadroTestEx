#pragma once
#include "TapeInterface.h"
#include "TapeExceptions.h"
#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>

class Tape :
    public TapeInterface
{
private:
    int delay_read_;//�� ������
    int delay_write_;//�� ������
    int delay_rewind_;//�� ���������
public:

    void readConfiguration();
    Tape(const std::string& nameOfFile) :TapeInterface(nameOfFile) {
        readConfiguration();
    };
    std::vector<int> read(const size_t& count) const override;
    std::vector<int> readFull()const override;
    int readFirstElement() const override;

    void writeElements(const std::vector<int>& elements) override;
    void eraseFirstElement() override;

    ~Tape() override;
};

