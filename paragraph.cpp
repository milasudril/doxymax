#ifdef __WAND__
target[name[paragraph.o] type[object]]
#endif

#include "paragraph.h"
#include "output.h"
#include "macro.h"
#include <herbs/stringformat/stringformat.h>
#include <herbs/exceptionmissing/exceptionmissing.h>

void Doxymax::Paragraph::expand(const Macro& macro,CommentProcessor& processor)
	{
	if(macro.args.length()<2)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}

	//Is it possible to reference to this?
	print(Herbs::format(STR("<a name=\"%1\"><h4>%0</h4></a>"),
		{
		 macro.args[0].begin()
		,macro.args[1].begin()
		}));
	}
