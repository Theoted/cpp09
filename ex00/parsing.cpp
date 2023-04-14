#include "main.hpp"

std::string strtrim(std::string str) {
    const char* whitespace_type = " ";
    str.erase(str.find_last_not_of(whitespace_type) + 1);
    str.erase(0,str.find_first_not_of(whitespace_type));
    return str;
}

// PARSE DATABASE
int getDateFromDataLine(const std::string &line, std::string *date)
{
    size_t commaPos = line.find(',');
    if (commaPos == std::string::npos)
        return (handleError("Error: data formating"));
    
    *date = line.substr(0, commaPos);
    return (0);
}

int getValueFromDataLine(const std::string &line, double *value)
{
    size_t commaPos = line.find(',');
    if (commaPos == std::string::npos)
        return (handleError("Error: data formating"));

    const std::string s_value = line.substr(commaPos + 1, line.size() - commaPos);
    *value = std::strtod(s_value.c_str(), NULL);

    return (0);
}

// PARSE INFILE
int getDateFromInfileLine(const std::string &line, std::string *date)
{
    size_t pipePos = line.find('|');
    if (pipePos == std::string::npos)
        return (handleError("Error: infile formating"));
    
    *date = line.substr(0, pipePos);
    return (0);
}

int getValueFromInfileLine(const std::string &line, double *value)
{
    size_t pipePos = line.find('|');
    if (pipePos == std::string::npos)
        return (handleError("Error: infile formating"));

    const std::string s_value = line.substr(pipePos + 1, line.size() - pipePos);
    *value = std::strtod(s_value.c_str(), NULL);

    return (0);
}
