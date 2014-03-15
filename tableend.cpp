#ifdef __WAND__
target[name[tableend.o] type[object]]
#endif

#include "tableend.h"
#include <herbs/string/string.h>

Herbs::String Doxymax::TableEnd::expand(const Macro& macro,CommentProcessor& processor)
	{
	return Herbs::String(STR("</table></div>"));
	}
