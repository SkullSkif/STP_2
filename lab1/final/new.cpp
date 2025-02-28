#include "main.h"

namespace lab1 {


Time::Time(int d, int h, int m, int s) : days(d), hours(h), minutes(m), seconds(s) {
    while (days < 0 || hours < 0 || minutes < 0 || seconds < 0)
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
    if (hours >= 24) {
        days += hours / 24;
        hours %= 24;
    }

    // if (days < 0 || hours < 0 || minutes < 0 || seconds < 0) {
    //     days = hours = minutes = seconds = 0; 
    // }    
}

TimeSpan Time::operator-(const Time& other) const {
    return TimeSpan(days - other.days, hours - other.hours, minutes - other.minutes, seconds - other.seconds);
}

TimeSpan Time::operator-(const TimeSpan& other) const {
    return TimeSpan(days - other.days, hours - other.hours, minutes - other.minutes, seconds - other.seconds);
}

Time Time::operator+(const TimeSpan& ts) const {
    return Time(days + ts.days, hours + ts.hours, minutes + ts.minutes, seconds + ts.seconds);
}

bool Time::operator==(const Time& other) const {
    return days == other.days && hours == other.hours && minutes == other.minutes && seconds == other.seconds;
}

bool Time::operator!=(const Time& other) const {
    return !(*this == other);
}

bool Time::operator<(const Time& other) const {
    return std::tie(days, hours, minutes, seconds) < std::tie(other.days, other.hours, other.minutes, other.seconds);
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
    os << std::setfill('0')
       << std::setw(2) << time.days << ":" 
       << std::setw(2) << time.hours << ":"
       << std::setw(2) << time.minutes << ":"
       << std::setw(2) << time.seconds;
    return os;
}


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
    if (days < 0)
        hours = 24;
    if (hours < 0)
        minutes = 60;
    if (minutes < 0)
        minutes = 0;
    if (seconds < 0)
        seconds = 0;
    // if (days < 0 || hours < 0 || minutes < 0 || seconds < 0) {
    //     TimeSpan::normalize();
    // }
    // if (days < 0 || hours < 0 || minutes < 0 || seconds < 0) {
    //     days = hours = minutes = seconds = 0; 
    // }    
}

TimeSpan TimeSpan::operator+(const TimeSpan& other) const {
    return TimeSpan(days + other.days, hours + other.hours, minutes + other.minutes, seconds + other.seconds);
}

TimeSpan TimeSpan::operator-(const TimeSpan& other) const {
    return TimeSpan(days - other.days, hours - other.hours, minutes - other.minutes, seconds - other.seconds);
}

// TimeSpan TimeSpan::operator-(const Time& other) const {
//     return TimeSpan(days - other.days, hours - other.hours, minutes - other.minutes, seconds - other.seconds);
// }

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

namespace literals {

TimeSpan operator"" _d(unsigned long long d) {
    return TimeSpan(static_cast<int>(d));
}

TimeSpan operator"" _h(unsigned long long h) {
    return TimeSpan(0, static_cast<int>(h));
}

TimeSpan operator"" _m(unsigned long long m) {
    return TimeSpan(0, 0, static_cast<int>(m));
}

TimeSpan operator"" _s(unsigned long long s) {
    return TimeSpan(0, 0, 0, static_cast<int>(s));
}

} // namespace literals

} // namespace lab1

int main() {
    using namespace lab1;
    using namespace lab1::literals;

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

