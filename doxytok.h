#ifdef __WAND__
dependency[doxytok.o]
target[name[doxytok.h] type[include]]
#endif

#ifndef DOXYTOK_H
#define DOXYTOK_H

#include <herbs/tokenizer/tokenizer.h>

namespace Doxymax
	{
	class DoxyTok:public Herbs::Tokenizer::CharClassifier
		{
		public:
			DoxyTok():whitespace_eat(0),ch_buff{0,0},char_literal(0)	
			,in_string(0),escape_next(0)
				{}
				
			Herbs::Tokenizer::tokclass_t charClassify(char_t delimiter);
				
			bool inString() const
				{return in_string;}
				
			void whitespaceEatInc()
				{++whitespace_eat;}
				
			void whitespaceEatDec()
				{--whitespace_eat;}
			
			static const
			Herbs::Tokenizer::tokclass_t SPACE=Herbs::Tokenizer::RESERVED_MAX+1;
			
			static const
			Herbs::Tokenizer::tokclass_t NEWLINE=Herbs::Tokenizer::RESERVED_MAX+2;
			
			static const
			Herbs::Tokenizer::tokclass_t ARG_BEGIN=Herbs::Tokenizer::RESERVED_MAX+3;
			
			static const
			Herbs::Tokenizer::tokclass_t ARG_DELIM=Herbs::Tokenizer::RESERVED_MAX+4;
			
			static const
			Herbs::Tokenizer::tokclass_t ARG_END=Herbs::Tokenizer::RESERVED_MAX+5;
			
			static const
			Herbs::Tokenizer::tokclass_t BLOCK_BEGIN=Herbs::Tokenizer::RESERVED_MAX+6;
			
			static const
			Herbs::Tokenizer::tokclass_t BLOCK_END=Herbs::Tokenizer::RESERVED_MAX+7;
		
		private:
			void moveNext(char_t delimiter)
				{
				ch_buff[0]=ch_buff[1];
				ch_buff[1]=delimiter;
				}

			size_t whitespace_eat;
			char_t ch_buff[2];
			bool char_literal;
			bool in_string;
			bool escape_next;
		};
	}
#endif
