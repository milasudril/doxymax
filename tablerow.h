#ifdef __WAND__
dependencies[tablerow.o]
target[name[tablerow.h] type[include]]
#endif

#ifndef TABLEROW_H
#define TABLEROW_H

#include "expander.h"

namespace Doxymax
	{
	class TableRow:public Expander
		{
		public:
			void expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif

