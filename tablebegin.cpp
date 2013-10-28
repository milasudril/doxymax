#ifdef __WAND__
target[name[tablebegin.o] type[object]]
#endif

#include "tablebegin.h"
#include "output.h"
#include "macro.h"
#include "commentprocessor.h"

#include <herbs/intformat.h>
#include <herbs/exceptionmissing.h>

namespace
	{
	Herbs::String quoteKill(const Herbs::String& str)
		{
		Herbs::String ret(str.length());
		const char_t* ptr_begin=str.begin();
		while(ptr_begin!=str.end())
			{
			if(*ptr_begin!=CHAR('"'))
				{ret.append(*ptr_begin);}
			++ptr_begin;
			}
		return ret;
		}
	}

void Doxymax::TableBegin::expand(const Macro& macro,CommentProcessor& processor)
	{
	if(macro.args.length()<2)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}
	else
		{
		Herbs::String str_out(64);
		
		str_out.append(STR("\\anchor ")).append(macro.args[1])
			.append(STR(" <div style=\"text-align:center;width:100%\">"
				"<div class=\"caption\">Table "));
		
		size_t n=processor.labelGet(macro.args[1]);
		if(n==0)
			{
			n=processor.counterGet(STR("Table"));
			++n;
			processor.labelSet(macro.args[1],n);
			}
		
		str_out.append(Herbs::IntFormat<size_t>(n)).append(STR(": "))
			.append(quoteKill(macro.args[0]))
			.append(STR("</div>"))
			.append(STR("<table class=\"doxtable\">"));
		
		print(str_out);
		}
	}
