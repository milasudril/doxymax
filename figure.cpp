#ifdef __WAND__
target[name[figure.o] type[object]]
#endif

#include "figure.h"
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

void Doxymax::Figure::expand(const Macro& macro,CommentProcessor& processor)
	{
	if(macro.args.length()<3)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}
	
	Herbs::String str_out(128);
	str_out
		.append(STR("\\anchor ")).append(macro.args[2]).append(CHAR(' '))
		.append(STR("<div class=\"image\">"))
		.append(STR("<img src=\""))
		.append(quoteKill(macro.args[0])).append(CHAR('"'));

	if(macro.args.length()>3)
		{
		str_out.append(STR(" width=\"")).append(quoteKill(macro.args[3]))
			.append(CHAR('"'));
		}
	
	if(macro.args.length()>4)
		{
		str_out.append(STR(" height=\"")).append(quoteKill(macro.args[4]))
			.append(CHAR('"'));
		}
	
	size_t n=processor.labelGet(macro.args[2]);
	if(n==0)
		{
		n=processor.counterGet(STR("Figure"));
		++n;
		processor.labelSet(macro.args[2],n);
		}
	str_out.append(STR("/><div class=\"caption\">Figure "))
		.append(Herbs::IntFormat<size_t>(n))
		.append(STR(": "))
		.append(quoteKill(macro.args[1]))
		.append(STR("</div></div>"));
	processor.counterSet(STR("Figure"),n);
	
	print(str_out);
	}