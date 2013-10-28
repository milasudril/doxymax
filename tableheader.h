#ifdef __WAND__
dependencies[tableheader.o]
target[name[tableheader.h] type[include]]
#endif

#ifndef TABLEHEADER_H
#define TABLEHEADER_H

#include "expander.h"

namespace Doxymax
	{
	class TableHeader:public Expander
		{
		public:
			void expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif

