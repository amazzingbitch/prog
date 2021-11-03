//
// Created by casde on 02.11.2021.
//
#include "TimeString.h"

TimeString::TimeString() : Date() { time = nullptr; ToStringTime(); }
TimeString::TimeString(int day, int month, int year, int hour, int minute, int second) {
    if (CheckTime(hour, minute, second) && CheckData(day, month, year)) {
        Day = day,  Month = month,  Year = year;
        Hour = hour,  Minute = minute,  Second = second;
        str = nullptr; time = nullptr; ToString(); ToStringTime();
    } else {
        Day = 1, Month = 1, Year = 2007,
        Hour = 0, Minute = 0, Second = 0;
        str = nullptr; time = nullptr; ToString(); ToStringTime();
    }
}
TimeString::TimeString(TimeString &a) : Date (a) { time = nullptr; ToStringTime(); }
TimeString::TimeString(const TimeString &a) : Date (a) { time = nullptr; ToStringTime(); }
TimeString::~TimeString() { delete[]time; }
void TimeString::ToStringTime() {
    int size[3], sum = 0;
    int date[3] = { Hour, Minute, Second };
    int move = 0, tt = 0;
    if (Hour == 0 || Hour == 12) {
        date[0] = 12;
        if (Hour == 12) {
            tt = 1;
        }
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
char* TimeString::GetTime() { char* copy = new char [strlen(time)+1]; strcpy(copy, time); return copy; }
void TimeString::SetDay(int day) {
    if (CheckDay(day, Month, Year)) {
        Day = day; ToString(); ToStringTime();
    } else {
        throw invalid_argument("Invalid day");
    }
}
void TimeString::SetMonth(int month) {
    if (month > 0 && month < 13) {
        Month = month; ToString(); ToStringTime();
    } else {
        throw invalid_argument("Invalid month");
    }
}
void TimeString::SetY(int year) {
    if (year >= 0) {
        Year = year; ToString(); ToStringTime();
    } else {
        throw invalid_argument("Invalid year");
    }
}
void TimeString::SetH(int hour) {
    if (hour < 24 && hour >= 0) {
        Hour = hour; ToString(); ToStringTime();
    } else {
        throw invalid_argument("Invalid hour");
    }
}
void TimeString::SetMinute(int minute) {
    if (minute < 60 && minute >= 0) {
        Minute = minute; ToString(); ToStringTime();
    } else {
        throw invalid_argument("Invalid minute");
    }
}
void TimeString::SetSecond(int second) {
    if (second < 60 && second >= 0) {
        Second = second; ToString(); ToStringTime();
    } else {
        throw invalid_argument("Invalid second");
    }
}
void TimeString::Plus(char k) {
    switch (k) {
        case 'y':
            Year++;
            break;
        case 'M':
            if (Month == 12) {
                Year++;
                Month = 1;
            } else {
                Month++;
            }
            break;
        case 'd':
            if (Day > 27)
                DayPlus();
            else
                Day++;
            break;
        case 'h':
            if (Hour == 23)
                HourPlus();
            else
                Hour++;
            break;
        case 'm':
            if (Minute == 59)
                MinutePlus();
            else
                Minute++;
            break;
        case 's':
            if (Second == 59)
                SecondPlus();
            else
                Second++;
            break;
        default:
            break;
    }
    ToString(); ToStringTime();
}
void TimeString::Minus(char k) {
    switch (k) {
        case 'y':
            if (Year != 0)
                Year--;
            break;
        case 'M':
            if (Month == 1) {
                Year--;
                Month = 12;
            } else {
                Month--;
            }
            break;
        case 'd':
            if (Day == 1)
                DayMinus();
            else
                Day--;
            break;
        case 'h':
            if (Hour == 0)
                HourMinus();
            else
                Hour--;
            break;
        case 'm':
            if (Minute == 0)
                MinuteMinus();
            else
                Minute--;
            break;
        case 's':
            if (Second == 0)
                SecondMinus();
            else
                Second--;
            break;
        default:
            break;
    }
    ToString(); ToStringTime();
}
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
istream &operator>>(istream &is, TimeString &d) {
    is >> d.Day; is.ignore(256, '/');
    is >> d.Month; is.ignore(256, '/');
    is >> d.Year; is.ignore(256, ' ');
    is >> d.Hour; is.ignore(256, ':');
    is >> d.Minute; is.ignore(256, ':');
    is >> d.Second; d.ToString(); d.ToStringTime();
    return is;
}
ostream &operator<<(ostream &os, const TimeString &d) { os << d.str; return os; }
ifstream& BinOut (ifstream& in, TimeString& p) {
    in.read((char*)&p.Day, sizeof(int));
    in.read((char*)&p.Month, sizeof(int));
    in.read((char*)&p.Year, sizeof(int));
    in.read((char*)&p.Hour, sizeof(int));
    in.read((char*)&p.Minute, sizeof(int));
    in.read((char*)&p.Second, sizeof(int));
    p.ToString(); p.ToStringTime();
    return in;
}
ofstream& BinIn (ofstream& os, TimeString& p) {
    os.write((char*)&p.Day, sizeof(int));
    os.write((char*)&p.Month, sizeof(int));
    os.write((char*)&p.Year, sizeof(int));
    os.write((char*)&p.Hour, sizeof(int));
    os.write((char*)&p.Minute, sizeof(int));
    os.write((char*)&p.Second, sizeof(int));
    return os;
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