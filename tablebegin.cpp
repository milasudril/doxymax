#ifdef __WAND__
target[name[tablebegin.o] type[object]]
#endif

#include "tablebegin.h"
#include "output.h"
#include "macro.h"
#include "commentprocessor.h"

#include <herbs/intformat/intformat.h>
#include <herbs/exceptionmissing/exceptionmissing.h>

void Doxymax::TableBegin::expand(const Macro& macro,CommentProcessor& processor)
	{
	if(macro.args.length()<2)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}

	Herbs::String str_out(64);
	
	str_out.append(STR("\\anchor ")).append(macro.args[1])
		.append(STR(" <div style=\"width:100%\">"
			"<div class=\"caption\" style=\"text-align:center\">Table "));
	
	size_t n=processor.labelGet(macro.args[1]);
	if(n==0)
		{
		n=processor.counterGet(STR("Table"));
		++n;
		processor.labelSet(macro.args[1],n);
		}
	processor.counterSet(STR("Table"),n);
	str_out.append(Herbs::IntFormat<size_t>(n)).append(STR(": "))
		.append(macro.args[0])
		.append(STR("</div>"))
		.append(STR("<table class=\"doxtable\" style=\"margin-left:auto;margin-right:auto;\">"));
	
	print(str_out);
	}
