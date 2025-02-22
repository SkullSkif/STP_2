#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <iomanip>
#include <tuple>

namespace your_namespace {

    class TimeSpan; // Предварительное объявление класса TimeSpan

    class Time {
    public:
        int hours;
        int minutes;
        int seconds;

        Time(int h = 0, int m = 0, int s = 0);

        void normalize();
        
        Time operator-(const Time& other) const;
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

        bool operator==(const TimeSpan& other) const;
        bool operator!=(const TimeSpan& other) const;

        friend std::ostream& operator<<(std::ostream& os, const TimeSpan& ts);
    };

    namespace literals {
        constexpr TimeSpan operator"" _d(unsigned long long d);
        constexpr TimeSpan operator"" _h(unsigned long long h);
        constexpr TimeSpan operator"" _m(unsigned long long m);
        constexpr TimeSpan operator"" _s(unsigned long long s);
    }
}

#endif // TIME_H
