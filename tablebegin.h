#ifdef __WAND__
dependency[tablebegin.o]
target[name[tablebegin.h] type[include]]
#endif

#ifndef TABLEBEGIN_H
#define TABLEBEGIN_H

#include "expander.h"

namespace Doxymax
	{
	class TableBegin:public Expander
		{
		public:
			void expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif

