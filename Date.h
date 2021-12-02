//
// Created by casde on 15.10.2021.
//

#ifndef PROG2_DATE_H
#define PROG2_DATE_H

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class Date {
public:
    // конструктор по умолчанию
    Date();
    // конструктор с параметрами
    Date(int day, int month, int year, int hour, int minute, int second);
    // конструктор копирования
    Date(Date &a);
    // конструктор копирования с константным объектом
    Date(const Date& a);
    // деструктор
    ~Date();
    // метод устанавливающий значение поля день
    void SetDay(int day);
    // метод устанавливающий значение поля месяц
    void SetMonth(int month);
    // метод устанавливающий значение поля год
    void SetY(int year);
    // метод устанавливающий значение поля час
    void SetH(int hour);
    // метод устанавливающий значение поля минута
    void SetMinute(int minute);
    // метод устанавливающий значение поля секунда
    void SetSecond(int second);
    // метод увеличения полей класса на 1
    void Plus(char k);
    // метод увеличения поля день на 1
    void DayPlus();
    // метод увеличения поля час на 1
    void HourPlus();
    // метод увеличения поля минута на 1
    void MinutePlus();
    // метод увеличения поля секунда на 1
    void SecondPlus();
    // метод уменьшения полей класса на 1
    void Minus(char k);
    // метод уменьшения поля день на 1
    void DayMinus();
    // метод уменьшения поля час на 1
    void HourMinus();
    // метод уменьшения поля минута на 1
    void MinuteMinus();
    // метод уменьшения поля секунда на 1
    void SecondMinus();
    // статичный метод подсчета количества цифр в числе
    static int countCalc(int num);
    // метод заполнения строкового поля
    virtual void ToString();
    // метод получения строкового представления даты
    virtual char* GetStr();
    // оператор сложения дат
    friend Date operator+(const Date &d1, const Date &d2);
    // оператор вычитания дат
    friend Date operator-(const Date &d1, const Date &d2);
    // оператор сложения числа дней, часов
    friend Date operator+(const Date &d1, int hour);
    // оператор вычитания числа дней, часов
    friend Date operator-(const Date &d1, int hour);
    // оператор присваивания
    Date &operator=(const Date &right);
    // оператор явного преобразования к типу char*
    explicit operator char*();
    // оператор записи объекта в текстовый файл
    friend ostream& operator << (ostream& os, const Date& d);
    // оператор загрузки объекта из текстового файла
    friend istream& operator >> (istream& os, Date& d);
    // метод записи объекта в двоичный файл
    friend ofstream& BinIn (ofstream &os, Date &val);
    // метод загрузки объекта из двоичного файла
    friend ifstream& BinOut (ifstream &is, Date &val);

protected:
    // поля даты и времени: день, месяц, год, час, минута, секуда
    int Day, Month, Year, Hour, Minute, Second, sizeStr;
    // поле строкового представления даты
    char* str;
    // статический метод определения корректности даты
    static bool CheckData(int day, int month, int year);
    // статический метод определения корректности времени
    static bool CheckTime(int hour, int minute, int second);
    // статический метод определения корректности дня
    static bool CheckDay(int day, int month, int year);
};
#endif //PROG2_DATE_H
