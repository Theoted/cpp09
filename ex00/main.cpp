#include "main.hpp"

int handleError(const std::string &err)
{
    std::cerr << err << std::endl;
    return (-1);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (handleError("./btc infile"));

    std::map<const std::string, double> data;

    convertDataToMap(data);
    
    std::ifstream infile;

    openFile(infile, av[1]);

    std::string line;
    std::string date;

    double value;
    double dataValue;
    while (getline(infile, line))
    {
        if (line == "date | value")
            continue ;
        
        getDateFromInfileLine(line, &date);
        getValueFromInfileLine(line, &value);

        if (!isValidDate(date))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue ;
        }

        if (value < 0 || value > 1000)
        {
            std::cerr << "Error: Invalid value => " << value << std::endl;
            continue ;
        }

        dataValue = findDataNode(date, data);
        std::cout << date << " => " << value << " = " << value * dataValue << std::endl;
    }

    return (0);
}
