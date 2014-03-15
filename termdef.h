#ifdef __WAND__
dependency[termdef.o]
target[name[termdef.h] type[include]]
#endif

#ifndef TERMDEF_H
#define TERMDEF_H

#include "expander.h"

namespace Doxymax
	{
	class TermDef:public Expander
		{
		public:
			Herbs::String expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif

