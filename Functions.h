#pragma once
#include <vector>
#include <string>

struct Time {
    int hour;
    int min;

    Time() {
        hour = 0;
        min = 0;
    }

    Time(std::string& str) {
        hour = (str[0] - '0') * 10 + (str[1] - '0');
        min = (str[3] - '0') * 10 + (str[4] - '0');
    }

    Time(const Time& other)
    {
        hour = other.hour;
        min = other.min;
    }

    bool operator<(const Time& other) {
        if (hour < other.hour) {
            return true;
        }
        else {
            return false;
        }
        if (hour == other.hour) {
            if (min < other.min)
            {
                return true;
            }
        }
        else {
            return false;
        }
    }

    bool operator>(const Time& other) {
        if (hour > other.hour) {
            return true;
        }
        else {
            return false;
        }
        if (hour == other.hour) {
            if (min > other.min)
            {
                return true;
            }
        }
        else {
            return false;
        }
    }

    bool operator==(const Time& other) {
        return (hour == other.hour && min == other.min);
    }

    bool operator!=(const Time& other)
    {
        return !(*this == other);
    }

    Time& operator=(const Time& other) {
        hour = other.hour;
        min = other.min;
        return *this;
    }

    int operator-(const Time& other) {
        if (*this < other) {
            throw "Eror!Trying to subtract a larger time value";
        }

        int result = 0;
        int hour_diff = this->hour - other.hour;
        int min_diff = this->min - other.min;

        if (min_diff < 0 && hour_diff>0) {
            result = hour_diff;
        }
        if (min_diff > 0 && hour_diff == 0) {
            result = 1;
        }
        if (min_diff > 0 && hour_diff > 0) {
            result = hour_diff + 1;
        }

        return result;
    }
};

