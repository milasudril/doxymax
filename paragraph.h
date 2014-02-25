#ifdef __WAND__
dependency[paragraph.o]
target[name[paragraph.h] type[include]]
#endif

#ifndef PARAGRAPH_H
#define PARAGRAPH_H

#include "expander.h"

namespace Doxymax
	{
	class Paragraph:public Expander
		{
		public:
			void expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif

