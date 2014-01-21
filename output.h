#ifdef __WAND__
dependency[output.o]
target[name[output.h] type[include]]
#endif

#ifndef OUTPUT_H
#define OUTPUT_H

#include <herbs/chartype/chartype.h>

namespace Herbs
	{
	template<class T>
	class Stringbase;
	
	typedef Stringbase<char_t> String;
	}

namespace Doxymax
	{
	void print(const Herbs::String& str);
	}

#endif
