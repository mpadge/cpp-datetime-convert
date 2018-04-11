#include "datetime.h"


#include <iostream>

std::string convert_datetime (std::string str)
{
    if (str.find (" ") == std::string::npos)
        throw std::invalid_argument ("Unable to parse date-time string");

    unsigned int ipos = static_cast <unsigned int> (str.find (" "));
    std::string ymd = str.substr (0, ipos);
    str = str.substr (ipos + 1, str.length () - ipos - 1);

    if (!date_is_standard (ymd))
        ymd = convert_date (ymd);
    if (!time_is_standard (str))
        str = convert_time (str);

    return ymd + " " + str;
}

bool date_is_standard (const std::string ymd)
{
    // stardard is yyyy-mm-dd
    bool check = false;
    // std::count counts char not string, so '-', not "-"
    if (ymd.size () == 10 && std::count (ymd.begin(), ymd.end(), '-') == 2)
        check = true;
    return check;
}

bool time_is_standard (const std::string hms)
{
    // stardard is HH:MM:SS
    bool check = false;
    if (hms.size () == 8 && std::count (hms.begin(), hms.end(), ':') == 2)
        check = true;
    return check;
}

std::string convert_date (std::string ymd)
{
    std::string delim = "-";
    if (ymd.find ("/") != std::string::npos)
        delim = "/";

    unsigned int ipos = static_cast <unsigned int> (ymd.find (delim.c_str ()));
    std::string y = ymd.substr (0, ipos);
    ymd = ymd.substr (ipos + 1, ymd.length () - ipos - 1);
    ipos = static_cast <unsigned int> (ymd.find (delim.c_str ()));
    std::string m = ymd.substr (0, ipos);
    std::string d = ymd.substr (ipos + 1, ymd.length () - ipos - 1);

    if (d.size () == 4) // change (y,m,d) = m/d/yyyy -> yyyy/m/d
    {
        std::string s = y;
        y = d;
        d = m;
        m = s;
    }
    if (y.size () == 2)
    {
        if (atoi (y.c_str ()) <= currentYear (2))
            y = "20" + y;
        else
            y = "19" + y;
    }
    zero_pad (m);
    zero_pad (d);

    return y + "-" + m + "-" + d;
}

std::string convert_time (std::string hms)
{
    const std::string delim = ":";
    unsigned int ipos = static_cast <unsigned int> (hms.find (delim.c_str ()));
    std::string h = hms.substr (0, ipos), m, s;
    hms = hms.substr (ipos + 1, hms.length () - ipos - 1);
    if (hms.find (delim.c_str ()) != std::string::npos) // has seconds
    {
        ipos = static_cast <unsigned int> (hms.find (delim.c_str ()));
        m = hms.substr (0, ipos);
        s = hms.substr (ipos + 1, hms.length () - ipos - 1);
    } else
    {
        m = hms;
        s = "00";
    }
    zero_pad (h);
    zero_pad (m);
    zero_pad (s);
    return h + delim + m + delim + s;
}

void zero_pad (std::string &t)
{
    if (t.size () == 1)
        t = "0" + t;
}


// Difference between two time strings formatted as
// YYYY-MM-DD hh:mm:ss
// @param t1 start date-time string
// @param t2 end date-time string
long int timediff (std::string t1, std::string t2)
{
    int Y1 = atoi (t1.substr (0, 4).c_str ()),
        M1 = atoi (t1.substr (5, 2).c_str ()),
        D1 = atoi (t1.substr (8, 2).c_str ()),
        h1 = atoi (t1.substr (11, 2).c_str ()),
        m1 = atoi (t1.substr (14, 2).c_str ()),
        s1 = atoi (t1.substr (17, 2).c_str ()),
        Y2 = atoi (t2.substr (0, 4).c_str ()),
        M2 = atoi (t2.substr (5, 2).c_str ()),
        D2 = atoi (t2.substr (8, 2).c_str ()),
        h2 = atoi (t2.substr (11, 2).c_str ()),
        m2 = atoi (t2.substr (14, 2).c_str ()),
        s2 = atoi (t2.substr (17, 2).c_str ());

    long int y1 = daynum (Y1, M1, D1), y2 = daynum (Y2, M2, D2);
    long int d1 = y1 * 3600 * 24 + h1 * 3600 + m1 * 60 + s1,
        d2 = y2 * 3600 * 24 + h2 * 3600 + m2 * 60 + s2;

    return d2 - d1;
}

// Julian day number calculation from
// http://www.cs.utsa.edu/~cs1063/projects/Spring2011/Project1/jdn-explanation.html
long int daynum (int y, int m, int d)
{
    int a = static_cast <int> (floor ((14.0 - m) / 12.0));
    y = y + 4800 - a;
    m = m + 12 * a - 3;
    long int res = static_cast <long int> (d) +
        static_cast <int> (floor ((153 * m + 2) / 5)) +
        static_cast <long int> (365 * y) +
        static_cast <long int> (floor (y / 4)) -
        static_cast <long int> (floor (y / 100)) +
        static_cast <long int> (floor (y / 400)) - 32045;
    return res;
}

// format output of timediff as days, hours, min, seconds
std::string prettytime (long int t)
{
    std::string out;
    int days = static_cast <int> (floor (t / (3600 * 24)));
    if (days > 0)
        out += std::to_string (days) + " days, ";
    t = t - days * 3600 * 24;
    int hh = static_cast <int> (floor (t / 3600));
    if (days > 0 | hh > 0)
        out += std::to_string (hh) + ":";
    t = t - hh * 3600;
    int mm = static_cast <int> (floor (t / 60));
    std::string s = std::to_string (mm);
    if (days > 0 | hh > 0)
    {
        zero_pad (s);
        out += s + ":";
    } else if (mm > 0)
        out += s + ":";
    s = std::to_string (t - mm * 60);
    zero_pad (s);

    return out + s;
}

int currentYear (int digits) {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime (buf, sizeof(buf), "%Y", &tstruct);
    std::string y = buf;
    if (digits == 2)
        y = y.substr (3, 2);
    return atoi (y.c_str ());
}
