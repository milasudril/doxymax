#ifdef __WAND__
target[name[paragraph_end.o] type[object]]
#endif

#include "paragraph_end.h"
#include "macro.h"

Herbs::String Doxymax::ParagraphEnd::expand(const Macro& macro,CommentProcessor& processor)
	{
	return Herbs::String(STR("</p></div>\\endhtmlonly"));
	}
