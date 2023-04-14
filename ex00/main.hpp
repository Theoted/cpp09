#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <iomanip>

// MAIN
int handleError(const std::string &err);

// FILE MANIP
int openFile(std::ifstream &infile, const char *file);

// MAP MANIP
int convertDataToMap(std::map<const std::string, double> &data);
int convertInfileToMap(std::map<const std::string, double> &data, const char *file);
void printDataMap(std::map<const std::string, double> &data);

// PARSING
int getDateFromDataLine(const std::string &line, std::string *date);
int getValueFromDataLine(const std::string &line, double *value);

int getDateFromInfileLine(const std::string &line, std::string *date);
int getValueFromInfileLine(const std::string &line, double *value);