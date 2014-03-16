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
	if(macro.args.length()<1)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}

	Herbs::String str_out(64);
	
	str_out.append(STR("<li class=\"itemdoxmax\""));
	if(processor.macroExpansionDepth()==1)
		{str_out.append(STR(" style=\"position:relative\""));}
	str_out.append(STR("><span class=\"itemhead\">")).append(macro.args[0])
		.append(STR("</span>"));
	if(macro.args.length()>2)
		{
		str_out.append(STR("<span class=\"itemcomment\">"))
			.append(macro.args[2])
			.append(STR("</span>"));
		}
	if(macro.args.length()>1)
		{
		str_out.append(macro.args[1]);
		}
	str_out.append(STR("</li>"));
	return std::move(str_out);
	}
