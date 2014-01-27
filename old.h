#ifdef __WAND__
dependency[old.o]
target[name[old.h] type[include]]
#endif

#ifndef OLD_H
#define OLD_H

#include "expander.h"

namespace Doxymax
	{
	class Old:public Expander
		{
		public:
			void expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif

