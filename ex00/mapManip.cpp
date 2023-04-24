#include "main.hpp"

void printDataMap(std::map<const std::string, double> &data)
{
    std::map<const std::string, double>::iterator it;
    for (it = data.begin(); it != data.end(); ++it) {
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

double findDataNode(const std::string &myDate, std::map<const std::string, double> &data)
{
    std::map<const std::string, double>::iterator it = data.begin();
    
    time_t date = parseDate(myDate);
    time_t closestDate = parseDate(it->first);

    for (; it != data.end(); ++it) {
        
        time_t currDate = parseDate(it->first);
        double diff = difftime(date, currDate);
        
        if (std::abs(diff) < std::abs(difftime(date, closestDate)))
            closestDate = currDate;
    }

    return (data.find(formatDate(closestDate))->second);
}
