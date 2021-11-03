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
    void SetDay(int day) override;
    void SetMonth(int month) override;
    void SetY(int year) override;
    void SetH(int hour) override;
    void SetMinute(int minute) override;
    void SetSecond(int second) override;
    void Plus(char k) override;
    void Minus(char k) override;
    friend Event operator+(const Event &d1, const Event &d2);
    friend Event operator-(const Event &d1, const Event &d2);
    friend Event operator+(const Event &d1, int hour);
    friend Event operator-(const Event &d1, int hour);
    Event &operator=(const Event &right);
    friend istream& operator >> (istream& os, Event& d);
    friend ostream& operator << (ostream& os, const Event& d);
    friend ifstream& BinOut (ifstream &is, Event &val);
    friend ofstream& BinIn (ofstream &os, Event &val);

protected:
    char* event; char* eventName;
};

#endif //DATE_CPP_EVENT_H
