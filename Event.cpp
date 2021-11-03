//
// Created by casde on 01.11.2021.
//
#include "Event.h"

Event::Event() : Date() {
    event = nullptr; eventName = nullptr; ToStringEvent();
}
Event::Event(int day, int month, int year, int hour, int minute, int second) {
    if (CheckTime(hour, minute, second) && CheckData(day, month, year)) {
        Day = day, Month = month, Year = year; Hour = hour, Minute = minute, Second = second;
        str = nullptr; eventName = nullptr; event = nullptr; ToString(); ToStringEvent();
    } else {
        Day = 1, Month = 1, Year = 2007, Hour = 0, Minute = 0, Second = 0;
        str = nullptr; eventName = nullptr; event = nullptr; ToString(); ToStringEvent();
    }
}
Event::Event(Event &a) : Date (a) { eventName = a.eventName; event = nullptr; ToStringEvent(); }
Event::Event(const Event &a) : Date (a) { eventName = a.eventName; event = nullptr; ToStringEvent(); }
Event::~Event() { delete[]event; delete[]eventName; delete[]str; }
void Event::ToStringEvent() {
    int size[6], sum = 0;
    int date[6] = { Day, Month, Year, Hour, Minute, Second };
    for (int i = 0; i < 6; i++) {
        size[i] = countCalc(date[i]); sum += countCalc(date[i]);
    }
    delete[] event; event = new char[sum + 26];
    int move = 0;
    for (int i = 0; i < 6; i++) {
        sprintf(event + move, "%d", date[i]);
        move += size[i];
        if (i < 2) {
            sprintf(event + move, "%c", '/');
            move++;
        }
        else if (i == 2) {
            sprintf(event + move, "%c", '-');
            move++;
        }
        else if (i < 5) {
            sprintf(event + move, "%c", ':');
            move++;
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
        strcpy(eventName, name); ToStringEvent();
    }
}
char* Event::GetEvent() {
    char* copy = new char [strlen(event)+1]; strcpy(copy, event); return copy;
}
void Event::SetDay(int day) {
    if (CheckDay(day, Month, Year)) {
        Day = day;
        ToString(); ToStringEvent();
    } else {
        throw invalid_argument("Invalid day");
    }
}
void Event::SetMonth(int month) {
    if (month > 0 && month < 13) {
        Month = month;
        ToString(); ToStringEvent();
    } else {
        throw invalid_argument("Invalid month");
    }
}
void Event::SetY(int year) {
    if (year >= 0) {
        Year = year;
        ToString(); ToStringEvent();
    } else {
        throw invalid_argument("Invalid year");
    }
}
void Event::SetH(int hour) {
    if (hour < 24 && hour >= 0) {
        Hour = hour;
        ToString(); ToStringEvent();
    } else {
        throw invalid_argument("Invalid hour");
    }
}
void Event::SetMinute(int minute) {
    if (minute < 60 && minute >= 0) {
        Minute = minute;
        ToString(); ToStringEvent();
    } else {
        throw invalid_argument("Invalid minute");
    }
}
void Event::SetSecond(int second) {
    if (second < 60 && second >= 0) {
        Second = second;
        ToString(); ToStringEvent();
    } else {
        throw invalid_argument("Invalid second");
    }
}

void Event::Plus(char k) {
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
    ToString(); ToStringEvent();
}

void Event::Minus(char k) {
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
    ToString(); ToStringEvent();
}
Event operator+(const Event &d1, const Event &d2) {
    Event temp;
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
    temp.ToStringEvent();
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
    if (d1.Year < d2.Year) {
        //temp.Year = 1;
        throw invalid_argument("Negative year");
    } else {
        temp.Year = d1.Year - d2.Year;
    }
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
    temp.ToStringEvent();

    return temp;
}

istream &operator>>(istream &is, Event &d) {
    //is >> d.str;
    /*stringstream ss;
    ss << d.str;*/
    is >> d.Day;
    is.ignore(256, '/');
    //cout << d.Day << endl;
    is >> d.Month;
    is.ignore(256, '/');
    is >> d.Year;
    is.ignore(256, '-');
    is >> d.Hour;
    is.ignore(256, ':');
    is >> d.Minute;
    is.ignore(256, ':');
    is >> d.Second;

    d.ToString(); d.ToStringEvent();
    return is;
}
ifstream& BinOut (ifstream& in, Event& p) {
    in.read((char*)&p.Day, sizeof(int));
    in.read((char*)&p.Month, sizeof(int));
    in.read((char*)&p.Year, sizeof(int));
    in.read((char*)&p.Hour, sizeof(int));
    in.read((char*)&p.Minute, sizeof(int));
    in.read((char*)&p.Second, sizeof(int));
    p.ToString(); p.ToStringEvent();
    return in;
}