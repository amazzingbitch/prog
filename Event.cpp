//
// Created by casde on 01.11.2021.
//

#include <cstring>
#include <fstream>
#include "Event.h"
#include <string.h>

Event::Event() {
    Day = 1, Month = 1, Year = 2007,
    Hour = 0, Minute = 0, Second = 0;
    this->str = nullptr;
    sizeStr = 0;
    ToString();
}
Event::Event(int day, int month, int year, int hour, int minute, int second) {
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
Event::Event(Event &a) {
    this-> Day = a.Day, this-> Month = a.Month, this-> Year = a.Year;
    this-> Hour = a.Hour, this-> Minute = a.Minute, this-> Second = a.Second;
    this->str = nullptr; this->sizeStr = 0;
    ToString();
}
Event::Event(const Event &a) {
    this-> Day = a.Day, this-> Month = a.Month, this-> Year = a.Year;
    this-> Hour = a.Hour, this-> Minute = a.Minute, this-> Second = a.Second;
    this->str = nullptr; this->sizeStr = 0;
    ToString();
}
Event::~Event() {
    delete[]this->str;
}