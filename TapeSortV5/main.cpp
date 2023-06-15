#include <iostream>
#include "Tape.h"
#include "TapeExceptions.h"
#include "TapeSort.h"
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Wrong number of arguments. Must be: "
            "<program name> <input_file> <output_file>";
        return -1;
    }

    TapeSort sorter;
        Tape tapeOrigin(argv[1]);

        Tape tapeResult(argv[2]);


        int countElementsInTempTape = 2;
        sorter.sort(tapeOrigin, tapeResult, countElementsInTempTape);
    
    

    return 0;
}