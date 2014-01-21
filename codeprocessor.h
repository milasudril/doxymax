#ifdef __WAND__
dependencies[codeprocessor.o]
target[name[codeprocessor.h]type[include]]
#endif

#ifndef CODEPROCESSOR_H
#define CODEPROCESSOR_H

#include "tokenprocessor.h"

namespace Doxymax
	{
	class CodeProcessor:public TokenProcessor
		{
		public:
			void process(const Herbs::Tokenizer::TokenInfo& info);
		};
	}

#endif
