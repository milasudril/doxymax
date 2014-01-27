#ifdef __WAND__
target[name[unquote.o] type[object]]
#endif

#include "unquote.h"
#include "output.h"
#include "macro.h"
#include <herbs/string/string.h>
#include <herbs/exceptionmissing/exceptionmissing.h>

void Doxymax::Unquote::expand(const Macro& macro,CommentProcessor& processor)
	{
	if(macro.args.length()<1)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}

	print(*macro.args.begin());
	}
