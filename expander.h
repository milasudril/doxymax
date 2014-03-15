#ifdef __WAND__
target[name[expander.h] type[include]]
#endif

#ifndef EXPANDER_H
#define EXPANDER_H

#include <herbs/string/string.h>

namespace Doxymax
	{
	class CommentProcessor;
	class Macro;
	class Expander
		{
		public:
			virtual Herbs::String expand(const Macro& macro,CommentProcessor& processor)=0;			
		};
	}

#endif

