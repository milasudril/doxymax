#ifdef __WAND__
dependency[tableend.o]
target[name[tableend.h] type[include]]
#endif

#ifndef TABLEEND_H
#define TABLEEND_H

#include "expander.h"

namespace Doxymax
	{
	class TableEnd:public Expander
		{
		public:
			Herbs::String expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif

