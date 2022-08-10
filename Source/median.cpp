#include "median.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

double median(std::vector<double> vec)
{	
	std::vector<double>::size_type size = vec.size();

	if (size == 0) {
		throw std::domain_error("median of an empty vector.");
	}
	
	std::sort(vec.begin(), vec.end());
	
	std::vector<double>::size_type mid = size / 2;

	return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}