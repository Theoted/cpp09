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

    std::string error;

    double value;
    double dataValue;
    while (getline(infile, line))
    {
        error = "";
        date = "";

        if (line == "")
            continue ;
        if (line == "date | value")
            continue ;
        
        getDateFromInfileLine(line, &date);
        if (!isValidDate(date, &error))
        {
            std::cerr << "Error: " << error << " => " << date << std::endl;
            continue ;
        }

        if (getValueFromInfileLine(line, &value, &error) == -1)
        {
            std::cerr << "Error: Invalid value => " << error << std::endl;
            continue ;
        }

        dataValue = findDataNode(date, data);
        std::cout << date << " => " << value << " = " << value * dataValue << std::endl;
    }

    return (0);
}
