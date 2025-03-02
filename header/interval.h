#ifndef INTERVAL_H
#define INTERVAL_H
#include <common_header.h>
class interval {
public:
    float min, max;
    interval();
    interval(float a, float b);
    interval(const interval& a, const interval& b);

    float size() const;
    bool contains(double x) const;
    bool surrounds(double x) const;
    void expand(float delta);
};
interval operator+(const interval& ival, double displacement);
interval operator+(double displacement, const interval& ival);
#endif
