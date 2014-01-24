#ifdef __WAND__
dependency[termlist.o]
target[name[termlist.h] type[include]]
#endif

#ifndef TERMLIST_H
#define TERMLIST_H

#include "expander.h"

namespace Doxymax
	{
	class TermList:public Expander
		{
		public:
			void expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif

