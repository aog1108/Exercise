#include "Student_info.h"
#include "grade.h"
#include "median.h"
#include <algorithm>

using std::cout; using std::endl;

bool compare(const Student_info& s1, const Student_info& s2)
{
	return s1.name() < s2.name();
}

std::istream& read_hw(std::istream& in, std::vector<double>& homework)
{
	if (in) {
		homework.clear();

		double x;

		while (std::cin >> x) {
			homework.push_back(x);
		}

		in.clear();
	}
	return in;
}

std::istream& Student_info::read(std::istream& in)
{
	in >> n >> midterm >> final;
	read_hw(in, homework);

	return in;
}

double Student_info::grade() const
{
	return ::grade(midterm, final, homework);
}