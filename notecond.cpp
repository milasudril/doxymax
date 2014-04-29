#ifdef __WAND__
target[name[notecond.o] type[object]]
#endif

#include "notecond.h"
#include "macro.h"
#include "commentprocessor.h"

#include <herbs/stringformat/stringformat.h>
#include <herbs/exceptionmissing/exceptionmissing.h>

Herbs::String Doxymax::NoteCond::expand(const Macro& macro,CommentProcessor& processor)
	{
	if(macro.args.length()<2)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}

	Herbs::String str_out(64);
	
	str_out.append(Herbs::format(STR("\\note <strong>%0:</strong> %1")
		,{macro.args[0].begin(),macro.args[1].begin()}));
	
	return std::move(str_out);
	}
