#ifndef GUARD_Str_H
#define GUARD_Str_H

#include "Vec.h"
#include <iterator>

class Str {
public:
	typedef Vec<char>::size_type size_type;

	Str() { }
	Str(size_type n, char c) : data(n, c) { }
	Str(const char* cp) {
		std::copy(cp, cp + std::strlen(cp), std::back_inserter(data));
	}
	template <class In> Str(In b, In e) {
		std::copy(b, e, std::back_inserter(data));
	}

private:
	Vec<char> data;
};

#endif