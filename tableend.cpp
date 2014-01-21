#ifdef __WAND__
target[name[tableend.o] type[object]]
#endif

#include "tableend.h"
#include "output.h"
#include <herbs/string/string.h>

void Doxymax::TableEnd::expand(const Macro& macro,CommentProcessor& processor)
	{
	Herbs::String str_out(64);
	str_out.append(STR("</table></div>"));
	print(str_out);
	}
