#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <fstream>

#include "Global.h"

typedef std::vector<std::string> TokenList;

namespace CMDparser
{
    /* parse command line args and store in Arguments struct */
    void parse(int, const char**, Arguments&);

    /* return a list of tokens from the command line arguments */
    TokenList getTokens(int, const char**);

    /* parse command line options */
    void parseOptions(TokenList&, Arguments&);

    /* parse libraries and include directories */
    void parseLibsAndIncludes(TokenList&, Arguments&);

    /* check if user passed in option */
    bool optionExists(TokenList&, std::string);

    /* get argument associated with option */
    std::string getArg(TokenList&, std::string);
};

namespace ConfigParser
{
    /* parse config file */
    void parse(Arguments&);

    /* find beginning of game section in config file */
    void findGame(Arguments&, std::ifstream&);

    /* parse line and store variable */
    void storeVariable(std::ifstream&, std::string, Arguments&);

    /* parse a table of hex values */
    Table getTable(std::ifstream&);

    /* store memory regions from the config file */
    void storeMemoryRegions(std::ifstream&, Arguments&);

    /* get titles of all games in config file */    
    FileList getGameTitles(std::string);
};

#endif
