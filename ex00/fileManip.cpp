#include "main.hpp"

int openFile(std::ifstream &infile, const char *file)
{
    infile.open(file);
    if (!infile)
        return (handleError("infile not found"));    

    return (0);
}
