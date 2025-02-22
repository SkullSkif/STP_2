#include "main.h"

namespace your_namespace {

// Реализация класса Time
Time::Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
    normalize();
}

void Time::normalize() {
    if (seconds >= 60) {
        minutes += seconds / 60;
        seconds %= 60;
    }
    if (minutes >= 60) {
        hours += minutes / 60;
        minutes %= 60;
    }
    if (hours < 0 || minutes < 0 || seconds < 0) {
        hours = minutes = seconds = 0; // Устанавливаем в 0 при отрицательных значениях
    }
}

Time Time::operator-(const Time& other) const {
    return Time(hours - other.hours, minutes - other.minutes, seconds - other.seconds);
}

TimeSpan Time::operator-(const TimeSpan& other) const {
    // Здесь можно реализовать логику для вычитания TimeSpan из Time
    // Например, преобразовать Time в TimeSpan и вычесть
    return TimeSpan(0, hours - other.hours, minutes - other.minutes, seconds - other.seconds);
}

Time Time::operator+(const TimeSpan& ts) const {
    return Time(hours + ts.hours, minutes + ts.minutes, seconds + ts.seconds);
}

bool Time::operator==(const Time& other) const {
    return hours == other.hours && minutes == other.minutes && seconds == other.seconds;
}

bool Time::operator!=(const Time& other) const {
    return !(*this == other);
}

bool Time::operator<(const Time& other) const {
    return std::tie(hours, minutes, seconds) < std::tie(other.hours, other.minutes, other.seconds);
}

bool Time::operator<=(const Time& other) const {
    return *this < other || *this == other;
}

bool Time::operator>(const Time& other) const {
    return !(*this <= other);
}

bool Time::operator>=(const Time& other) const {
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << std::setfill('0') << std::setw(2) << time.hours << ":"
       << std::setw(2) << time.minutes << ":"
       << std::setw(2) << time.seconds;
    return os;
}

// Реализация класса TimeSpan
TimeSpan::TimeSpan(int d, int h, int m, int s) : days(d), hours(h), minutes(m), seconds(s) {
    normalize();
}

void TimeSpan::normalize() {
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

TimeSpan TimeSpan::operator+(const TimeSpan& other) const {
    return TimeSpan(days + other.days, hours + other.hours, minutes + other.minutes, seconds + other.seconds);
}

TimeSpan TimeSpan::operator-(const TimeSpan& other) const {
    return TimeSpan(days - other.days, hours - other.hours, minutes - other.minutes, seconds - other.seconds);
}

bool TimeSpan::operator==(const TimeSpan& other) const {
    return days == other.days && hours == other.hours && minutes == other.minutes && seconds == other.seconds;
}

bool TimeSpan::operator!=(const TimeSpan& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const TimeSpan& ts) {
    os << ts.days << "d " << ts.hours << "h " << ts.minutes << "m " << ts.seconds << "s";
    return os;
}

// Реализация пользовательских литералов
namespace literals {

constexpr TimeSpan operator"" _d(unsigned long long d) {
    return TimeSpan(static_cast<int>(d));
}

constexpr TimeSpan operator"" _h(unsigned long long h) {
    return TimeSpan(0, static_cast<int>(h));
}

constexpr TimeSpan operator"" _m(unsigned long long m) {
    return TimeSpan(0, 0, static_cast<int>(m));
}

constexpr TimeSpan operator"" _s(unsigned long long s) {
    return TimeSpan(0, 0, 0, static_cast<int>(s));
}

} // namespace literals

} // namespace your_namespace
