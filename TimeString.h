//
// Created by casde on 01.11.2021.
//

#ifndef DATE_CPP_TIMESTRING_H
#define DATE_CPP_TIMESTRING_H

#include "Date.h"

class TimeString : public Date {
public:
    TimeString();
    TimeString(int day, int month, int year, int hour, int minute, int second);
    TimeString(TimeString &a);
    TimeString(const TimeString &a);
    ~TimeString();
    void ToStringTime();
    char* GetStrDate();
    char* GetStr() override;
    void ToString() override;
    friend TimeString operator+(const TimeString &d1, const TimeString &d2);
    friend TimeString operator-(const TimeString &d1, const TimeString &d2);
    friend TimeString operator+(const TimeString &d1, int hour);
    friend TimeString operator-(const TimeString &d1, int hour);
    TimeString &operator=(const TimeString &right);

protected:
    char* time;
};

#endif //DATE_CPP_TIMESTRING_H
