#include <iomanip>
#include <iostream>
#include <string>
#include <ios>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "Student_info.h"
#include "grade.h"

using std::cout; using std::endl;

int main() {
	std::vector<Student_info> students;

	Student_info record;
	std::string::size_type maxlen = 0;

	while (record.read(std::cin)) {
		maxlen = std::max(maxlen, record.name().size());
		students.push_back(record);
	}

	std::sort(students.begin(), students.end(), Student_info::compare);

	for (std::vector<Student_info>::size_type i = 0; i != students.size(); ++i) {
		cout << students[i].name()
			<< std::string(maxlen + 1 - students[i].name().size(), ' ');
		try {
			double final_grade = students[i].grade();
			std::streamsize prec = cout.precision();
			cout << std::setprecision(3) << final_grade << std::setprecision(prec) << endl;
		}
		catch (std::domain_error e) {
			cout << e.what() << endl;
		}
	}
	return 0;
}