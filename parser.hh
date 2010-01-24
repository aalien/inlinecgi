#include <string>
#include <fstream>
#include <iostream>

class Parser
{
    public:
        Parser(std::string filename);
        ~Parser();

        bool parse(std::ostream& stream_out);
        std::string exec_and_read(std::string s);
    
    private:
        std::ifstream file_;
        
        // states for parser
        enum State { PARSE, READ, INTERPRET };
};

