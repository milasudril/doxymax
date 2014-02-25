#ifdef __WAND__
dependency[paragraph_end.o]
target[name[paragraph_end.h] type[include]]
#endif

#ifndef PARAGRAPH_END_H
#define PARAGRAPH_END_H

#include "expander.h"

namespace Doxymax
	{
	class ParagraphEnd:public Expander
		{
		public:
			void expand(const Macro& macro,CommentProcessor& processor);
		};
	}

#endif

