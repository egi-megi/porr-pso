#include "../include/InputParser.h"

void InputParser::parse(Options *options, int argc, char* argv[])
{
    if(argc == 3)
    {
        sscanf(argv[1], "%d", &options->amountOfParticles);
        sscanf(argv[2], "%d", &options->dimension);
    }
}