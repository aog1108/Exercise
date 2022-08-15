#ifndef GUARD_Student_info_h
#define GUARD_Student_info_h

#include <string>
#include <vector>
#include <iostream>

class Core {
	friend class Student_info;
public:
	Core() : midterm(0), final(0) { }
	Core(std::istream& is) { read(is); }

	virtual ~Core() { }

	std::string name() const { return n; }
	virtual std::istream& read(std::istream&);
	virtual double grade() const;

protected:
	virtual Core* clone() { return new Core(*this); }
	std::istream& read_common(std::istream&);
	double midterm, final;
	std::vector<double> homework;

private:
	std::string n;
};

class Grad : public Core {
public:
	Grad() : thesis(0) { }
	Grad(std::istream& is) { read(is); }
	double grade() const;
	std::istream& read(std::istream&);

protected:
	Grad* clone() { return new Grad(*this); }

private:
	double thesis;
};

class Student_info {
public:
	Student_info() : cp(0) { }
	Student_info(std::istream& is) : cp(0) { read(is); }
	
	Student_info(const Student_info& s) : cp(0) { if (s.cp) cp = s.cp->clone(); }
	
	Student_info& operator=(const Student_info& s)
	{
		if (&s != this) {
			delete cp;
			if (s.cp)
				cp = s.cp->clone();
			else
				cp = 0;
		}
		return *this;
	}
	
	~Student_info() { delete cp; }

	std::istream& read(std::istream&);

	std::string name() const {
		if (cp) return cp->name();
		else throw std::runtime_error("uninitialized Student");
	}
	double grade() const {
		if (cp) return cp->grade();
		else throw std::runtime_error("uninitialized Student");
	}
	static bool compare(const Student_info& s1, const Student_info& s2) {
		return s1.name() < s2.name();
	}

private:
	Core* cp;
};

bool compare(const Core&, const Core&);
bool compare_Core_ptrs(const Core*, const Core*);
bool compare_grades(const Core&, const Core&);

std::istream& read_hw(std::istream&, std::vector<double>&);

#endif