#include <iostream>
#include <iomanip>
#include <chrono>
#include "main.h"

namespace your_namespace {
    class Time {
    public:
        int hours;
        int minutes;
        int seconds;

        Time(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {
            normalize();
        }

        void normalize() {
            if (seconds >= 60) {
                minutes += seconds / 60;
                seconds %= 60;
            }
            if (minutes >= 60) {
                hours += minutes / 60;
                minutes %= 60;
            }
        }

        Time operator-(const Time& other) const {
            return Time(hours - other.hours, minutes - other.minutes, seconds - other.seconds);
        }

        TimeSpan operator-(const TimeSpan& other) const;

        Time operator+(const TimeSpan& ts) const;

        bool operator==(const Time& other) const {
            return hours == other.hours && minutes == other.minutes && seconds == other.seconds;
        }

        bool operator!=(const Time& other) const {
            return !(*this == other);
        }

        bool operator<(const Time& other) const {
            return std::tie(hours, minutes, seconds) < std::tie(other.hours, other.minutes, other.seconds);
        }

        bool operator<=(const Time& other) const {
            return *this < other || *this == other;
        }

        bool operator>(const Time& other) const {
            return !(*this <= other);
        }

        bool operator>=(const Time& other) const {
            return !(*this < other);
        }

        friend std::ostream& operator<<(std::ostream& os, const Time& time) {
            return os << std::setfill('0') << std::setw(2) << time.hours << "h "
                      << std::setw(2) << time.minutes << "m "
                      << std::setw(2) << time.seconds << "s";
        }
    };

    class TimeSpan {
    public:
        int days;
        int hours;
        int minutes;
        int seconds;

        TimeSpan(int d = 0, int h = 0, int m = 0, int s = 0)
            : days(d), hours(h), minutes(m), seconds(s) {
            normalize();
        }

        void normalize() {
            if (seconds >= 60) {
                minutes += seconds / 60;
                seconds %= 60;
            }
            if (minutes >= 60) {
                hours += minutes / 60;
                minutes %= 60;
            }
            if (hours >= 24) {
                days += hours / 24;
                hours %= 24;
            }
        }

        TimeSpan operator+(const TimeSpan& other) const {
            return TimeSpan(days + other.days, hours + other.hours, minutes + other.minutes, seconds + other.seconds);
        }

        TimeSpan operator-(const TimeSpan& other) const {
            return TimeSpan(days - other.days, hours - other.hours, minutes - other.minutes, seconds - other.seconds);
        }

        bool operator==(const TimeSpan& other) const {
            return days == other.days && hours == other.hours && minutes == other.minutes && seconds == other.seconds;
        }

        bool operator!=(const TimeSpan& other) const {
            return !(*this == other);
        }

        friend std::ostream& operator<<(std::ostream& os, const TimeSpan& ts) {
            return os << std::setfill('0') << std::setw(2) << ts.days << "d "
                      << std::setw(2) << ts.hours << "h "
                      << std::setw(2) << ts.minutes << "m "
                      << std::setw(2) << ts.seconds << "s";
        }
    };

    // Перегрузка операторов для работы с классами
    TimeSpan Time::operator-(const Time& other) const {
        return TimeSpan(0, hours - other.hours, minutes - other.minutes, seconds - other.seconds);
    }

    Time Time::operator+(const TimeSpan& ts) const {
        return Time(hours + ts.hours + (ts.days * 24), minutes + ts.minutes, seconds + ts.seconds);
    }

    // Пользовательские литералы
    namespace literals {
        constexpr TimeSpan operator"" _d(unsigned long long d) {
            return TimeSpan(d);
        }
        
        constexpr TimeSpan operator"" _h(unsigned long long h) {
            return TimeSpan(0, h);
        }
        
        constexpr TimeSpan operator"" _m(unsigned long long m) {
            return TimeSpan(0, 0, m);
        }
        
        constexpr TimeSpan operator"" _s(unsigned long long s) {
            return TimeSpan(0, 0, 0, s);
        }
    }
}

int main() {
    using namespace your_namespace;
    using namespace your_namespace::literals;

    Time t1(1, 30, 45); // 1h 30m 45s
    Time t2(0, 45, 15); // 0h 45m 15s

    TimeSpan ts1 = t1 - t2; // Разница времени
    std::cout << "Time Span: " << ts1 << std::endl;

    Time t3 = t1 + ts1; // Время после добавления интервала
    std::cout << "New Time: " << t3 << std::endl;

    // Пример использования пользовательских литералов
    auto interval = 2_d + 3_h + 15_m + 30_s; // Интервал времени
    std::cout << "Interval: " << interval << std::endl;

    return 0;
}
