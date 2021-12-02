//
// Created by casde on 01.11.2021.
//
#ifndef DATE_CPP_EVENT_H
#define DATE_CPP_EVENT_H

#include "Date.h"

class Event : public Date {
public:
    // конструктор по умолчанию
    Event();
    // конструктор с параметрами
    Event(int day, int month, int year, int hour, int minute, int second);
    // конструктор с параметрами
    Event(int day, int month, int year, int hour, int minute, int second, const char* name);
    // конструктор копирования
    Event(Event &a);
    // конструктор копирования с константным объектом
    Event(const Event &a);
    // деструктор
    ~Event();
    // метод заполнения строковых полей, для конструкторов
    void ToStringEvent();
    // метод устанавливающий значение названия мероприятия
    void SetEvent(const char* name);
    // метод получения строкового представления даты и времени
    char* GetStrDate();
    // метод получения строкого представления даты, времени и мероприятия
    char* GetStr() override;
    // метод заполнения строковых полей
    void ToString() override;
    // оператор сложения дат
    friend Event operator+(const Event &d1, const Event &d2);
    // оператор вычитания дат
    friend Event operator-(const Event &d1, const Event &d2);
    // оператор сложения числа дней, часов
    friend Event operator+(const Event &d1, int hour);
    // оператор вычитания числа дней, часов
    friend Event operator-(const Event &d1, int hour);
    // оператор присваивания
    Event &operator=(const Event &right);

protected:
    // поле строкового представления даты, времени и названия мероприятия
    char* event;
    // поле для названия мероприятия
    char* eventName;
};

#endif //DATE_CPP_EVENT_H
