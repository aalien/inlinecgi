#include "parser.hh"
#include <iostream>
#include <string>

void show_usage()
{
    std::cout << "inlinecgi FILE" << std::endl;
}

int main(int argc, char** argv)
{
    std::string filename = "";
    
    if(argc != 2)
    {
        show_usage();
        return 1;
    }

    filename = argv[1];
    Parser parser(filename);
    if(!parser.parse(std::cout))
    {
        std::cout << "Could not parse file " << filename << std::endl;
        return 1;
    }
    return 0;
}

