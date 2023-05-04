#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>
#include <deque>
#include <time.h>
#include <iomanip>

template<typename Container>
void printVec(const Container vec)
{
    for(std::size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << ' ';
        if (i >= 3)
        {
            std::cout << "[...]";
            return ;
        }
    }
    std::cout << std::endl;
}

template<typename Container>
Container merge(Container a, Container b)
{
    Container c;

    while (a.size() > 0 && b.size() > 0)
    {
        if (a[0] > b[0])
        {
            c.push_back(b[0]);
            b.erase(b.begin() + 0);
        }
        else
        {
            c.push_back(a[0]);
            a.erase(a.begin() + 0);
        }
    }

    while (a.size() > 0)
    {
        c.push_back(a[0]);
        a.erase(a.begin() + 0);
    }

    while (b.size() > 0)
    {
        c.push_back(b[0]);
        b.erase(b.begin() + 0);
    }

    return (c);
}

template<typename Container>
Container mergeSort(Container vec)
{
    std::size_t len = vec.size();

    if (len == 1)
        return (vec);

    std::size_t const half_size = vec.size() / 2;

    typename Container::iterator begin = vec.begin();
    typename Container::iterator half = vec.begin() + half_size;
    typename Container::iterator end = vec.end();

    Container first_half(begin, half);
    Container second_half(half, end);

    first_half = mergeSort(first_half);
    second_half = mergeSort(second_half);
    return (merge(first_half, second_half));
}

int isDigits(const char *str)
{
    for (int i = 0; str[i]; i++) {
        if (!(str[i] >= 48 && str[i] <= 57 && str[i] != '-' && str[i] != '+'))
            return (1);
    }
    return (0);
}

template<typename Container>
Container createContainer(char **input)
{
    int i = 1;
    Container create;
    while (input[i])
    {
        create.push_back(std::atoi(input[i]));
        if (isDigits(input[i]))
        {
            std::cerr << "Error: input error: " << input[i] << "\n";
            exit(1);
        }
        i++;
    }
    return (create);
}

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "./PmergeMe [int list to sort]\n";
        return (-1);
    }
    std::vector<int> vec;
    std::deque<int> deq;
    int n = ac - 1;

    clock_t start_t, end_t, start_t1, end_t1;
    double total_t, total_t1;

    vec = createContainer<std::vector<int> >(av);
    deq = createContainer<std::deque<int> >(av);

    std::cout << "before: ";
    printVec(vec);
    std::cout << "\n";

    // SORT USING VEC
    start_t = clock();
    vec = mergeSort(vec);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    // SORT USING DEQ
    start_t1 = clock();
    deq = mergeSort(deq);
    end_t1 = clock();
    total_t1 = (double)(end_t1 - start_t1) / CLOCKS_PER_SEC;

    std::cout << "after: ";
    printVec(vec);
    std::cout << "\n";

    std::cout << std::fixed;
    std::cout << std::setprecision(6);
    std::cout << "Time to process a range of  " << n << " elements with std::vector :  " << total_t << " us"<< std::endl;
    std::cout << "Time to process a range of  " << n << " elements with std::deque  :  " << total_t1 << " us"<< std::endl;


    return (0);
}