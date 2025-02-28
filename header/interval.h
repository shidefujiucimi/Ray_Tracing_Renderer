#ifndef INTERVAL_H
#define INTERVAL_H
#include <common_header.h>
class interval {
public:
    float min, max;
    interval() {
        min = 0.0;
        max = 0.0;
    }
    interval(float a, float b) {
        if (a <= b) {
            min = a;
            max = b;
        }
        else {
            min = b;
            max = a;
        }
    }
    interval(const interval& a, const interval& b) {
        // Create the interval tightly enclosing the two input intervals.
        min = a.min <= b.min ? a.min : b.min;
        max = a.max >= b.max ? a.max : b.max;
    }

    float size() const {
        return max - min;
    }
    bool contains(double x) const {
        return min <= x && x <= max;
    }
    bool surrounds(double x) const {
        return min < x && x < max;
    }
    void expand(float delta) {
        max += delta;
    }
};
interval operator+(const interval& ival, double displacement) {
    return interval(ival.min + displacement, ival.max + displacement);
}

interval operator+(double displacement, const interval& ival) {
    return ival + displacement;
}
#endif
