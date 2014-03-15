#ifdef __WAND__
dependency[ref.o]
target[name[ref.h] type[include]]
#endif

#ifndef REF_H
#define REF_H

#include "expander.h"

namespace Doxymax
	{
	class Ref:public Expander
		{
		public:
			Herbs::String expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif

