#ifdef __WAND__
dependencies[tableend.o]
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
			void expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif

