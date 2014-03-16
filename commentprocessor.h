#ifdef __WAND__
dependency[commentprocessor.o]
target[name[commentprocessor.h]type[include]]
#endif

#ifndef COMMENTPROCESSOR_H
#define COMMENTPROCESSOR_H

#include "tokenprocessor.h"

#include <herbs/string/string.h>
#include <herbs/stack/stack.h>

#include <map>

namespace Doxymax
	{
	class DoxyTok;
	class Expander;
	class Macro;
	
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
			
			size_t macroExpansionDepth() const
				{return nodes.depth();}
			
			
			const Herbs::String* definitionGet(const Herbs::String& term) const;
			void definitionSet(const Herbs::String& term,const Herbs::String& def);
			
			class DefsEnumCallback
				{
				public:
					virtual bool operator()(const Herbs::String& term
						,const Herbs::String& def)=0;
				};			
			bool definitionsEnum(DefsEnumCallback& defenum) const;

			void expanderRegister(const char_t* name,Expander& expander);
			
			
		private:
			DoxyTok& m_classifier;	
			Herbs::String m_name_scope;
			std::map<Herbs::String,Expander*> expanders;			
			struct Node;				
			Herbs::Stack<Node*> nodes;
			Node* node_current;
			
			std::map<Herbs::String,size_t> counters;
			std::map<Herbs::String,size_t> labels;
			std::map<Herbs::String,Herbs::String> terms;
		};
	}

#endif
