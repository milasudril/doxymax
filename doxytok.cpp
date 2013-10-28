#ifdef __WAND__
target[name[doxytok.o]type[object]]
#endif

#include "doxytok.h"

Herbs::Tokenizer::tokclass_t Doxymax::DoxyTok::charClassify(char_t delimiter)
	{
	if(escape_next)
		{
		escape_next=0;
		moveNext(delimiter);
		return Herbs::Tokenizer::NO_DELIMITER;
		}
		
	if(char_literal)
		{
		switch(delimiter)
			{
			case CHAR('\\'):
				escape_next=1;
				moveNext(delimiter);
				return  Herbs::Tokenizer::NO_DELIMITER;
			case CHAR('\''):
				char_literal=0;
				moveNext(delimiter);
				return Herbs::Tokenizer::NO_DELIMITER;
			default:
				moveNext(delimiter);
				return Herbs::Tokenizer::NO_DELIMITER;
			}				
		}
		
	if(in_string)
		{
		switch(delimiter)
			{
			case CHAR('\\'):
				escape_next=1;
				moveNext(delimiter);
				return Herbs::Tokenizer::NO_DELIMITER;
			case CHAR('"'):
				in_string=0;
				moveNext(delimiter);
				return Herbs::Tokenizer::NO_DELIMITER;
			default:
				moveNext(delimiter);
				return Herbs::Tokenizer::NO_DELIMITER;
			}	
		}

	if(ch_buff[0]==CHAR('/') && ch_buff[1]==CHAR('*') && delimiter==CHAR('*'))
		{
		moveNext(delimiter);
		return BLOCK_BEGIN;
		}
	
	if(ch_buff[1]==CHAR('*') && delimiter==CHAR('/'))
		{
		moveNext(delimiter);
		return BLOCK_END;
		}
	
	if(delimiter>=CHAR('\0') && delimiter<=CHAR(' ') && delimiter!=CHAR('\n'))
		{
		moveNext(delimiter);
		if(whitespace_eat)
			{return Herbs::Tokenizer::SKIP;}
		else
			{return SPACE;}
		}

	switch(delimiter)
		{
		case CHAR('\''):
			char_literal=!char_literal;
			moveNext(delimiter);
			return Herbs::Tokenizer::NO_DELIMITER;
		case CHAR('"'):
			in_string=!in_string;
			moveNext(delimiter);
			return Herbs::Tokenizer::NO_DELIMITER;
		case CHAR('\n'):
			moveNext(delimiter);
			return NEWLINE;
		case CHAR('('):
			moveNext(delimiter);
			return ARG_BEGIN;
		case CHAR(','):
			moveNext(delimiter);
			return ARG_DELIM;
		case CHAR(')'):
			moveNext(delimiter);
			return ARG_END;
		default:
			moveNext(delimiter);
			return Herbs::Tokenizer::NO_DELIMITER;
		}
	}
