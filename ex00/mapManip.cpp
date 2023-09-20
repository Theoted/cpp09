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
    struct stat     s;

    if (stat("data.csv", &s) == 0)
    {
        if (s.st_mode & S_IFDIR)
        {
            return (handleError("data.csv is a directory"));
        }
    }
    else
    {
        return (handleError("data.csv not found"));
    }

    if (isDatabaseValid() == false) {
        return handleError("invalid database");
    }

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

double findNDataNode(int i, std::map<const std::string, double> &data) {
    int j = -1;
    std::map<const std::string, double>::iterator it = data.begin();
    time_t dateBeforeClosest;

    while (++j < i - 1) {
        ++it;
    }

    dateBeforeClosest = parseDate(it->first);
    return (data.find(formatDate(dateBeforeClosest))->second);
}

double findDataNode(const std::string &myDate, std::map<const std::string, double> &data)
{
    std::map<const std::string, double>::iterator it = data.begin();
    
    time_t date = parseDate(myDate);
    time_t closestDate = parseDate(it->first);
    int i = 0;

    for (; it != data.end(); ++it) {
        
        time_t currDate = parseDate(it->first);
        double diff = difftime(date, currDate);
        if (std::abs(diff) < std::abs(difftime(date, closestDate))) {
            i++;
            closestDate = currDate;
        }
    }
    if (static_cast<size_t>(i) == data.size() - 1) {
        return (data.find(formatDate(closestDate))->second);
    }
    return (findNDataNode(i, data));
}
