#include "Student_info.h"
#include "grade.h"
#include "median.h"
#include <algorithm>
#include "Handle.h"

using std::cout; using std::endl;

double Core::grade() const
{
	return ::grade(midterm, final, homework);
}

std::istream& Core::read_common(std::istream& in)
{
	in >> n >> midterm >> final;
	return in;
}

std::istream& Core::read(std::istream& in)
{
	read_common(in);
	read_hw(in, homework);
	return in;
}

std::istream& Grad::read(std::istream& in)
{
	Core::read_common(in);
	in >> thesis;
	read_hw(in, homework);
	return in;
}

double Grad::grade() const
{
	return std::min(Core::grade(), thesis);
}

bool compare(const Core& c1, const Core& c2)
{
	return c1.name() < c2.name();
}

bool compare(const Core* cp1, const Core* cp2)
{
	return cp1->name() < cp2->name();
}

bool compare_grades(const Core& c1, const Core& c2)
{
	return c1.grade() < c2.grade();
}

bool compare_Core_handles(const Handle<Core>& h1, const Handle<Core>& h2)
{
	return h1->name() < h2->name();
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

std::istream& Student_info::read(std::istream& is) {
	char ch;
	is >> ch;

	if (ch == 'U')
		cp = new Core(is);
	else
		cp = new Grad(is);

	return is;
}