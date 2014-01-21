#ifdef __WAND__
dependencies[figure.o]
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
			void expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif

