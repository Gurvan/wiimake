#include "Parser.h"
#include "Global.h"

/* parse config file */
void ConfigParser::parse(Arguments& args)
{
    /* find beginning of game info */
    std::ifstream file = ConfigParser::findGame(args);

    /* parse arguments */
    std::string line;
    while (!file.eof())
    {
        /* keep reading until variable is found */
        if (line.find("=") == std::string::npos)
        {
            file >> line;
        }
        else
        {
            ConfigParser::storeVariable(file, line, args);
            file >> line;
        }
    }

    /* close file */
    file.close();
}

/* find beginning of game section in config file */
std::ifstream ConfigParser::findGame(Arguments& args)
{
    /* open up text file */
    std::ifstream file (args.cmdOptions["--config-file"]);

    /* read until correct game number found */
    std::string line;
    while (!file.eof() && line != "game_id=" + args.cmdOptions["--game-id"])
    {
        file >> line;
    }

    /* return file stream */
    return file;
}

/* parse line and store variable */
void ConfigParser::storeVariable(std::ifstream& file, std::string line,
Arguments& args)
{
    /* get variable name and value */
    std::string name = line.substr(0, line.find("="));
    std::string value = line.substr(line.find("=") + 1);

    /* parse special variables differently */
    if (name == "address_table")
    {
        args.addressTable = ConfigParser::getTable(file);
    }
    else if (name == "memory_regions")
    {
        ConfigParser::storeMemoryRegions(file, args);
    }
    else
    {
        args.configOptions.insert(std::make_pair(name,
            stoul(value, nullptr, 16)));
    }
}

/* parse a table of hex values */
Table ConfigParser::getTable(std::ifstream& file)
{
    /* return vector */
    Table table;
        
    /* read to first line */
    std::string line;
    file >> line; file >> line;

    /* read until closing bracket */
    while (line.find("}") == std::string::npos)
    {
        /* get values */
        std::string val_1 = line.substr(0, line.find("-"));
        std::string val_2 = line.substr(line.find("-") + 1);

        /* add to table */
        table.push_back(std::make_pair(
            stoul(val_1, nullptr, 16), stoul(val_2, nullptr, 16)));

        /* read next line */
        file >> line;
    }

    /* return table */
    return table;
}        

/* store memory regions from the config file */
void ConfigParser::storeMemoryRegions(std::ifstream& file, Arguments& args)
{
    /* get table */
    Table table = ConfigParser::getTable(file);

    /* iterate through and create MemRegion objects */
    for (auto it = table.begin(); it != table.end(); ++it)
    {
        /* add object to memory region list */
        args.memRegions.push_back(MemRegion((*it).first, (*it).second));
    }
}

