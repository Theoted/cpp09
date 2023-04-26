#include <vector>
#include <list>
#include <iostream>
#include <string>

// int merge()
// {
//     std::list<std::vector<int>> 
//     return (0);
// }

// int mergeSort()
// {
//     return (0);
// }

int isDigits(const char *str)
{
    for (int i = 0; str[i]; i++) {
        if (!(str[i] >= 48 && str[i] <= 57 && str[i] != '-' && str[i] != '+'))
            return (1);
    }
    return (0);
}

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "./PmergeMe [int list to sort]\n";
        return (-1);
    }
    std::vector<int> vec;
    std::string input(av[1]);
    int i = 1;
    while (av[i])
    {
        vec.push_back(std::atoi(av[i]));
        if (isDigits(av[i]))
        {
            std::cerr << "Error: input error: " << av[i] << "\n";
            return (-1);
        }
        i++;
    }

    return (0);
}