#pragma once

#include <string>
#include <algorithm> // std::count
#include <cmath> // floor
#include <stdexcept>
#include <time.h>

std::string convert_datetime (std::string str);
bool date_is_standard (const std::string ymd);
bool time_is_standard (const std::string hms);
std::string convert_date (std::string ymd);
std::string convert_time (std::string hms);
void zero_pad (std::string &t);

std::string prettytime (long int t);
long int timediff (std::string t1, std::string t2);
long int daynum (int y, int m, int d);
int currentYear (int digits);
