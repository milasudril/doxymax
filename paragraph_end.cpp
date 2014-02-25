#ifdef __WAND__
target[name[paragraph_end.o] type[object]]
#endif

#include "paragraph_end.h"
#include "output.h"
#include "macro.h"
#include <herbs/string/string.h>

void Doxymax::ParagraphEnd::expand(const Macro& macro,CommentProcessor& processor)
	{
	print(Herbs::String(STR("</p></div>\\endhtmlonly")));
	}
