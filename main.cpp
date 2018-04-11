#include <vector>
#include <iostream>

#include "datetime.h"

int main ()
{
    // Demonstrate conversion from a range of formats:
    std::vector <std::string> tests (16);
    tests [0] = "2000-01-01 01:01:00";
    tests [1] = "2000-01-01 01:01";
    tests [2] = "2000-01-01 1:1:0";
    tests [3] = "2000-01-01 1:1";
    tests [4] = "2000-1-1 01:01:00";
    tests [5] = "2000-1-1 01:01";
    tests [6] = "2000-1-1 1:1:0";
    tests [7] = "2000-1-1 1:1";
    tests [8] = "01/01/2000 01:01:00";
    tests [9] = "01/01/2000 01:01";
    tests [10] = "01/01/2000 1:1:0";
    tests [11] = "01/01/2000 1:1";
    tests [12] = "1/1/2000 01:01:00";
    tests [13] = "1/1/2000 01:01";
    tests [14] = "1/1/2000 1:1:0";
    tests [15] = "1/1/2000 1:1";

    for (auto t: tests)
        std::cout << "[" << t << " -> " << convert_datetime (t) << "]" << std::endl;

    // Demonstrate the timediff function
    tests [0] = "1967-12-23 01:34:57";
    tests [1] = "1967-12-23 01:34:57";
    //tests [1] = "2014-07-18 18:37:11";
    tests [2] = "1967-12-23 14:23:02";
    tests [3] = "1967-12-23 04:23:02";
    tests [4] = "1967-12-23 01:35:07";
    for (int i = 1; i < 5; i++)
    {
        long int d = timediff (tests [0], tests [i]);
        std::cout << "time difference = " << prettytime (d) << std::endl;
    }
}
