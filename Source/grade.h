#ifndef GUARD_grade_h
#define GUARD_grade_h

#include <vector>
#include "Student_info.h"

double grade(double, double, double);

double grade(double, double, std::vector<double>);

bool fgrade(const Student_info&);

bool pgrade(const Student_info&);

double average(const std::vector<double>&);

#endif