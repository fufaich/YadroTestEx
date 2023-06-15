#include "TapeExceptions.h"

Exc::EmptyTapeException::EmptyTapeException() : message_("Tape is empty")
{
}

Exc::UnableToOpenFileException::UnableToOpenFileException() : message_("Unaple to open file")
{
}
