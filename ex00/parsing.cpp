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
        return (-1);
    
    *date = line.substr(0, commaPos);
    return (0);
}

int getValueFromDataLine(const std::string &line, double *value)
{
    size_t commaPos = line.find(',');
    if (commaPos == std::string::npos)
        return (-1);

    const std::string s_value = line.substr(commaPos + 1, line.size() - commaPos);
    *value = std::strtod(s_value.c_str(), NULL);

    return (0);
}

// PARSE INFILE
int getDateFromInfileLine(const std::string &line, std::string *date)
{
    size_t pipePos = line.find('|');
    if (pipePos == std::string::npos)
        return (-1);
    
    *date = line.substr(0, pipePos);
    return (0);
}

int getValueFromInfileLine(const std::string &line, double *value)
{
    size_t pipePos = line.find('|');
    if (pipePos == std::string::npos)
    {
        *value = -1;
        return (-1);
    }

    const std::string s_value = line.substr(pipePos + 1, line.size() - pipePos);
    *value = std::strtod(s_value.c_str(), NULL);

    return (0);
}

// PARSE DATE
bool isValidDate(std::string myDate)
{
    int year, month, day;
    char delim;
    std::stringstream ss(myDate);
    ss >> year >> delim >> month >> delim >> day;
    if (ss.fail()) {
        return false;
    }

    struct tm date;
    std::memset(&date, 0, sizeof(struct tm));
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;
    
    time_t t = mktime(&date);
    return (t != -1) && (date.tm_year == year - 1900) && (date.tm_mon == month - 1) && (date.tm_mday == day);
}

time_t parseDate(const std::string &dateStr)
{
    struct tm timeStruct = {};
    strptime(dateStr.c_str(), "%Y-%m-%d", &timeStruct);
    return (mktime(&timeStruct));
}

std::string formatDate(time_t date)
{
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&date));
    return (std::string(buffer));
}
