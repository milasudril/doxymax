#ifdef __WAND__
target[name[tablerow.o] type[object]]
#endif

#include "tablerow.h"
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

void Doxymax::TableRow::expand(const Macro& macro,CommentProcessor& processor)
	{
	Herbs::String str_out(256);
	str_out.append(STR("<tr>"));
	auto i=macro.args.begin();
	while(i!=macro.args.end())
		{
		str_out.append(STR("<td>")).append(quoteKill(*i)).append(STR("</td>"));
		++i;
		}
	str_out.append(STR("</tr>"));
	print(str_out);
	}