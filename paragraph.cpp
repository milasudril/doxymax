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

	print(Herbs::format(STR("\\htmlonly <div class=\"parabox\"><h4><a name=\"%1\">%0</a></h4><p class=\"parainline\">"),
		{
		 macro.args[0].begin()
		,macro.args[1].begin()
		}));
	}