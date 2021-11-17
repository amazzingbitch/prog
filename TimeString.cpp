//
// Created by casde on 02.11.2021.
//
#include "TimeString.h"

TimeString::TimeString() : Date() { time = nullptr; ToStringTime(); }
TimeString::TimeString(int day, int month, int year, int hour, int minute, int second) {
    if (CheckTime(hour, minute, second) && CheckData(day, month, year)) {
        Day = day,  Month = month,  Year = year; Hour = hour,  Minute = minute,  Second = second;
        str = nullptr; time = nullptr; ToStringTime();
    } else {
        Day = 1, Month = 1, Year = 2007, Hour = 0, Minute = 0, Second = 0;
        str = nullptr; time = nullptr; ToStringTime();
    }
}
TimeString::TimeString(TimeString &a) : Date (a) { time = nullptr; ToStringTime(); }
TimeString::TimeString(const TimeString &a) : Date (a) { time = nullptr; ToStringTime(); }
TimeString::~TimeString() { delete[]time; }
void TimeString::ToStringTime() {
    int size[6], sum = 0;
    int date[6] = { Day, Month, Year, Hour, Minute, Second };
    for (int i = 0; i < 6; i++) {
        size[i] = countCalc(date[i]);
        sum += countCalc(date[i]);
    }
    delete[] str;
    str = new char[sum + 6];
    int move = 0;
    for (int i = 0; i < 6; i++) {
        sprintf(str + move, "%d", date[i]);
        move += size[i];
        if (i < 2) {
            sprintf(str + move, "%c", '/');
            move++;
        }
        else if (i == 2) {
            sprintf(str + move, "%c", ' ');
            move++;
        }
        else if (i < 5) {
            sprintf(str + move, "%c", ':');
            move++;
        }
    }
    int size2[3], sum2 = 0;
    int date2[3] = { Hour, Minute, Second };
    int move2 = 0, tt = 0;
    if (Hour == 0 || Hour == 12) {
        date2[0] = 12;
        if (Hour == 12) {
            tt = 1;
        }
    } else if (Hour > 12) {
        date2[0] = Hour - 12; tt = 1;
    }
    for (int i = 0; i < 3; i++) {
        size2[i] = countCalc(date2[i]);
        sum2 += countCalc(date2[i]);
    }
    delete[] time; time = new char[sum + 6];
    for (int i = 0; i < 3; i++) {
        sprintf(time + move2, "%d", date2[i]); move2 += size2[i];
        if (i < 2) {
            sprintf(time + move2, "%c", ':'); move2++;
        }
        else {
            sprintf(time + move2, "%c", ' '); move2++;
            if (tt) sprintf(time + move2, "%s", "pm");
            else sprintf(time + move2, "%s", "am");
        }
    }
}
void TimeString::ToString() {
    int size[6], sum = 0;
    int date[6] = { Day, Month, Year, Hour, Minute, Second };
    for (int i = 0; i < 6; i++) {
        size[i] = countCalc(date[i]);
        sum += countCalc(date[i]);
    }
    delete[] str;
    str = new char[sum + 6];
    int move = 0;
    for (int i = 0; i < 6; i++) {
        sprintf(str + move, "%d", date[i]);
        move += size[i];
        if (i < 2) {
            sprintf(str + move, "%c", '/');
            move++;
        }
        else if (i == 2) {
            sprintf(str + move, "%c", ' ');
            move++;
        }
        else if (i < 5) {
            sprintf(str + move, "%c", ':');
            move++;
        }
    }
    int size2[3], sum2 = 0;
    int date2[3] = { Hour, Minute, Second };
    int move2 = 0, tt = 0;
    if (Hour == 0 || Hour == 12) {
        date2[0] = 12;
        if (Hour == 12) {
            tt = 1;
        }
    } else if (Hour > 12) {
        date2[0] = Hour - 12; tt = 1;
    }
    for (int i = 0; i < 3; i++) {
        size2[i] = countCalc(date2[i]);
        sum2 += countCalc(date2[i]);
    }
    delete[] time; time = new char[sum2 + 6];
    for (int i = 0; i < 3; i++) {
        sprintf(time + move2, "%d", date2[i]); move2 += size2[i];
        if (i < 2) {
            sprintf(time + move2, "%c", ':'); move2++;
        }
        else {
            sprintf(time + move2, "%c", ' '); move2++;
            if (tt) sprintf(time + move2, "%s", "pm");
            else sprintf(time + move2, "%s", "am");
        }
    }
}
char* TimeString::GetTime() { char* copy = new char [strlen(time)+1]; strcpy(copy, time); return copy; }
TimeString operator+(const TimeString &d1, const TimeString &d2) {
    TimeString temp;
    int month, day, hour, min, sec;
    temp.Year = d1.Year + d2.Year;
    month = d1.Month + d2.Month;
    if (month <= 12) {
        temp.Month = month;
    } else {
        temp.Month = 0;
        for (int i = 0; i < month; i++) {
            temp.Plus('M');
        }
    }
    day = d1.Day + d2.Day;
    if (day < 28) {
        temp.Day = day;
    } else {
        temp.Day = 0;
        for (int i = 0; i < day; i++) {
            temp.Plus('d');
        }
    }
    hour = d1.Hour + d2.Hour;
    if (hour < 24) {
        temp.Hour = hour;
    } else {
        temp.Hour = 0;
        for (int i = 0; i < hour; i++) {
            temp.Plus('h');
        }
    }
    min = d1.Minute + d2.Minute;
    if (min < 60) {
        temp.Minute = min;
    } else {
        temp.Minute = 0;
        for (int i = 0; i < min; i++) {
            temp.Plus('m');
        }
    }
    sec = d1.Second + d2.Second;
    if (sec < 60) {
        temp.Second = sec;
    } else {
        temp.Second = 0;
        for (int i = 0; i < sec; i++) {
            temp.Plus('s');
        }
    }
    temp.ToString(); temp.ToStringTime();
    return temp;
}
TimeString &TimeString::operator=(const TimeString &a) {
    if (this == &a) {
        return *this;
    }
    Day = a.Day,  Month = a.Month,  Year = a.Year;
    Hour = a.Hour,  Minute = a.Minute,  Second = a.Second;
    ToString(); ToStringTime(); return *this;
}
TimeString operator-(const TimeString &d1, const TimeString &d2) {
    TimeString temp;
    if (d1.Year < d2.Year) {
        throw invalid_argument("Negative year");
    } else {
        temp.Year = d1.Year - d2.Year;
    }
    temp.Month = d1.Month; int raz;
    if ((d1.Month - d2.Month) >= 1) {
        raz = abs(d1.Month - d2.Month);
    } else {
        raz = abs(d1.Month - d2.Month) + 2;
    }
    for (int i = 0; i < raz; i++) {
        temp.Minus('M');
    }
    temp.Day = d1.Day;
    for (int i = 0; i < abs(d1.Day - d2.Day); i++) {
        temp.Minus('d');
    }
    temp.Hour = d1.Hour; raz = d2.Hour;
    for (int i = 0; i < raz; i++) {
        temp.Minus('h');
    }
    temp.Minute = d1.Minute; raz = d2.Minute;
    for (int i = 0; i < raz; i++) {
        temp.Minus('m');
    }
    temp.Second = d1.Second; raz = d2.Second;
    for (int i = 0; i < raz; i++) {
        temp.Minus('s');
    }
    temp.ToString(); temp.ToStringTime(); return temp;
}
TimeString operator+(const TimeString &d1, int hour) {
    TimeString temp(d1);
    for (int i = 0; i < hour; i++) {
        temp.Plus('h');
    }
    return temp;
}
TimeString operator-(const TimeString &d1, int hour) {
    TimeString temp(d1);
    for (int i = 0; i < hour; i++) {
        if (temp.Year == 0 && temp.Month == 1 && temp.Day == 1 && temp.Hour == 0 && temp.Minute == 0 && temp.Second == 0)
            throw invalid_argument("Negative year");
        temp.Minus('h');
    }
    return temp;
}
