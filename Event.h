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
    Event(int day, int month, int year, int hour, int minute, int second, const char* name);
    Event(Event &a);
    Event(const Event &a);
    ~Event();
    void ToStringEvent();
    void SetEvent(const char* name);
    char* GetEvent();
    void ToString() override;
    friend Event operator+(const Event &d1, const Event &d2);
    friend Event operator-(const Event &d1, const Event &d2);
    friend Event operator+(const Event &d1, int hour);
    friend Event operator-(const Event &d1, int hour);
    Event &operator=(const Event &right);

protected:
    char* event; char* eventName;
};

#endif //DATE_CPP_EVENT_H
