#ifdef __WAND__
target[name[paragraph.o] type[object]]
#endif

#include "paragraph.h"
#include "macro.h"
#include <herbs/stringformat/stringformat.h>
#include <herbs/exceptionmissing/exceptionmissing.h>

Herbs::String Doxymax::Paragraph::expand(const Macro& macro,CommentProcessor& processor)
	{
	if(macro.args.length()<2)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}

	return Herbs::format(STR("\\htmlonly <div class=\"parabox\"><h4><a class=\"anchor\" id=\"%1\"></a>%0</h4><p class=\"parainline\">"),
		{
		 macro.args[0].begin()
		,macro.args[1].begin()
		});
	}
