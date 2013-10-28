#ifdef __WAND__
target[name[tokenprocessor.h]type[include]]
#endif

#ifndef TOKENPROCESSOR_H
#define TOKENPROCESSOR_H

#include <herbs/tokenizer.h>

namespace Doxymax
	{
	class TokenProcessor
		{
		public:
			virtual void process(const Herbs::Tokenizer::TokenInfo& tokinfo)=0;
		};
	}

#endif
