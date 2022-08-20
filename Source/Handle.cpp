#include "Handle.h"

template <> Vec<char>* clone(const Vec<char>* vp)
{
	return new Vec<char>(*vp);
}