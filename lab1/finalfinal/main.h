#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <iomanip>
#include <tuple>

namespace lab1 {

    class TimeSpan; 

    class Time {
    public:
        int days;
        int hours;
        int minutes;
        int seconds;

        Time(int d = 0, int h = 0, int m = 0, int s = 0);

        void normalize();
        
        TimeSpan operator-(const Time& other) const;
        TimeSpan operator-(const TimeSpan& other) const;
        Time operator+(const TimeSpan& ts) const;

        bool operator==(const Time& other) const;
        bool operator!=(const Time& other) const;
        bool operator<(const Time& other) const;
        bool operator<=(const Time& other) const;
        bool operator>(const Time& other) const;
        bool operator>=(const Time& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Time& time);
    };

    class TimeSpan {
    public:
        int days;
        int hours;
        int minutes;
        int seconds;

        TimeSpan(int d = 0, int h = 0, int m = 0, int s = 0);

        void normalize();

        TimeSpan operator+(const TimeSpan& other) const;
        TimeSpan operator-(const TimeSpan& other) const;
        TimeSpan operator-(const Time& other) const;

        bool operator==(const TimeSpan& other) const;
        bool operator!=(const TimeSpan& other) const;

        friend std::ostream& operator<<(std::ostream& os, const TimeSpan& ts);
    };

    namespace literals {
        TimeSpan operator"" _d(unsigned long long d);
        TimeSpan operator"" _h(unsigned long long h);
        TimeSpan operator"" _m(unsigned long long m);
        TimeSpan operator"" _s(unsigned long long s);
    }
}

#endif 