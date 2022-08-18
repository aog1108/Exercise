#ifndef GUARD_Handle_H
#define GUARD_Handle_H

#include <stdexcept>

template <class T> class Handle {
public:
	Handle() : p(0) { }
	Handle(const Handle& s) : p(0) { if (s.p) p = s.p->clone(); }
	Handle& operator=(const Handle&);
	~Handle() { delete p; }

	Handle(T* t) : p(t) { }

	operator bool() const { return p; }
	T& operator*() const;
	T* operator->() const;

private:
	T* p;
};

template <class T> class Ref_handle{
public:
	Ref_handle() : p(0), refptr(new std::size_t(1)) { }
	Ref_handle(T* t) : p(t), refptr(new std::size_t(1)) { }
	Ref_handle(const Ref_handle& h) : p(h.p), refptr(h.refptr)
	{
		++ *refptr;
	}
	Ref_handle& operator=(const Ref_handle&);
	~Ref_handle();

	operator bool() const { return p; }
	T& operator*() const
	{
		if (p)
			return p;

		std::runtime_error("unbound Ref_handle");
	}
	T* operator->() const
	{
		if (p)
			return *p;
		
		std::runtime_error("unbound Ref_handle");
	}

private:
	T* p;
	std::size_t* refptr;
};

template <class T> class Ptr {
public:
	void make_unique()
	{
		if (*refptr != 1) {
			-- *refptr;
			refptr = new std::size_t(1);
			p = p ? p->clone() : 0;
		}
	}

	Ptr() : p(0), refptr(new std::size_t(1)) { }
	Ptr(T* t) : p(t), refptr(new std::size_t(1)) { }
	Ptr(const Ptr& h) : p(h.p), refptr(h.refptr) { ++ *refptr; }

	Ptr& operator=(const Ptr&);
	~Ptr();
	
	operator bool() const { return p; }
	Ptr& operator*() const {
		if (p)
			return *p;

		std::runtime_error("unbound Ptr");
	}
	Ptr* operator->() const {
		if (p)
			return p;

		std::runtime_error("unbound Ptr");
	}

private:
	T* p;
	std::size_t* refptr;
};

template <class T> Handle<T>& Handle<T>::operator=(const Handle& rhs)
{
	if (&rhs != this) {
		delete p;
		p = rhs.p ? rhs.p->clone() : 0;
	}
	return *this;

}

template <class T> T& Handle<T>::operator*() const
{
	if (p)
		return *p;

	throw std::runtime_error("unbound Handle");
}

template <class T> T* Handle<T>::operator->() const
{
	if (p)
		return p;

	throw std::runtime_error("unbound Handle");
}

template <class T> Ref_handle<T>& Ref_handle<T>::operator=(const Ref_handle& rhs)
{
	++ *rhs.refptr;
	if (-- *refptr == 0) {
		delete p;
		delete refptr;
	}

	refptr = rhs.refptr;
	p = rhs.p;

	return *this;
}

template <class T> Ref_handle<T>:: ~Ref_handle()
{
	if (-- *refptr == 0) {
		delete p;
		delete refptr;
	}
}

template <class T> Ptr<T>& Ptr<T>::operator=(const Ptr& rhs)
{
	++ *rhs.refptr;
	if (-- *refptr == 0) {
		delete p;
		delete refptr;
	}
	
	p = rhs.p;
	refptr = rhs.refptr;
	return *this;
}

template <class T> Ptr<T>::~Ptr()
{

}

#endif