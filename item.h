#ifdef __WAND__
dependency[item.o]
target[name[item.h] type[include]]
#endif

#ifndef ITEM_H
#define ITEM_H

#include "expander.h"

namespace Doxymax
	{
	class Item:public Expander
		{
		public:
			void expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif
