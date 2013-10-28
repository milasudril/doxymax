#ifdef __WAND__
target[name[ref.o] type[object]]
#endif

#include "ref.h"
#include "output.h"
#include "macro.h"
#include "commentprocessor.h"

#include <herbs/intformat.h>
#include <herbs/exceptionmissing.h>

namespace
	{
	Herbs::String quoteKill(const Herbs::String& str)
		{
		Herbs::String ret(str.length());
		const char_t* ptr_begin=str.begin();
		while(ptr_begin!=str.end())
			{
			if(*ptr_begin!=CHAR('"'))
				{ret.append(*ptr_begin);}
			++ptr_begin;
			}
		return ret;
		}
	}

void Doxymax::Ref::expand(const Macro& macro,CommentProcessor& processor)
	{
	if(macro.args.length()<1)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}
	
	Herbs::String str_out(64);
	size_t cval=processor.labelGet(macro.args[0]);
	str_out.append(STR("\\ref ")).append(macro.args[0])
		.append(STR(" \""))
		.append(Herbs::IntFormat<size_t>(cval))
		.append(CHAR('"'));
	
	print(str_out);
	}