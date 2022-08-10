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
	std::vector<Student_info> did, didnt;

	Student_info student;

	while (read(std::cin, student)) {
		if (did_all_hw(student))
			did.push_back(student);
		else
			didnt.push_back(student);
	}

	if (did.empty()) {
		cout << "No student did all the homework!" << endl;	
		return 1;
	}

	if (didnt.empty()) {
		cout << "Every student did all the homework!" << endl;
		return 1;
	}

	write_analysis(cout, "median", median_analysis, did, didnt);
	write_analysis(cout, "average", average_analysis, did, didnt);
	write_analysis(cout, "median of homework turned in", optimistic_median_analysis, did, didnt);

	return 0;
}