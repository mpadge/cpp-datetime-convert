#pragma once

#include <string>
#include <algorithm> // std::count
#include <cmath> // floor
#include <stdexcept>

std::string convert_datetime (std::string str);
bool date_is_standard (const std::string ymd);
bool time_is_standard (const std::string hms);
std::string convert_date (std::string ymd);
std::string convert_time (std::string hms);
void zero_pad (std::string &t);

std::string prettytime (int t);
int timediff (std::string t1, std::string t2);
int daynum (int y, int m, int d);
