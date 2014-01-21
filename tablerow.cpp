#ifdef __WAND__
target[name[tablerow.o] type[object]]
#endif

#include "tablerow.h"
#include "output.h"
#include "macro.h"

#include <herbs/intformat/intformat.h>
#include <herbs/exceptionmissing/exceptionmissing.h>

void Doxymax::TableRow::expand(const Macro& macro,CommentProcessor& processor)
	{
	Herbs::String str_out(256);
	str_out.append(STR("<tr>"));
	auto i=macro.args.begin();
	while(i!=macro.args.end())
		{
		str_out.append(STR("<td>")).append(*i).append(STR("</td>"));
		++i;
		}
	str_out.append(STR("</tr>"));
	print(str_out);
	}
