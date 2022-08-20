#pragma once

#include "Vec.h"
#include <iterator>
#include <iostream>
#include "Handle.h"

class Str {
	friend std::istream& operator>>(std::istream&, Str&);
public:
	Str& operator+=(const Str& s)
	{
		data.make_unique();
		std::copy(s.data->begin(), s.data->end(), std::back_inserter(*data));
		return *this;
	}

	typedef Vec<char>::size_type size_type;

	Str() : data(new Vec<char>) { }
	Str(size_type n, char c) : data(new Vec<char>(n, c)) { }
	Str(const char* cp) {
		std::copy(cp, cp + std::strlen(cp), std::back_inserter(*data));
	}
	template <class In> Str(In b, In e) {
		std::copy(b, e, std::back_inserter(*data));
	}

	char& operator[](size_type i) { 
		data.make_unique();
		return (*data)[i]; 
	}
	const char& operator[](size_type i) const { return (*data)[i]; }

	size_type size() const { return data->size(); }

private:
	Ptr< Vec<char> > data;
};

std::istream& operator>>(std::istream&, Str&);
std::ostream& operator<<(std::ostream&, const Str&);

Str operator+(const Str&, const Str&);