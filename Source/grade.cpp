#include "grade.h"
#include "median.h"
#include <list>
#include <numeric>
#include <algorithm>

double grade(double midterm, double final, double median)
{
	return 0.2 * midterm + 0.4 * final + 0.4 * median;
}

double grade(double midterm, double final, std::vector<double> homework)
{
	return grade(midterm, final, median(homework));
}

bool fgrade(const Student_info& s)
{
	return s.grade() < 60;
}

bool pgrade(const Student_info& s)
{
	return !fgrade(s);
}

double average(std::vector<double>& v)
{
	return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}