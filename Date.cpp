//
// Created by casde on 15.10.2021.
//

#include "Date.h"

Date::Date() {
    Day = 1, Month = 1, Year = 2007,
    Hour = 0, Minute = 0, Second = 0;
    this->str = nullptr;
    sizeStr = 0;
    ToString();
}
Date::Date(int day, int month, int year, int hour, int minute, int second) {
    if (CheckTime(hour, minute, second) && CheckData(day, month, year)) {
        this-> Day = day, this-> Month = month, this-> Year = year;
        this-> Hour = hour, this-> Minute = minute, this-> Second = second;
        this->str = nullptr;
        sizeStr = 0;
        ToString();
    } else {
        Day = 1, Month = 1, Year = 2007,
        Hour = 0, Minute = 0, Second = 0;
        this->str = nullptr;
        sizeStr = 0;
        ToString();
    }
}
Date::Date(Date &a) {
    this-> Day = a.Day, this-> Month = a.Month, this-> Year = a.Year;
    this-> Hour = a.Hour, this-> Minute = a.Minute, this-> Second = a.Second;
    this->str = nullptr; this->sizeStr = 0;
    ToString();
}
Date::Date(const Date &a) {
    this-> Day = a.Day, this-> Month = a.Month, this-> Year = a.Year;
    this-> Hour = a.Hour, this-> Minute = a.Minute, this-> Second = a.Second;
    this->str = nullptr; this->sizeStr = 0;
    ToString();
}
Date::~Date() {
    delete[]this->str;
}
void Date::ToString() {
    int size[6], sum = 0;
    int date[6] = { Day, Month, Year, Hour, Minute, Second };
    for (int i = 0; i < 6; i++) {
        size[i] = countCalc(date[i]);
        sum += countCalc(date[i]);
    }
    delete[] this->str;
    this->str = new char[sum + 7];
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
        if (i == 5) {
            sprintf(str + move, "%c", '\0');
        }
    }
    this->sizeStr = sum + 7;
}
int Date::countCalc(int num) {
    int len = 0;
    if (num == 0) return 1;
    while (num > 0) {
        len++;
        num = num / 10;
    }
    return len;
}
char* Date::GetStr() { // геттер строки
    char* cpStr = new char[sizeStr];
    for (int j = 0; j < sizeStr + 1; j++) {
        cpStr[j] = str[j];
    }
    return cpStr;
}
void Date::SetDay(int day) {
    this-> Day = day;
    ToString();
}
void Date::SetMonth(int month) {
    this-> Month = month;
    ToString();
}
void Date::SetY(int year) {
    this-> Year = year;
    ToString();
}
void Date::SetH(int hour) {
    this-> Hour = hour;
    ToString();
}
void Date::SetMinute(int minute) {
    this-> Minute = minute;
    ToString();
}
void Date::SetSecond(int second) {
    this-> Second = second;
    ToString();
}
bool Date::CheckData(int day, int month, int year)
{
    if (year < 0 || day < 1 || month < 1 || month > 12 || !(CheckDay(day, month, year)))
        return false;
    else
        return true;
}
bool Date::CheckDay(int day, int month, int year) {
    int a[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && year % 4 == 0) {
        if (day > 29) return false;
        else return true;
    } else {
        if (day > a[month]) return false;
        else return true;
    }
}
bool Date::CheckTime(int hour, int minute, int second)
{
    if (hour >= 0  && hour < 24 && minute >= 0 && minute < 60 && second >= 0 && second < 60)
        return true;
    else
        return false;
}
void Date::Plus(char k) {
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
    ToString();
}
void Date::DayPlus() {
    switch (Day) {
        case 28:
            if (Month == 2 && Year % 4 != 0) {
                Day = 1;
                Month = 3;
            } else {
                Day++;
            }
            break;
        case 29:
            if (Month == 2) {
                Day = 1;
                Month = 3;
            } else {
                Day++;
            }
            break;
        case 30:
            if (Month == 4 || Month == 6 || Month == 9 || Month == 11) {
                Day = 1;
                Month++;
            } else {
                Day++;
            }
            break;
        case 31:
            if (Month == 12) {
                Day = 1;
                Month = 1;
                Year++;
            } else {
                Month++;
                Day = 1;
            }
            break;
    }
}
void Date::HourPlus() {
    if (Day < 28) {
        Day++;
        Hour = 0;
    } else {
        DayPlus();
        Hour = 0;
    }
}
void Date::MinutePlus() {
    if (Hour < 23) {
        Minute = 0;
        Hour++;
    } else {
        Minute = 0;
        HourPlus();
    }
}
void Date::SecondPlus() {
    if (Minute < 59) {
        Second = 0;
        Minute++;
    } else {
        Second = 0;
        MinutePlus();
    }
}
void Date::Minus(char k) {
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
    ToString();
}
void Date::DayMinus() {
    if (Month == 1) {
        Year--;
        Month = 12;
        Day = 31;
    } else if (Month == 3 && Year % 4 == 0) {
        Month--;
        Day = 29;
    } else if (Month == 3) {
        Month--;
        Day = 28;
    } else if (Month == 5 || Month == 7 || Month == 10 || Month == 12) {
        Month--;
        Day = 30;
    } else {
        Month--;
        Day = 31;
    }
}
void Date::HourMinus() {
    if (Day > 1) {
        Hour = 23;
        Day--;
    } else {
        Hour = 23;
        DayMinus();
    }
}
void Date::MinuteMinus() {
    if (Hour > 0) {
        Minute = 59;
        Hour--;
    } else {
        Minute = 59;
        HourMinus();
    }
}
void Date::SecondMinus() {
    if (Minute > 0) {
        Second = 59;
        Minute--;
    } else {
        Second = 59;
        MinuteMinus();
    }
}
Date operator+(const Date &d1, const Date &d2) {
    Date temp;
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
    temp.ToString();
    return temp;
}
Date &Date::operator=(const Date &a) {
    if (this == &a) {
        return *this;
    }
    this-> Day = a.Day, this-> Month = a.Month, this-> Year = a.Year;
    this-> Hour = a.Hour, this-> Minute = a.Minute, this-> Second = a.Second;
    ToString();
    return *this;
}
Date operator-(const Date &d1, const Date &d2) {
    Date temp;
    temp.Year = d1.Year - d2.Year;
    temp.Month = d1.Month;
    int raz = 0;
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

    temp.Hour = d1.Hour;
    raz = d2.Hour;
    for (int i = 0; i < raz; i++) {
        temp.Minus('h');
    }

    temp.Minute = d1.Minute;
    raz = d2.Minute;
    for (int i = 0; i < raz; i++) {
        temp.Minus('m');
    }

    temp.Second = d1.Second;
    raz = d2.Second;
    for (int i = 0; i < raz; i++) {
        temp.Minus('s');
    }

    temp.ToString();

    return temp;
}
Date operator+(const Date &d1, int hour) {
    Date temp(d1);
    for (int i = 0; i < hour; i++) {
        temp.Plus('h');
    }
    return temp;
}
Date operator-(const Date &d1, int hour) {
    Date temp(d1);
    for (int i = 0; i < hour; i++) {
        temp.Minus('h');
    }
    return temp;
}

Date::operator char*() const { return this->str; }