#ifdef __WAND__
dependency[termref.o]
target[name[termref.h] type[include]]
#endif

#ifndef TERMREF_H
#define TERMREF_H

#include "expander.h"

namespace Doxymax
	{
	class TermRef:public Expander
		{
		public:
			void expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif

