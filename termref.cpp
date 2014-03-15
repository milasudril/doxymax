#ifdef __WAND__
target[name[termref.o] type[object]]
#endif

#include "termref.h"
#include "commentprocessor.h"
#include "macro.h"

#include <herbs/intformat/intformat.h>
#include <herbs/exceptionmissing/exceptionmissing.h>

Herbs::String Doxymax::TermRef::expand(const Macro& macro,CommentProcessor& processor)
	{
	if(macro.args.length()<2)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}
	
	Herbs::String str_out(128);
	const Herbs::String* def=processor.definitionGet(macro.args[0]);
	Herbs::String def_deref(STR("????"));
	if(def!=nullptr)
		{def_deref=*def;}
		
	str_out.append(STR("<span class=\"termref\" title=\""))
		.append(def_deref).append(STR("\">"))
		.append(macro.args[1])
		.append(STR("</span>"));
	
	return std::move(str_out);
	}
