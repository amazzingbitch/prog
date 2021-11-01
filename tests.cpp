//
// Created by casde on 15.10.2021.
//

#include "Date.h"
#include "catch.hpp"
#include "Event.h"
#include <iostream>
#include <fstream>
#include <cstring>

TEST_CASE("DateTime class tests", "[LAB1]") {
    Date a(28, 2, 2020, 23, 5, 14);
    REQUIRE(strcmp(a.GetStr(), "28/2/2020-23:5:14") == 0);
    Date b;
    REQUIRE(strcmp(b.GetStr(), "1/1/2007-0:0:0") == 0);
    Date c(b);
    REQUIRE(strcmp(b.GetStr(), c.GetStr()) == 0);

    c.Plus('y');
    REQUIRE(strcmp(c.GetStr(), "1/1/2008-0:0:0") == 0);
    c.Plus('M');
    REQUIRE(strcmp(c.GetStr(), "1/2/2008-0:0:0") == 0);
    c.Plus('d');
    REQUIRE(strcmp(c.GetStr(), "2/2/2008-0:0:0") == 0);
    c.Plus('h');
    REQUIRE(strcmp(c.GetStr(), "2/2/2008-1:0:0") == 0);
    c.Plus('m');
    REQUIRE(strcmp(c.GetStr(), "2/2/2008-1:1:0") == 0);
    c.Plus('s');
    REQUIRE(strcmp(c.GetStr(), "2/2/2008-1:1:1") == 0);

    a.Minus('y');
    REQUIRE(strcmp(a.GetStr(), "28/2/2019-23:5:14") == 0);
    a.Minus('M');
    REQUIRE(strcmp(a.GetStr(), "28/1/2019-23:5:14") == 0);
    a.Minus('d');
    REQUIRE(strcmp(a.GetStr(), "27/1/2019-23:5:14") == 0);
    a.Minus('h');
    REQUIRE(strcmp(a.GetStr(), "27/1/2019-22:5:14") == 0);
    a.Minus('m');
    REQUIRE(strcmp(a.GetStr(), "27/1/2019-22:4:14") == 0);
    a.Minus('s');
    REQUIRE(strcmp(a.GetStr(), "27/1/2019-22:4:13") == 0);

    a.SetY(1984);
    REQUIRE(strcmp(a.GetStr(), "27/1/1984-22:4:13") == 0);
    a.SetMonth(3);
    REQUIRE(strcmp(a.GetStr(), "27/3/1984-22:4:13") == 0);
    a.SetDay(15);
    REQUIRE(strcmp(a.GetStr(), "15/3/1984-22:4:13") == 0);
    a.SetH(12);
    REQUIRE(strcmp(a.GetStr(), "15/3/1984-12:4:13") == 0);
    a.SetMinute(30);
    REQUIRE(strcmp(a.GetStr(), "15/3/1984-12:30:13") == 0);
    a.SetSecond(49);
    REQUIRE(strcmp(a.GetStr(), "15/3/1984-12:30:49") == 0);
}
TEST_CASE("DateTime class tests 2", "[LAB2]") {
    Date d(22, 8, 1337, 7, 33, 1);
    Date e(1, 2, 2007, 2, 3, 4);
    Date f;
    f = d + e;
    REQUIRE(strcmp(f.GetStr(), "23/10/3344-9:36:5") == 0);

    Date h;
    h = e - d;
    REQUIRE(strcmp(h.GetStr(), "10/5/669-18:30:3") == 0);

    h = h - 48;
    REQUIRE(strcmp(h.GetStr(), "8/5/669-18:30:3") == 0);

    h = h + 4 * 24;
    REQUIRE(strcmp(h.GetStr(), "12/5/669-18:30:3") == 0);

    REQUIRE(strcmp("12/5/669-18:30:3", (char *) h) == 0);
}
TEST_CASE("DateTime class tests 3", "[LAB3]") {
    Date aa(15, 3, 1984, 12, 4, 13);
    Date bb;

    fstream file;
    file.open("../text.txt", fstream::out);
    if (!file.is_open()) {
        std::cerr << "File open error" << "\n";
        exit(1);
    }
    file << aa << endl;
    file.close();

    file.open("../text.txt", fstream::in);
    if (!file.is_open()) {
        std::cerr << "File open error" << "\n";
        exit(1);
    }
    file >> bb;
    REQUIRE(strcmp(aa.GetStr(), bb.GetStr()) == 0);
    file.close();

    Date cc(20, 3, 1984, 12, 20, 20);
    Date dd;

    ofstream bin("..\\binText.dat", ios::binary);
    if (!bin.is_open()) {
        cerr << "File open error";
        exit(1);
    }
    BinIn(bin, cc);
    bin.close();
    ifstream bin2("..\\binText.dat", ios::binary);
    if (!bin2.is_open()) {
        cerr << "File open error";
        exit(1);
    }
    BinOut(bin2, dd);
    bin2.close();
    REQUIRE(strcmp(cc.GetStr(), dd.GetStr()) == 0);
/*
    ofstream binFileIn;
    binFileIn.open("../binText.dat", ios::binary);
    if (!binFileIn.is_open()) {
        std::cerr << "File open error" << "\n";
        exit(1);
    }
    binFileIn << cc << endl;
    binFileIn.close();

    ifstream binFileOut;
    binFileOut.open("../binText.dat", ios::binary);
    if (!binFileOut.is_open()) {
        std::cerr << "File open error" << "\n";
        exit(1);
    }
    binFileOut >> dd;
    binFileOut.close();
*/
}
TEST_CASE("DateTime class tests 4", "[LAB4]") {
    Event a;
    REQUIRE(strcmp(a.GetStr(), "1/1/2007-0:0:0") == 0);
    a.SetEvent("birthday");
    REQUIRE(strcmp(a.GetEvent(), "1/1/2007-0:0:0 birthday") == 0);

    Event n(28, 2, 2020, 23, 5, 14);
    REQUIRE(strcmp(n.GetStr(), "28/2/2020-23:5:14") == 0);
    n.SetEvent("funeral");
    REQUIRE(strcmp(n.GetEvent(), "28/2/2020-23:5:14 funeral") == 0);

    Event c(n);
    REQUIRE(strcmp(n.GetStr(), c.GetStr()) == 0);
    REQUIRE(strcmp(n.GetEvent(), c.GetEvent()) == 0);
}
TEST_CASE("DateTime class tests 6", "[LAB6]") {
    Date test;
    try {
        test.SetY(-1);
    } catch (exception &ex) {
        REQUIRE(strcmp(ex.what(), "Invalid year") == 0);
    }

    try {
        test.SetMonth(14);
    } catch (exception &ex) {
        REQUIRE(strcmp(ex.what(), "Invalid month") == 0);
    }

    try {
        test.SetDay(32);
    } catch (exception &ex) {
        REQUIRE(strcmp(ex.what(), "Invalid day") == 0);
    }

    try {
        test.SetH(29);
    } catch (exception &ex) {
        REQUIRE(strcmp(ex.what(), "Invalid hour") == 0);
    }

    try {
        test.SetMinute(70);
    } catch (exception &ex) {
        REQUIRE(strcmp(ex.what(), "Invalid minute") == 0);
    }

    try {
        test.SetSecond(77);
    } catch (exception &ex) {
        REQUIRE(strcmp(ex.what(), "Invalid second") == 0);
    }

    Date test2(1, 1, 2008, 0, 0, 1);
    try {
        test2 = test - test2;
    } catch (exception &ex) {
        REQUIRE(strcmp(ex.what(), "Negative year") == 0);
    }

    Date test3(1, 1, 0, 0, 0, 0);
    try {
        test3 = test3 - 25;
    } catch (exception &ex) {
        REQUIRE(strcmp(ex.what(), "Negative year") == 0);
    }

    Event test4;
    try {
        test4.SetEvent("sweet wedding of my lovely cousin");
    } catch (exception &ex) {
        REQUIRE(strcmp(ex.what(), "Invalid length of event name") == 0);
    }
}