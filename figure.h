#ifdef __WAND__
dependency[figure.o]
target[name[figure.h] type[include]]
#endif

#ifndef FIGURE_H
#define FIGURE_H

#include "expander.h"

namespace Doxymax
	{
	class Figure:public Expander
		{
		public:
			Herbs::String expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif

