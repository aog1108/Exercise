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

double grade(const Student_info& s)
{
	return grade(s.midterm, s.final, s.homework);
}

bool fgrade(const Student_info& s)
{
	return grade(s) < 60;
}

bool pgrade(const Student_info& s)
{
	return !fgrade(s);
}

std::list<Student_info> extract_fails(std::list<Student_info>& students)
{
	std::list<Student_info> fail;
	std::list<Student_info>::iterator iter = students.begin();

	while (iter != students.end()) {
		if (fgrade(*iter)) {
			fail.push_back(*iter);
			iter = students.erase(iter);
		}
		else {
			++iter;
		}
	}
	return fail;
}

double grade_aux(const Student_info& s)
{
	try {
		return grade(s);
	}
	catch (std::domain_error) {
		return grade(s.midterm, s.final, 0);
	}
}

double average(const std::vector<double>& v)
{
	return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double average_grade(const Student_info& s)
{
	return grade(s.midterm, s.final, average(s.homework));
}

double optimistic_median(const Student_info& s)
{
	std::vector<double> nonzero;
	std::remove_copy(s.homework.begin(), s.homework.end(), std::back_inserter(nonzero), 0);

	if (nonzero.empty())
		return grade(s.midterm, s.final, 0);
	else
		return grade(s.midterm, s.final, median(nonzero));
}