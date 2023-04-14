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
    std::map<const std::string, double> infile;

    convertDataToMap(data);
    convertInfileToMap(infile, av[1]);
    printDataMap(infile);
    return (0);
}
