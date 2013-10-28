#ifdef __WAND__
dependencies[ref.o]
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
			void expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif

