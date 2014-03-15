#ifdef __WAND__
target[name[old.o] type[object]]
#endif

#include "old.h"

Herbs::String Doxymax::Old::expand(const Macro& macro,CommentProcessor& processor)
	{
	return Herbs::String(STR("<dl class=\"section warning\"><dt>Warning</dt>"
		"<dd>The contents of this page or section is out-of-date and needs to "
		"be rewritten.</dd></dl>"));
	}
