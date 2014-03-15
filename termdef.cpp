#ifdef __WAND__
target[name[termdef.o] type[object]]
#endif

#include "termdef.h"
#include "commentprocessor.h"

#include <herbs/intformat/intformat.h>
#include <herbs/exceptionmissing/exceptionmissing.h>

Herbs::String Doxymax::TermDef::expand(const Macro& macro,CommentProcessor& processor)
	{
	if(macro.args.length()<3)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}
	
	Herbs::String str_out(128);
	processor.definitionSet(macro.args[0],macro.args[2]);

		
	str_out.append(STR("<span class=\"termref\" title=\""))
		.append(macro.args[2]).append(STR("\">"))
		.append(macro.args[1])
		.append(STR("</span>"));
	
	return std::move(str_out);
	}
