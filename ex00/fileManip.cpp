#include "main.hpp"

int openFile(std::ifstream &infile, const char *file)
{
    infile.open(file);
    if (!infile)
        return (handleError("infile not found"));    

    return (0);
}

static bool isValidDateFormat(const std::string& date) {
    if (date.length() != 10)
        return (false);

    std::istringstream dateStream(date);
    int year, month, day;
    char dash1, dash2;
    if (!(dateStream >> year >> dash1 >> month >> dash2 >> day))
        return (false);
    if (dateStream.get() != EOF)
        return (false);
    if (dash1 != '-' || dash2 != '-')
        return (false);
    if (month < 1 || month > 12 || day < 1 || day > 31)
        return (false);
    return (true);
}

static bool isValidValue(const std::string& value) {
    if (value.find_first_not_of("0123456789.") == std::string::npos) {
	    return (true);
    }
    else {
	    return (false);
    }
}

static bool isValidDatabaseEntry(const std::string& entry) {

    size_t commaPos = entry.find(',');
    if (commaPos == std::string::npos)
        return (false);

    std::string datePart = entry.substr(0, commaPos);
    std::string valuePart = entry.substr(commaPos + 1);
    if (!isValidDateFormat(datePart))
        return (false);

    if (!isValidValue(valuePart))
        return (false);

    return (true);
}

bool isDatabaseValid() {
    std::ifstream   dataBase("data.csv");
    std::string     line;
    int i = -1;

    while (getline(dataBase, line))
    {
        i++;
        if (i == 0)
            continue ;
        if (isValidDatabaseEntry(line) == false)
            return (false);
    }
    return (true);
}
