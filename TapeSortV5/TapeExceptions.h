#pragma once
#include <exception>
#include <string>

namespace Exc {
    class EmptyTapeException : public std::exception {
    private:
        const char* message_;
    public:
        EmptyTapeException();
    };




    class UnableToOpenFileException : public std::exception {
    private:
        const char* message_;
    public:
        UnableToOpenFileException();
    };
}