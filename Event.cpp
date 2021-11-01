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
        str = nullptr; eventName = nullptr; event = nullptr; ToStringEvent(); copyName();
    } else {
        Day = 1, Month = 1, Year = 2007, Hour = 0, Minute = 0, Second = 0;
        str = nullptr; eventName = nullptr; event = nullptr;
        ToStringEvent();
    }
}
Event::Event(Event &a) {
    Day = a.Day, Month = a.Month, Year = a.Year; Hour = a.Hour, Minute = a.Minute,
    Second = a.Second, eventName = a.eventName; str = nullptr; event = nullptr;
    ToStringEvent();
}
Event::~Event() {
    delete[]event; delete[]eventName; delete[]str;
}
void Event::ToStringEvent() {
    int size[6], sum = 0;
    int date[6] = { Day, Month, Year, Hour, Minute, Second };
    for (int i = 0; i < 6; i++) {
        size[i] = countCalc(date[i]); sum += countCalc(date[i]);
    }
    delete[] str; delete[] event; str = new char[sum + 6]; event = new char[sum + 26];
    int move = 0;
    for (int i = 0; i < 6; i++) {
        sprintf(str + move, "%d", date[i]); sprintf(event + move, "%d", date[i]);
        move += size[i];
        if (i < 2) {
            sprintf(str + move, "%c", '/'); sprintf(event + move, "%c", '/');
            move++;
        }
        else if (i == 2) {
            sprintf(str + move, "%c", '-'); sprintf(event + move, "%c", '-');
            move++;
        }
        else if (i < 5) {
            sprintf(str + move, "%c", ':'); sprintf(event + move, "%c", ':');
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
    char* copy = new char [strlen(event)+1];
    strcpy(copy, event);
    return copy;
}
