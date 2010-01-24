#include "parser.hh"

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

Parser::Parser(std::string filename) : file_()
{
    file_.open(filename.c_str());
}

Parser::~Parser()
{
    file_.close();
}

bool Parser::parse(std::ostream& stream_out)
{
    char buf = 0;
    std::string to_interp = "";
    Parser::State state = PARSE;

    if(!file_.is_open())
    {
        return false;
    }

    while(file_.get(buf))
    {
        switch(state)
        {
            case PARSE:
            {
                if(buf == '<' and file_.peek() == '?')
                {
                    file_.get(buf); // throw away the "?"
                    state = READ;
                } else
                {
                    stream_out << buf;
                }
                break;
            }
            case READ:
            {
                if(buf == '?' and file_.peek() == '>')
                {
                    state = INTERPRET;
                } else
                {
                    to_interp += buf;
                }
                break;
            }
            case INTERPRET:
            {
                stream_out << exec_and_read(to_interp);
                to_interp = "";
                state = PARSE;
                break;
            }
            default:
            {
                std::cerr <<
                    "Something wrong with the parser, state is "
                    << state << std::endl;
                return false;
            }
        }
    }

    return true;
}

std::string Parser::exec_and_read(std::string s)
{
    std::string return_string = "";
    char buf[1024];
    FILE* pipe = NULL;

    if(s == "")
    {
        return "";
    }
    
    pipe = popen(s.c_str(), "r");
    if(!pipe)
    {
        return "";
    }
    while(fgets(buf, sizeof(buf), pipe))
    {
        return_string.append(buf);
    }
    if(pclose(pipe) == -1)
    {
        return "";
    }
    return return_string;
}

