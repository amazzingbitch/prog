//
// Created by casde on 15.10.2021.
//
#include "catch.hpp"
#include "Date.h"
#include "Event.h"
#include "TimeString.h"
#include "List.h"
#include <map>
#include <vector>
#include <ctime>
#include <cstdlib>

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

        a.Plus('y');
        REQUIRE(strcmp(a.GetStr(), "1/1/2008 0:0:0") == 0);
        REQUIRE(strcmp(a.GetEvent(), "1/1/2008 0:0:0 birthday") == 0);
        a.Plus('M');
        REQUIRE(strcmp(a.GetStr(), "1/2/2008 0:0:0") == 0);
        REQUIRE(strcmp(a.GetEvent(), "1/2/2008 0:0:0 birthday") == 0);
        a.Plus('d');
        REQUIRE(strcmp(a.GetStr(), "2/2/2008 0:0:0") == 0);
        REQUIRE(strcmp(a.GetEvent(), "2/2/2008 0:0:0 birthday") == 0);
        a.Plus('h');
        REQUIRE(strcmp(a.GetStr(), "2/2/2008 1:0:0") == 0);
        REQUIRE(strcmp(a.GetEvent(), "2/2/2008 1:0:0 birthday") == 0);
        a.Plus('m');
        REQUIRE(strcmp(a.GetStr(), "2/2/2008 1:1:0") == 0);
        REQUIRE(strcmp(a.GetEvent(), "2/2/2008 1:1:0 birthday") == 0);
        a.Plus('s');
        REQUIRE(strcmp(a.GetStr(), "2/2/2008 1:1:1") == 0);
        REQUIRE(strcmp(a.GetEvent(), "2/2/2008 1:1:1 birthday") == 0);

        a.Minus('y');
        REQUIRE(strcmp(a.GetStr(), "2/2/2007 1:1:1") == 0);
        REQUIRE(strcmp(a.GetEvent(), "2/2/2007 1:1:1 birthday") == 0);
        a.Minus('M');
        REQUIRE(strcmp(a.GetStr(), "2/1/2007 1:1:1") == 0);
        REQUIRE(strcmp(a.GetEvent(), "2/1/2007 1:1:1 birthday") == 0);
        a.Minus('d');
        REQUIRE(strcmp(a.GetStr(), "1/1/2007 1:1:1") == 0);
        REQUIRE(strcmp(a.GetEvent(), "1/1/2007 1:1:1 birthday") == 0);
        a.Minus('h');
        REQUIRE(strcmp(a.GetStr(), "1/1/2007 0:1:1") == 0);
        REQUIRE(strcmp(a.GetEvent(), "1/1/2007 0:1:1 birthday") == 0);
        a.Minus('m');
        REQUIRE(strcmp(a.GetStr(), "1/1/2007 0:0:1") == 0);
        REQUIRE(strcmp(a.GetEvent(), "1/1/2007 0:0:1 birthday") == 0);
        a.Minus('s');
        REQUIRE(strcmp(a.GetStr(), "1/1/2007 0:0:0") == 0);
        REQUIRE(strcmp(a.GetEvent(), "1/1/2007 0:0:0 birthday") == 0);

        a.SetY(1984);
        REQUIRE(strcmp(a.GetStr(), "1/1/1984 0:0:0") == 0);
        REQUIRE(strcmp(a.GetEvent(), "1/1/1984 0:0:0 birthday") == 0);
        a.SetMonth(3);
        REQUIRE(strcmp(a.GetStr(), "1/3/1984 0:0:0") == 0);
        REQUIRE(strcmp(a.GetEvent(), "1/3/1984 0:0:0 birthday") == 0);
        a.SetDay(15);
        REQUIRE(strcmp(a.GetStr(), "15/3/1984 0:0:0") == 0);
        REQUIRE(strcmp(a.GetEvent(), "15/3/1984 0:0:0 birthday") == 0);
        a.SetH(12);
        REQUIRE(strcmp(a.GetStr(), "15/3/1984 12:0:0") == 0);
        REQUIRE(strcmp(a.GetEvent(), "15/3/1984 12:0:0 birthday") == 0);
        a.SetMinute(30);
        REQUIRE(strcmp(a.GetStr(), "15/3/1984 12:30:0") == 0);
        REQUIRE(strcmp(a.GetEvent(), "15/3/1984 12:30:0 birthday") == 0);
        a.SetSecond(49);
        REQUIRE(strcmp(a.GetStr(), "15/3/1984 12:30:49") == 0);
        REQUIRE(strcmp(a.GetEvent(), "15/3/1984 12:30:49 birthday") == 0);
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
    SECTION("Event input/output tests") {
        Event a1(15, 3, 1984, 12, 4, 13, "chill");
        Event b1;

        fstream file;
        file.open("../text3.txt", fstream::out);
        if (!file.is_open()) {
            std::cerr << "File open error" << "\n";
            exit(1);
        }
        file << a1 << endl;
        file.close();

        file.open("../text3.txt", fstream::in);
        if (!file.is_open()) {
            std::cerr << "File open error" << "\n";
            exit(1);
        }
        file >> b1;
        REQUIRE(strcmp(a1.GetStr(), b1.GetStr()) == 0);
        REQUIRE(strcmp(a1.GetEvent(), b1.GetEvent()) == 0);
        file.close();

        Event c1(20, 3, 1984, 12, 20, 20, "concert");
        Event d1;

        ofstream bin("..\\binText3.dat", ios::binary);
        if (!bin.is_open()) {
            cerr << "File open error";
            exit(1);
        }
        BinIn(bin, c1);
        bin.close();
        ifstream bin2("..\\binText3.dat", ios::binary);
        if (!bin2.is_open()) {
            cerr << "File open error";
            exit(1);
        }
        BinOut(bin2, d1);
        bin2.close();
        REQUIRE(strcmp(c1.GetStr(), d1.GetStr()) == 0);
        REQUIRE(strcmp(c1.GetEvent(), d1.GetEvent()) == 0);
    }
    SECTION("Event class exception tests") {
        Event test;
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

        d.Plus('y');
        REQUIRE(strcmp(d.GetStr(), "1/1/2008 0:0:0") == 0);
        d.Plus('M');
        REQUIRE(strcmp(d.GetStr(), "1/2/2008 0:0:0") == 0);
        d.Plus('d');
        REQUIRE(strcmp(d.GetStr(), "2/2/2008 0:0:0") == 0);
        d.Plus('h');
        REQUIRE(strcmp(d.GetStr(), "2/2/2008 1:0:0") == 0);
        REQUIRE(strcmp(d.GetTime(), "1:0:0 am") == 0);
        d.Plus('m');
        REQUIRE(strcmp(d.GetStr(), "2/2/2008 1:1:0") == 0);
        REQUIRE(strcmp(d.GetTime(), "1:1:0 am") == 0);
        d.Plus('s');
        REQUIRE(strcmp(d.GetStr(), "2/2/2008 1:1:1") == 0);
        REQUIRE(strcmp(d.GetTime(), "1:1:1 am") == 0);

        d.Minus('y');
        REQUIRE(strcmp(d.GetStr(), "2/2/2007 1:1:1") == 0);
        d.Minus('M');
        REQUIRE(strcmp(d.GetStr(), "2/1/2007 1:1:1") == 0);
        d.Minus('d');
        REQUIRE(strcmp(d.GetStr(), "1/1/2007 1:1:1") == 0);
        d.Minus('h');
        REQUIRE(strcmp(d.GetStr(), "1/1/2007 0:1:1") == 0);
        REQUIRE(strcmp(d.GetTime(), "12:1:1 am") == 0);
        d.Minus('m');
        REQUIRE(strcmp(d.GetStr(), "1/1/2007 0:0:1") == 0);
        REQUIRE(strcmp(d.GetTime(), "12:0:1 am") == 0);
        d.Minus('s');
        REQUIRE(strcmp(d.GetStr(), "1/1/2007 0:0:0") == 0);
        REQUIRE(strcmp(d.GetTime(), "12:0:0 am") == 0);

        d.SetY(1984);
        REQUIRE(strcmp(d.GetStr(), "1/1/1984 0:0:0") == 0);
        d.SetMonth(3);
        REQUIRE(strcmp(d.GetStr(), "1/3/1984 0:0:0") == 0);
        d.SetDay(15);
        REQUIRE(strcmp(d.GetStr(), "15/3/1984 0:0:0") == 0);
        d.SetH(12);
        REQUIRE(strcmp(d.GetStr(), "15/3/1984 12:0:0") == 0);
        REQUIRE(strcmp(d.GetTime(), "12:0:0 pm") == 0);
        d.SetMinute(30);
        REQUIRE(strcmp(d.GetStr(), "15/3/1984 12:30:0") == 0);
        REQUIRE(strcmp(d.GetTime(), "12:30:0 pm") == 0);
        d.SetSecond(49);
        REQUIRE(strcmp(d.GetStr(), "15/3/1984 12:30:49") == 0);
        REQUIRE(strcmp(d.GetTime(), "12:30:49 pm") == 0);
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
    SECTION("TimeString input/output tests") {
        TimeString aa(15, 3, 1984, 12, 4, 13);
        TimeString bb;

        fstream file;
        file.open("../text2.txt", fstream::out);
        if (!file.is_open()) {
            std::cerr << "File open error" << "\n";
            exit(1);
        }
        file << aa << endl;
        file.close();

        file.open("../text2.txt", fstream::in);
        if (!file.is_open()) {
            std::cerr << "File open error" << "\n";
            exit(1);
        }
        file >> bb;
        REQUIRE(strcmp(aa.GetStr(), bb.GetStr()) == 0);
        REQUIRE(strcmp(aa.GetTime(), bb.GetTime()) == 0);
        file.close();

        TimeString cc(20, 3, 1984, 12, 20, 20);
        TimeString dd;

        ofstream bin("..\\binText2.dat", ios::binary);
        if (!bin.is_open()) {
            cerr << "File open error";
            exit(1);
        }
        BinIn(bin, cc);
        bin.close();
        ifstream bin2("..\\binText2.dat", ios::binary);
        if (!bin2.is_open()) {
            cerr << "File open error";
            exit(1);
        }
        BinOut(bin2, dd);
        bin2.close();
        REQUIRE(strcmp(cc.GetStr(), dd.GetStr()) == 0);
        REQUIRE(strcmp(cc.GetTime(), dd.GetTime()) == 0);
    }
    SECTION("TimeString exception tests") {
        TimeString test1_0;
        try {
            test1_0.SetY(-1);
        } catch (exception &ex) {
            REQUIRE(strcmp(ex.what(), "Invalid year") == 0);
        }

        try {
            test1_0.SetMonth(14);
        } catch (exception &ex) {
            REQUIRE(strcmp(ex.what(), "Invalid month") == 0);
        }

        try {
            test1_0.SetDay(32);
        } catch (exception &ex) {
            REQUIRE(strcmp(ex.what(), "Invalid day") == 0);
        }

        try {
            test1_0.SetH(29);
        } catch (exception &ex) {
            REQUIRE(strcmp(ex.what(), "Invalid hour") == 0);
        }

        try {
            test1_0.SetMinute(70);
        } catch (exception &ex) {
            REQUIRE(strcmp(ex.what(), "Invalid minute") == 0);
        }

        try {
            test1_0.SetSecond(77);
        } catch (exception &ex) {
            REQUIRE(strcmp(ex.what(), "Invalid second") == 0);
        }

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
TEST_CASE("DateTime class tests 5", "[LAB5]") {
    Date a;
    Event b(28, 2, 2000, 23, 5, 14, "family dinner");
    TimeString c(28, 2, 2020, 23, 5, 14);
    List <Date> Lst;
    Lst.Push(a);
    Lst.Push(b);
    REQUIRE(strcmp(Lst[1].GetStr(), "1/1/2007 0:0:0") == 0);
    REQUIRE(strcmp(Lst[0].GetStr(), "28/2/2000 23:5:14") == 0);
    Lst.Pop();
    Lst.Push(c);
    REQUIRE(strcmp(Lst[0].GetStr(), "28/2/2020 23:5:14") == 0);
    try {
        Lst[2];
    } catch (exception &ex) {
        REQUIRE(strcmp(ex.what(), "Invalid index") == 0);
    }
    List <Date> Lst2;
    try {
        Lst2[0];
    } catch (exception &ex) {
        REQUIRE(strcmp(ex.what(), "Invalid index") == 0);
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
TEST_CASE("DateTime class tests 7", "[LAB7]") {
    SECTION("Templates <int>") {
        List <int> q1;
        int n1 = 5, n2 = 1, n3 = 9;

        q1.Push(n1);
        q1.Push(n2);
        q1.Push(n3);

        REQUIRE(q1[0] == 9);
        REQUIRE(q1[1] == 1);
        REQUIRE(q1[2] == 5);

        q1.Pop();
        REQUIRE(q1[0] == 1);
    }

    SECTION("Templates <float>") {
        List <float> q2;
        float n1 = 6.6, n2 = 8.4, n3 = 2.8;

        q2.Push(n1);
        q2.Push(n2);
        q2.Push(n3);

        REQUIRE(q2[0] == 2.8f);
        REQUIRE(q2[1] == 8.4f);
        REQUIRE(q2[2] == 6.6f);

        q2.Pop();
        REQUIRE(q2[0] == 8.4f);
    }

    SECTION("Templates <char>") {
        List <char> q3;
        char n1 = 'c', n2 = 'a', n3 = 't';

        q3.Push(n1);
        q3.Push(n2);
        q3.Push(n3);

        REQUIRE(q3[0] == 't');
        REQUIRE(q3[1] == 'a');
        REQUIRE(q3[2] == 'c');

        q3.Pop();
        REQUIRE(q3[0] == 'a');
    }
}
TEST_CASE("DateTime class tests 8", "[LAB8]") {
    SECTION("STL: map") {
        cout << "Map" << endl;
        map<int, int> m;
        m.insert(make_pair(1, 1));
        REQUIRE(m[1] == 1);
        srand(time(nullptr));
        int start = clock();
        for (int i = 0; i < 10000; ++i) {
            m.insert(make_pair(i, rand() % 10000));
        }
        cout << "Add : " << clock() - start << endl;
        start = clock();
        for (int i = 0; i < 10000; ++i) {
            m.find(i);
        }
        cout << "Find : " << clock() - start << endl;
    }
}