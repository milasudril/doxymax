#ifdef __WAND__
target[name[item.o] type[object]]
#endif

#include "item.h"
#include "macro.h"
#include "commentprocessor.h"

#include <herbs/intformat/intformat.h>
#include <herbs/exceptionmissing/exceptionmissing.h>

Herbs::String Doxymax::Item::expand(const Macro& macro,CommentProcessor& processor)
	{
	if(macro.args.length()<2)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}

	Herbs::String str_out(64);
	
	str_out.append(STR("<li style=\"position:relative\">")).append(macro.args[0]);
	if(macro.args.length()>1)
		{
		str_out.append(STR("<span class=\"itemcomment\">"))
			.append(macro.args[1])
			.append(STR("</span>"));
		}
	str_out.append(STR("</li>"));
	return std::move(str_out);
	}
