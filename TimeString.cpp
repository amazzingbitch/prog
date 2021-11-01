//
// Created by casde on 02.11.2021.
//
#include "TimeString.h"

TimeString::TimeString() {
    Day = 1, Month = 1, Year = 2007,
    Hour = 0, Minute = 0, Second = 0;
    str = nullptr; time = nullptr;
    ToString(); ToStringTime();
}
TimeString::TimeString(int day, int month, int year, int hour, int minute, int second) {
    if (CheckTime(hour, minute, second) && CheckData(day, month, year)) {
        Day = day,  Month = month,  Year = year;
        Hour = hour,  Minute = minute,  Second = second;
        str = nullptr; time = nullptr;
        ToString(); ToStringTime();
    } else {
        Day = 1, Month = 1, Year = 2007,
        Hour = 0, Minute = 0, Second = 0;
        str = nullptr; time = nullptr;
        ToString(); ToStringTime();
    }
}
TimeString::TimeString(TimeString &a) {
    Day = a.Day,  Month = a.Month,  Year = a.Year;
    Hour = a.Hour,  Minute = a.Minute,  Second = a.Second;
    str = nullptr; time = nullptr;
    ToString(); ToStringTime();
}
TimeString::~TimeString() {
    delete[]time; delete[]str;
}
void TimeString::ToStringTime() {
    int size[3], sum = 0;
    int date[3] = { Hour, Minute, Second };
    int move = 0, tt = 0;
    if (Hour == 0) {
        date[0] = 12;
    } else if (Hour > 12) {
        date[0] = Hour - 12; tt = 1;
    }
    for (int i = 0; i < 3; i++) {
        size[i] = countCalc(date[i]);
        sum += countCalc(date[i]);
    }
    delete[] time; time = new char[sum + 6];
    for (int i = 0; i < 3; i++) {
        sprintf(time + move, "%d", date[i]); move += size[i];
        if (i < 2) {
            sprintf(time + move, "%c", ':'); move++;
        }
        else {
            sprintf(time + move, "%c", ' '); move++;
            if (tt) sprintf(time + move, "%s", "pm");
            else sprintf(time + move, "%s", "am");
        }
    }
}
char* TimeString::GetTime() {
    char* copy = new char [strlen(time)+1];
    strcpy(copy, time);
    return copy;
}