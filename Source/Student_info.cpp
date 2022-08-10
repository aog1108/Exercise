#include "Student_info.h"
#include "grade.h"
#include "median.h"
#include <algorithm>

using std::cout; using std::endl;

bool compare(const Student_info& s1, const Student_info& s2)
{
	return s1.name < s2.name; 
}

std::istream& read(std::istream& in, Student_info& s)
{
	in >> s.name >> s.midterm >> s.final;
	read_hw(in, s);
	return in;
}

std::istream& read_hw(std::istream& is, Student_info& s)
{
	if (is) {
		s.homework.clear();
		
		double x;
		
		while (std::cin >> x) {
			s.homework.push_back(x);
		}

		is.clear();
	}
	return is;
}

bool did_all_hw(const Student_info& s)
{
	return (std::find(s.homework.begin(), s.homework.end(), 0) == s.homework.end());
}

double median_analysis(const std::vector<Student_info>& students)
{
	std::vector<double> grades;
	std::transform(students.begin(), students.end(), std::back_inserter(grades), grade_aux);
	return median(grades);
}

void write_analysis(std::ostream& out, const std::string& name, double analysis(const std::vector<Student_info>&), const std::vector<Student_info>& did, const std::vector<Student_info>& didnt)
{
	out << name << ": median(did) = " << analysis(did) << ", median(didnt) = " << analysis(didnt) << endl;
}

double average_analysis(const std::vector<Student_info>& students)
{
	std::vector<double> grades;
	std::transform(students.begin(), students.end(), std::back_inserter(grades), average_grade);
	return median(grades);
}

double optimistic_median_analysis(const std::vector<Student_info>& students)
{
	std::vector<double> grades;
	std::transform(students.begin(), students.end(), std::back_inserter(grades), optimistic_median);
	return median(grades);
}

std::vector<Student_info> extract_fails(std::vector<Student_info>& students)
{
	std::vector<Student_info>::iterator iter = std::stable_partition(students.begin(), students.end(), pgrade);
	std::vector<Student_info> fail(iter, students.end());
	students.erase(iter, students.end());
	return fail;
}