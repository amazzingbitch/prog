#ifndef PROG2_DATE_H
#define PROG2_DATE_H
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;
class Date {
public:
    Date();
    Date(int day, int month, int year, int hour, int minute, int second);
    Date(Date &a);
    Date(const Date &a);
    ~Date();
    void SetDay(int day);
    void SetMonth(int month);
    void SetY(int year);
    void SetH(int hour);
    void SetMinute(int minute);
    void SetSecond(int second);
    void Plus(char k);
    void DayPlus();
    void HourPlus();
    void MinutePlus();
    void SecondPlus();
    void Minus(char k);
    void DayMinus();
    void HourMinus();
    void MinuteMinus();
    void SecondMinus();
    static int countCalc(int num);
    void ToString();
    char* GetStr();
    friend Date operator+(const Date &d1, const Date &d2);
    friend Date operator-(const Date &d1, const Date &d2);
    friend Date operator+(const Date &d1, int hour);
    friend Date operator-(const Date &d1, int hour);
    Date &operator=(const Date &right);
    explicit operator char *() const;
    friend ostream& operator << (ostream& os, const Date& d);
    friend istream& operator >> (istream& os, Date& d);
    friend ofstream& BinIn (ofstream &os, Date &val);
    friend ifstream& BinOut (ifstream &is, Date &val);

private:
    int Day, Month, Year, Hour, Minute, Second;
    char* str;
    static bool CheckData(int day, int month, int year);
    static bool CheckTime(int hour, int minute, int second);
    static bool CheckDay(int day, int month, int year);
};
#endif //PROG2_DATE_H
