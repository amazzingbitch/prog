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
    TimeString(const TimeString &a);
    ~TimeString();
    void ToStringTime();
    char* GetTime();

    void SetDay(int day) override;
    void SetMonth(int month) override;
    void SetY(int year) override;
    void SetH(int hour) override;
    void SetMinute(int minute) override;
    void SetSecond(int second) override;
    void Plus(char k) override;
    void Minus(char k) override;

    friend TimeString operator+(const TimeString &d1, const TimeString &d2);
    friend TimeString operator-(const TimeString &d1, const TimeString &d2);
    TimeString &operator=(const TimeString &right);
    friend istream& operator >> (istream& os, TimeString& d);
    friend ifstream& BinOut (ifstream &is, TimeString &val);

protected:
    char* time;
};

#endif //DATE_CPP_TIMESTRING_H
