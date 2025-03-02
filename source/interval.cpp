#include <interval.h>
interval::interval() {
    min = 0.0;
    max = 0.0;
}
interval::interval(float a, float b) {
    if (a <= b) {
        min = a;
        max = b;
    }
    else {
        min = b;
        max = a;
    }
}
interval::interval(const interval& a, const interval& b) {
    // Create the interval tightly enclosing the two input intervals.
    min = a.min <= b.min ? a.min : b.min;
    max = a.max >= b.max ? a.max : b.max;
}

float interval::size() const {
    return max - min;
}
bool interval::contains(double x) const {
    return min <= x && x <= max;
}
bool interval::surrounds(double x) const {
    return min < x && x < max;
}
void interval::expand(float delta) {
    max += delta;
}

interval operator+(const interval& ival, double displacement) {
    return interval(ival.min + displacement, ival.max + displacement);
}
interval operator+(double displacement, const interval& ival) {
    return ival + displacement;
}