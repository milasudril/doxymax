#ifdef __WAND__
target[name[tableheader.o] type[object]]
#endif

#include "tableheader.h"
#include "macro.h"

#include <herbs/intformat/intformat.h>
#include <herbs/exceptionmissing/exceptionmissing.h>

Herbs::String Doxymax::TableHeader::expand(const Macro& macro,CommentProcessor& processor)
	{
	Herbs::String str_out(256);
	str_out.append(STR("<tr>"));
	auto i=macro.args.begin();
	while(i!=macro.args.end())
		{
		str_out.append(STR("<th>")).append(*i).append(STR("</th>"));
		++i;
		}
	str_out.append(STR("</tr>"));
	return std::move(str_out); 
	}
