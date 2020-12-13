#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_INPUTPARSER_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_INPUTPARSER_H

#include "Options.h"

class InputParser {
    public:
        static void parse(Options *options, int argc, char* argv[]);
};

#endif // ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_INPUTPARSER_H