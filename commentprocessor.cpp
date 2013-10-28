#ifdef __WAND__
target[name[commentprocessor.o] type[object]]
#endif

#include "commentprocessor.h"
#include "doxytok.h"
#include "output.h"
#include <herbs/exceptionmissing.h>

void Doxymax::CommentProcessor::process(const Herbs::Tokenizer::TokenInfo& info)
	{
	if(info.tok_class==DoxyTok::ARG_BEGIN)
		{
		if(*info.buffer==CHAR('$'))
			{
			name=Herbs::String(info.buffer+1);
			m_classifier.whitespaceEatInc();
			}
		else
			{
			print(Herbs::String(info.buffer).append(info.delimiter));
			}
		return;
		}
		
	if(name.length())
		{
		switch(info.tok_class)
			{
			case DoxyTok::ARG_BEGIN:
				throw Herbs::ExceptionMissing(___FILE__,__LINE__);
			case DoxyTok::ARG_DELIM:
				print(Herbs::String(info.buffer).append(CHAR(';')));
				args.append(Herbs::String(info.buffer));
				return;
			case DoxyTok::ARG_END:
				print(Herbs::String(info.buffer));
				args.append(Herbs::String(info.buffer));
				name.clear();
				m_classifier.whitespaceEatDec();
				return;
			default:
				throw Herbs::ExceptionMissing(___FILE__,__LINE__);
			}
		}
	else
		{print(Herbs::String(info.buffer).append(info.delimiter));}
	}
