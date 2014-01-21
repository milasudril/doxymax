#ifdef __WAND__
dependencies[commentprocessor.o]
target[name[commentprocessor.h]type[include]]
#endif

#ifndef COMMENTPROCESSOR_H
#define COMMENTPROCESSOR_H

#include "tokenprocessor.h"
#include "macro.h"

#include <map>

namespace Doxymax
	{
	class DoxyTok;
	class Expander;
	
	class CommentProcessor:public TokenProcessor
		{
		public:
			CommentProcessor(DoxyTok& classifier,const Herbs::String& name_scope);
			~CommentProcessor();
			
			void process(const Herbs::Tokenizer::TokenInfo& info);
			
			void labelSet(const Herbs::String& label,size_t counter);
			size_t labelGet(const Herbs::String& label);
			void counterSet(const char_t* name,size_t value);
			size_t counterGet(const char_t* name);

			void expanderRegister(const char_t* name,Expander& expander);
			
		private:
			DoxyTok& m_classifier;	
			
			Herbs::String m_name_scope;
			
			std::map<Herbs::String,size_t> counters;
			std::map<Herbs::String,size_t> labels;
			std::map<Herbs::String,Expander*> expanders;
			
			Macro macro_current;
		};
	}

#endif
