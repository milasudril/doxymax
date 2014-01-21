#ifdef __WAND__
target[name[macro.h] type[include]]
#endif

#ifndef MACRO_H
#define MACRO_H

#include <herbs/string/string.h>

namespace Doxymax
	{
	struct Macro
		{
		Herbs::String name;
		Herbs::Array<Herbs::String> args;
		};
	}
	
#endif
