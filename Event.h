//
// Created by casde on 01.11.2021.
//

#ifndef DATE_CPP_EVENT_H
#define DATE_CPP_EVENT_H

#include "Date.h"

class Event : public Date {
public:
    Event();
    Event(int day, int month, int year, int hour, int minute, int second);
    Event(Event &a);
    Event(const Event &a);
    ~Event();

protected:
    char* event;

};

#endif //DATE_CPP_EVENT_H
