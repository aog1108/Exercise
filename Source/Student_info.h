#ifndef GUARD_Student_info_h
#define GUARD_Student_info_h

#include <string>
#include <vector>
#include <iostream>

class Student_info {
public:
	Student_info() : midterm(0), final(0) {}
	Student_info(std::istream& is) { read(is); }

	std::istream& read(std::istream&);
	double grade() const;
	std::string name() const { return n; }
	bool valid() const { return !homework.empty(); }

private:
	std::string n;
	double midterm, final;
	std::vector<double> homework;
};

bool compare(const Student_info&, const Student_info&);

std::istream& read_hw(std::istream&, std::vector<double>&);

#endif