#ifdef __WAND__
dependency[unquote.o]
target[name[unquote.h] type[include]]
#endif

#ifndef UNQUOTE_H
#define UNQUOTE_H

#include "expander.h"

namespace Doxymax
	{
	class Unquote:public Expander
		{
		public:
			void expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif

