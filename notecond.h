#ifdef __WAND__
dependency[notecond.o]
target[name[notecond.h] type[include]]
#endif

#ifndef NOTECOND_H
#define NOTECOND_H

#include "expander.h"

namespace Doxymax
	{
	class NoteCond:public Expander
		{
		public:
			Herbs::String expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif

