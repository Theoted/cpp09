#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <cmath>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// MAIN
int handleError(const std::string &err);

// FILE MANIP
int openFile(std::ifstream &infile, const char *file);
bool isDatabaseValid();

// MAP MANIP
int convertDataToMap(std::map<const std::string, double> &data);
void printDataMap(std::map<const std::string, double> &data);
double findDataNode(const std::string &myDate, std::map<const std::string, double> &data);
// PARSING
int getDateFromDataLine(const std::string &line, std::string *date);
int getValueFromDataLine(const std::string &line, double *value);

int getDateFromInfileLine(const std::string &line, std::string *date);
int getValueFromInfileLine(const std::string &line, double *value, std::string *error);

bool isValidDate(std::string myDate, std::string *error);
time_t parseDate(const std::string &dateStr);
std::string formatDate(time_t date);