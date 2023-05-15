#include "main.hpp"

std::string strtrim(std::string str)
{
    const char *whitespace_type = " ";
    str.erase(str.find_last_not_of(whitespace_type) + 1);
    str.erase(0, str.find_first_not_of(whitespace_type));
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

static bool isNumber(const std::string s_value)
{
    int i = 0;
    int point_count = 0;
    int n_count = 0;
    while (s_value[i] == ' ' && s_value[i])
        i++;
    while (s_value[i])
    {
        if (s_value[i] == '.')
        {
            if (point_count == 1)
                return (false);
            point_count++;
        }
        if ((s_value[i] < 48 || s_value[i] > 57) && s_value[i] != '.')
            return (false);
        if ((s_value[i] >= 48 && s_value[i] <= 57))
            n_count++;
        i++;
    }
    if (n_count == 0)
        return (false);
    return (true);
}

int getValueFromInfileLine(const std::string &line, double *value, std::string *error)
{
    size_t pipePos = line.find('|');
    if (pipePos == std::string::npos)
    {
        *value = -1;
        *error = "No value";
        return (-1);
    }

    const std::string s_value = line.substr(pipePos + 1, line.size() - pipePos);
    if (!isNumber(s_value))
    {
        *value = -1;
        *error = s_value;
        return (-1);
    }

    *value = std::strtod(s_value.c_str(), NULL);
    if (*value < 0)
    {
        *error = "not a positive number";
        return (-1);
    }
    if (*value > 1000)
    {
        *error = "too large a number";
        return (-1);
    }
    return (0);
}

// PARSE DATE
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

bool checkDateFormat(std::string myDate)
{
    int count = 1;
    size_t i = 0;

    for (i = 0; i < myDate.size(); i++)
    {
        std::cout << myDate.at(i) << std::endl;
        if (myDate.at(i) == '-')
            break ;
        count++;
    }
    if (count != 4)
        return (false);

    count = 1;
    i++;

    for (size_t j = 0; j < 2; j++)
    {
        for (i = 0; i < myDate.size(); i++)
        {
            if (myDate.at(i) == '-')
                break ;
            count++;
        }
        if (count != 2)
            return (false);
        count = 1;
        i++;
    }
    return (true);
}

bool isValidDate(std::string myDate, std::string *error)
{
    for (size_t i = 0; i < myDate.size(); i++)
    {
        if (!std::isdigit(myDate[i]) && myDate[i] != '-' && myDate[i] != ' ')
        {
            *error = "bad date";
            return (false);
        }
    }

    time_t date = parseDate(myDate);
    if (date == -1)
    {
        *error = "bad date";
        return false;
    }

    if (checkDateFormat(myDate) == false)
    {
        *error = "bad format";
        return false;
    }

    std::stringstream ss(myDate);
    int year;
    ss >> year;

    if (year > 2023 || year < 2009)
    {
        *error = "outside db";
        return (false);
    }

    return (true);
}
