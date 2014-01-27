#ifdef __WAND__
target[name[old.o] type[object]]
#endif

#include "old.h"
#include "output.h"
#include <herbs/string/string.h>

void Doxymax::Old::expand(const Macro& macro,CommentProcessor& processor)
	{
	Herbs::String str_out(64);
	str_out.append(STR("<dl class=\"section warning\"><dt>Warning</dt><dd>The contents of this page or section is out-of-date and needs to be rewritten.</dd></dl>"));
	print(str_out);
	}
