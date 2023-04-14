#include "main.hpp"

void printDataMap(std::map<const std::string, double> &data)
{
    std::map<const std::string, double>::iterator it;
    for (it = data.begin(); it != data.end(); it++) {
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    }
}

int convertDataToMap(std::map<const std::string, double> &data)
{
    std::string     line;
    std::ifstream   dataBase("data.csv");
    std::string     date;
    double          value;

    while (getline(dataBase, line))
    {
        if (line == "date,exchange_rate")
            continue ;
        getDateFromDataLine(line, &date);
        getValueFromDataLine(line, &value);
        data.insert(std::pair<const std::string, double>(date, value));
    }

    return (0);
}

int convertInfileToMap(std::map<const std::string, double> &data, const char *file)
{
    std::string     line;
    std::ifstream   infile;
    std::string     date;
    double          value;

    if (openFile(infile, file) == -1)
        return (-1);

    while (getline(infile, line))
    {
        if (line == "date | value")
            continue ;
        getDateFromInfileLine(line, &date);
        getValueFromInfileLine(line, &value);
        data.insert(std::pair<const std::string, double>(date, value));
    }

    return (0);
}
