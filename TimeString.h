//
// Created by casde on 01.11.2021.
//

#ifndef DATE_CPP_TIMESTRING_H
#define DATE_CPP_TIMESTRING_H

#include "Date.h"
#include <cstring>
#include <fstream>

class TimeString : public Date {
public:
    TimeString();
    TimeString(int day, int month, int year, int hour, int minute, int second);
    TimeString(TimeString &a);
    ~TimeString();
    void ToStringTime();
    char* GetTime();

protected:
    char* time;
};

#endif //DATE_CPP_TIMESTRING_H
