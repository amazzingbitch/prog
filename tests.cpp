//
// Created by casde on 15.10.2021.
//
#include "catch.hpp"
#include "Date.h"
#include "Event.h"
#include "TimeString.h"

TEST_CASE("DateTime class tests", "[LAB1]") {
    Date a(28, 2, 2020, 23, 5, 14);
    REQUIRE(strcmp(a.GetStr(), "28/2/2020 23:5:14") == 0);
    Date b;
    REQUIRE(strcmp(b.GetStr(), "1/1/2007 0:0:0") == 0);
    Date c(b);
    REQUIRE(strcmp(b.GetStr(), c.GetStr()) == 0);

    c.Plus('y');
    REQUIRE(strcmp(c.GetStr(), "1/1/2008 0:0:0") == 0);
    c.Plus('M');
    REQUIRE(strcmp(c.GetStr(), "1/2/2008 0:0:0") == 0);
    c.Plus('d');
    REQUIRE(strcmp(c.GetStr(), "2/2/2008 0:0:0") == 0);
    c.Plus('h');
    REQUIRE(strcmp(c.GetStr(), "2/2/2008 1:0:0") == 0);
    c.Plus('m');
    REQUIRE(strcmp(c.GetStr(), "2/2/2008 1:1:0") == 0);
    c.Plus('s');
    REQUIRE(strcmp(c.GetStr(), "2/2/2008 1:1:1") == 0);

    a.Minus('y');
    REQUIRE(strcmp(a.GetStr(), "28/2/2019 23:5:14") == 0);
    a.Minus('M');
    REQUIRE(strcmp(a.GetStr(), "28/1/2019 23:5:14") == 0);
    a.Minus('d');
    REQUIRE(strcmp(a.GetStr(), "27/1/2019 23:5:14") == 0);
    a.Minus('h');
    REQUIRE(strcmp(a.GetStr(), "27/1/2019 22:5:14") == 0);
    a.Minus('m');
    REQUIRE(strcmp(a.GetStr(), "27/1/2019 22:4:14") == 0);
    a.Minus('s');
    REQUIRE(strcmp(a.GetStr(), "27/1/2019 22:4:13") == 0);

    a.SetY(1984);
    REQUIRE(strcmp(a.GetStr(), "27/1/1984 22:4:13") == 0);
    a.SetMonth(3);
    REQUIRE(strcmp(a.GetStr(), "27/3/1984 22:4:13") == 0);
    a.SetDay(15);
    REQUIRE(strcmp(a.GetStr(), "15/3/1984 22:4:13") == 0);
    a.SetH(12);
    REQUIRE(strcmp(a.GetStr(), "15/3/1984 12:4:13") == 0);
    a.SetMinute(30);
    REQUIRE(strcmp(a.GetStr(), "15/3/1984 12:30:13") == 0);
    a.SetSecond(49);
    REQUIRE(strcmp(a.GetStr(), "15/3/1984 12:30:49") == 0);
}
TEST_CASE("DateTime class tests 2", "[LAB2]") {
    Date d(22, 8, 1337, 7, 33, 1);
    Date e(1, 2, 2007, 2, 3, 4);
    Date f;
    f = d + e;
    REQUIRE(strcmp(f.GetStr(), "23/10/3344 9:36:5") == 0);

    Date h;
    h = e - d;
    REQUIRE(strcmp(h.GetStr(), "10/5/669 18:30:3") == 0);

    h = h - 48;
    REQUIRE(strcmp(h.GetStr(), "8/5/669 18:30:3") == 0);

    h = h + 4 * 24;
    REQUIRE(strcmp(h.GetStr(), "12/5/669 18:30:3") == 0);

    REQUIRE(strcmp("12/5/669 18:30:3", (char *) h) == 0);
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
}
TEST_CASE("DateTime class tests 4", "[LAB4]") {
    SECTION("Event class fundamental tests") {
        Event a;
        REQUIRE(strcmp(a.GetStr(), "1/1/2007 0:0:0") == 0);
        a.SetEvent("birthday");
        REQUIRE(strcmp(a.GetEvent(), "1/1/2007 0:0:0 birthday") == 0);

        Event n(28, 2, 2020, 23, 5, 14);
        REQUIRE(strcmp(n.GetStr(), "28/2/2020 23:5:14") == 0);
        n.SetEvent("funeral");
        REQUIRE(strcmp(n.GetEvent(), "28/2/2020 23:5:14 funeral") == 0);

        Event x(8, 6, 2000, 15, 17, 0, "party");
        REQUIRE(strcmp(x.GetEvent(), "8/6/2000 15:17:0 party") == 0);

        Event c(n);
        REQUIRE(strcmp(n.GetStr(), c.GetStr()) == 0);
        REQUIRE(strcmp(n.GetEvent(), c.GetEvent()) == 0);

        a.Plus('m');
        REQUIRE(strcmp(a.GetStr(), "1/1/2007 0:1:0") == 0);
        REQUIRE(strcmp(a.GetEvent(), "1/1/2007 0:1:0 birthday") == 0);
        a.Plus('s');
        REQUIRE(strcmp(a.GetStr(), "1/1/2007 0:1:1") == 0);
        REQUIRE(strcmp(a.GetEvent(), "1/1/2007 0:1:1 birthday") == 0);

        a.Minus('y');
        REQUIRE(strcmp(a.GetStr(), "1/1/2006 0:1:1") == 0);
        REQUIRE(strcmp(a.GetEvent(), "1/1/2006 0:1:1 birthday") == 0);
        a.Minus('m');
        REQUIRE(strcmp(a.GetStr(), "1/1/2006 0:0:1") == 0);
        REQUIRE(strcmp(a.GetEvent(), "1/1/2006 0:0:1 birthday") == 0);

        a.SetDay(15);
        REQUIRE(strcmp(a.GetStr(), "15/1/2006 0:0:1") == 0);
        REQUIRE(strcmp(a.GetEvent(), "15/1/2006 0:0:1 birthday") == 0);
        a.SetH(12);
        REQUIRE(strcmp(a.GetStr(), "15/1/2006 12:0:1") == 0);
        REQUIRE(strcmp(a.GetEvent(), "15/1/2006 12:0:1 birthday") == 0);
    }
    SECTION("Event operator tests") {
        Event d(22, 8, 1337, 7, 33, 1, "meeting");
        Event e(1, 2, 2007, 2, 3, 4, "flexing");
        Event f;
        f = d + e;
        REQUIRE(strcmp(f.GetStr(), "23/10/3344 9:36:5") == 0);
        REQUIRE(strcmp(f.GetEvent(), "23/10/3344 9:36:5 meeting") == 0);

        Event h;
        h = e - d;
        REQUIRE(strcmp(h.GetStr(), "10/5/669 18:30:3") == 0);
        REQUIRE(strcmp(h.GetEvent(), "10/5/669 18:30:3 flexing") == 0);

        h = h - 48;
        REQUIRE(strcmp(h.GetStr(), "8/5/669 18:30:3") == 0);
        REQUIRE(strcmp(h.GetEvent(), "8/5/669 18:30:3 flexing") == 0);

        h = h + 4 * 24;
        REQUIRE(strcmp(h.GetStr(), "12/5/669 18:30:3") == 0);
        REQUIRE(strcmp(h.GetEvent(), "12/5/669 18:30:3 flexing") == 0);

        REQUIRE(strcmp("12/5/669 18:30:3", (char *) h) == 0);
    }
    SECTION("Event class exception tests") {
        Event test;
        Event test2(1, 1, 2008, 0, 0, 1);
        try {
            test2 = test - test2;
        } catch (exception &ex) {
            REQUIRE(strcmp(ex.what(), "Negative year") == 0);
        }

        Event test3(1, 1, 0, 0, 0, 0);
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
    SECTION("TimeString class fundamental tests") {
        TimeString d;
        REQUIRE(strcmp(d.GetStr(), "1/1/2007 0:0:0") == 0);
        REQUIRE(strcmp(d.GetTime(), "12:0:0 am") == 0);

        TimeString e(28, 2, 2020, 23, 5, 14);
        REQUIRE(strcmp(e.GetStr(), "28/2/2020 23:5:14") == 0);
        REQUIRE(strcmp(e.GetTime(), "11:5:14 pm") == 0);

        TimeString f(e);
        REQUIRE(strcmp(f.GetStr(), e.GetStr()) == 0);
        REQUIRE(strcmp(f.GetTime(), e.GetTime()) == 0);

        d.Plus('h');
        REQUIRE(strcmp(d.GetStr(), "1/1/2007 1:0:0") == 0);
        REQUIRE(strcmp(d.GetTime(), "1:0:0 am") == 0);
        d.Plus('s');
        REQUIRE(strcmp(d.GetStr(), "1/1/2007 1:0:1") == 0);
        REQUIRE(strcmp(d.GetTime(), "1:0:1 am") == 0);
        e.Minus('h');
        REQUIRE(strcmp(e.GetStr(), "28/2/2020 22:5:14") == 0);
        REQUIRE(strcmp(e.GetTime(), "10:5:14 pm") == 0);
        e.Minus('m');
        REQUIRE(strcmp(e.GetStr(), "28/2/2020 22:4:14") == 0);
        REQUIRE(strcmp(e.GetTime(), "10:4:14 pm") == 0);
        d.SetMinute(30);
        REQUIRE(strcmp(d.GetStr(), "1/1/2007 1:30:1") == 0);
        REQUIRE(strcmp(d.GetTime(), "1:30:1 am") == 0);
        d.SetSecond(49);
        REQUIRE(strcmp(d.GetStr(), "1/1/2007 1:30:49") == 0);
        REQUIRE(strcmp(d.GetTime(), "1:30:49 am") == 0);
    }
    SECTION("TimeString operator tests") {
        TimeString q(22, 8, 1337, 7, 33, 1);
        TimeString w(1, 2, 2007, 2, 3, 4);
        TimeString r;
        r = w + q;
        REQUIRE(strcmp(r.GetStr(), "23/10/3344 9:36:5") == 0);
        REQUIRE(strcmp(r.GetTime(), "9:36:5 am") == 0);

        TimeString t;
        t = w - q;
        REQUIRE(strcmp(t.GetStr(), "10/5/669 18:30:3") == 0);
        REQUIRE(strcmp(t.GetTime(), "6:30:3 pm") == 0);

        t = t - 48;
        REQUIRE(strcmp(t.GetStr(), "8/5/669 18:30:3") == 0);
        REQUIRE(strcmp(t.GetTime(), "6:30:3 pm") == 0);

        t = t + 4 * 24;
        REQUIRE(strcmp(t.GetStr(), "12/5/669 18:30:3") == 0);
        REQUIRE(strcmp(t.GetTime(), "6:30:3 pm") == 0);

        REQUIRE(strcmp("12/5/669 18:30:3", (char *) t) == 0);
    }
    SECTION("TimeString exception tests") {
        TimeString test1_0;
        TimeString test1_2(1, 1, 2008, 0, 0, 1);
        try {
            test1_2 = test1_0 - test1_2;
        } catch (exception &ex) {
            REQUIRE(strcmp(ex.what(), "Negative year") == 0);
        }

        TimeString test1_3(1, 1, 0, 0, 0, 0);
        try {
            test1_3 = test1_3 - 25;
        } catch (exception &ex) {
            REQUIRE(strcmp(ex.what(), "Negative year") == 0);
        }
    }
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
}
