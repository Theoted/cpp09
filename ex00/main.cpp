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
    return (0);
}
