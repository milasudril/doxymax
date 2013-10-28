#ifdef __WAND__
dependencies[commentprocessor.o]
target[name[commentprocessor.h]type[include]]
#endif

#ifndef COMMENTPROCESSOR_H
#define COMMENTPROCESSOR_H

#include "tokenprocessor.h"

#include <herbs/string.h>

namespace Doxymax
	{
	class DoxyTok;
	
	class CommentProcessor:public TokenProcessor
		{
		public:
			CommentProcessor(DoxyTok& classifier):m_classifier(classifier)
			,is_string(0)
				{}
		
			void process(const Herbs::Tokenizer::TokenInfo& info);
		
		private:
			DoxyTok& m_classifier;
			Herbs::String name;
			Herbs::Array<Herbs::String> args;
			bool is_string;
		};
	}

#endif
