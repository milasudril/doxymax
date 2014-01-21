#ifdef __WAND__
target[name[expander.h] type[include]]
#endif

#ifndef EXPANDER_H
#define EXPANDER_H

namespace Doxymax
	{
	class CommentProcessor;
	class Macro;
	class Expander
		{
		public:
			virtual void expand(const Macro& macro,CommentProcessor& processor)=0;			
		};
	}

#endif

