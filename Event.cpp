//
// Created by casde on 01.11.2021.
//
#include "Event.h"

Event::Event() : Date() { event = nullptr; eventName = nullptr; ToStringEvent(); }
Event::Event(int day, int month, int year, int hour, int minute, int second) {
    if (CheckTime(hour, minute, second) && CheckData(day, month, year)) {
        Day = day, Month = month, Year = year; Hour = hour, Minute = minute, Second = second;
        str = nullptr; eventName = nullptr; event = nullptr; ToStringEvent();
    } else {
        Day = 1, Month = 1, Year = 2007, Hour = 0, Minute = 0, Second = 0;
        str = nullptr; eventName = nullptr; event = nullptr; ToStringEvent();
    }
}
Event::Event(int day, int month, int year, int hour, int minute, int second, const char* name) {
    if (CheckTime(hour, minute, second) && CheckData(day, month, year)) {
        Day = day, Month = month, Year = year; Hour = hour, Minute = minute, Second = second;
        str = nullptr; eventName = (char*)name; event = nullptr; ToStringEvent();
    } else {
        Day = 1, Month = 1, Year = 2007, Hour = 0, Minute = 0, Second = 0;
        str = nullptr; eventName = (char*)name; event = nullptr; ToStringEvent();
    }
}
Event::Event(Event &a) : Date (a) { eventName = a.eventName; event = nullptr; ToStringEvent(); }
Event::Event(const Event &a) : Date (a) { eventName = a.eventName; event = nullptr; ToStringEvent(); }
Event::~Event() { delete[]event; delete[]eventName; }
void Event::ToString() {
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
    int size2[6], sum2 = 0;
    int date2[6] = { Day, Month, Year, Hour, Minute, Second };
    for (int i = 0; i < 6; i++) {
        size2[i] = countCalc(date2[i]); sum2 += countCalc(date2[i]);
    }
    delete[] event; event = new char[sum2 + 26];
    int move2 = 0;
    for (int i = 0; i < 6; i++) {
        sprintf(event + move2, "%d", date2[i]);
        move2 += size2[i];
        if (i < 2) {
            sprintf(event + move2, "%c", '/');
            move2++;
        }
        else if (i == 2) {
            sprintf(event + move2, "%c", ' ');
            move2++;
        }
        else if (i < 5) {
            sprintf(event + move2, "%c", ':');
            move2++;
        }
    }
    if (eventName != nullptr) {
        sprintf(event + strlen(str), "%c", ' '); int j = 0;
        for (int i = (int)strlen(str) + 1; i < strlen(eventName) + strlen(str) + 2; i++) {
            event[i] = eventName[j]; j++;
        }
    }
}
void Event::ToStringEvent() {
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
    int size2[6], sum2 = 0;
    int date2[6] = { Day, Month, Year, Hour, Minute, Second };
    for (int i = 0; i < 6; i++) {
        size2[i] = countCalc(date2[i]); sum2 += countCalc(date2[i]);
    }
    delete[] event; event = new char[sum2 + 26];
    int move2 = 0;
    for (int i = 0; i < 6; i++) {
        sprintf(event + move2, "%d", date2[i]);
        move2 += size2[i];
        if (i < 2) {
            sprintf(event + move2, "%c", '/');
            move2++;
        }
        else if (i == 2) {
            sprintf(event + move2, "%c", ' ');
            move2++;
        }
        else if (i < 5) {
            sprintf(event + move2, "%c", ':');
            move2++;
        }
    }
    if (eventName != nullptr) {
        sprintf(event + strlen(str), "%c", ' '); int j = 0;
        for (int i = (int)strlen(str) + 1; i < strlen(eventName) + strlen(str) + 2; i++) {
            event[i] = eventName[j]; j++;
        }
    }
}
void Event::SetEvent(const char* name) {
    if (strlen(name) > 20) {
        throw invalid_argument("Invalid length of event name");
    } else {
        delete[]eventName; eventName = new char [strlen(name)+1];
        strcpy(eventName, name); ToString();
    }
}
char* Event::GetEvent() { char* copy = new char [strlen(event)+1]; strcpy(copy, event); return copy; }
Event operator+(const Event &d1, const Event &d2) {
    Event temp; int month, day, hour, min, sec;
    temp.eventName = d1.eventName;
    temp.Year = d1.Year + d2.Year; month = d1.Month + d2.Month;
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
Event &Event::operator=(const Event &a) {
    if (this == &a) {
        return *this;
    }
    Day = a.Day,  Month = a.Month,  Year = a.Year;
    Hour = a.Hour,  Minute = a.Minute,  Second = a.Second; eventName = a.eventName;
    ToString(); ToStringEvent();
    return *this;
}
Event operator-(const Event &d1, const Event &d2) {
    Event temp;
    temp.eventName = d1.eventName;
    if (d1.Year < d2.Year) {
        throw invalid_argument("Negative year");
    } else {
        temp.Year = d1.Year - d2.Year;
    }
    temp.Month = d1.Month;
    int raz;
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
Event operator+(const Event &d1, int hour) {
    Event temp(d1);
    for (int i = 0; i < hour; i++) {
        temp.Plus('h');
    }
    return temp;
}
Event operator-(const Event &d1, int hour) {
    Event temp(d1);
    for (int i = 0; i < hour; i++) {
        if (temp.Year == 0 && temp.Month == 1 && temp.Day == 1 && temp.Hour == 0 && temp.Minute == 0 && temp.Second == 0)
            throw invalid_argument("Negative year");
        temp.Minus('h');
    }
    return temp;
}
