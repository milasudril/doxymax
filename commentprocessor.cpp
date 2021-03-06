#ifdef __WAND__
target[name[commentprocessor.o] type[object]]
#endif

#include "commentprocessor.h"
#include "doxytok.h"
#include "output.h"
#include "expander.h"
#include "macro.h"

#include <herbs/exceptionmissing/exceptionmissing.h>
#include <herbs/filein/filein.h>
#include <herbs/fileout/fileout.h>
#include <herbs/fileutils/fileutils.h>

namespace
	{
	bool load(Herbs::StreamIn& source,size_t& value)
		{
		if(source.read(&value,sizeof(value))!=sizeof(value))
			{return 0;}
		return 1;
		}
		
	bool load(Herbs::StreamIn& source,Herbs::String& value)
		{
		size_t length;
		if(!load(source,length))
			{return 0;}
			
		value=Herbs::String(length);
		if(source.read(value.begin(),length*sizeof(char_t))!=length*sizeof(char_t))
			{return 0;}
		value.lengthValidSet(length);
		return 1;
		}
	
	bool load(Herbs::StreamIn& source,std::map<Herbs::String,size_t>& map)
		{
		size_t count;
		if(!load(source,count))
			{return 0;}
		while(count)
			{
			Herbs::String key;
			if(!load(source,key))
				{return 0;}
			size_t value;
			if(!load(source,value))
				{return 0;}
			map[key]=value;
			--count;
			}
		return 1;
		}
	
	bool load(Herbs::StreamIn& source
		,std::map<Herbs::String,Herbs::String>& map)
		{
		size_t count;
		if(!load(source,count))
			{return 0;}
		while(count)
			{
			Herbs::String key;
			if(!load(source,key))
				{return 0;}
			Herbs::String value;
			if(!load(source,value))
				{return 0;}
			map[key]=value;
			--count;
			}
		return 1;
		}
		
	bool store(size_t x,Herbs::StreamOut& dest)
		{
		if(dest.write(&x,sizeof(x))!=sizeof(x))
			{return 0;}
		return 1;
		}
		
	bool store(const Herbs::String& string,Herbs::StreamOut& dest)
		{
		size_t l=string.length();
		if(!store(l,dest))
			{return 0;}
		if(dest.write(string.begin(),l*sizeof(char_t))!=l*sizeof(char_t))
			{return 0;}
		return 1;
		}
		
	bool store(const std::map<Herbs::String,size_t>& map,Herbs::StreamOut& dest)
		{
		if(!store(map.size(),dest))
			{return 0;}
		
		auto i=map.begin();
		while(i!=map.end())
			{
			if(!store(i->first,dest))
				{return 0;}
			if(!store(i->second,dest))
				{return 0;}
			++i;
			}
		return 1;
		}
	
	bool store(const std::map<Herbs::String,Herbs::String>& map
		,Herbs::StreamOut& dest)
		{
		if(!store(map.size(),dest))
			{return 0;}
		
		auto i=map.begin();
		while(i!=map.end())
			{
			if(!store(i->first,dest))
				{return 0;}
			if(!store(i->second,dest))
				{return 0;}
			++i;
			}
		return 1;
		}
		
	Herbs::String escape(const Herbs::String& string)
		{
		Herbs::String ret(string.length());
		const char_t* i=string.begin();
		while(i!=string.end())
			{
			if(*i==CHAR('/') || *i==CHAR('\\') || *i==CHAR(':') || *i==CHAR('?')
				|| *i==CHAR('#') || *i==CHAR('.'))
				{
				++i;
				continue;
				}
			ret.append(*i);
			++i;
			}
		return ret;
		}
		
	
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

	
struct Doxymax::CommentProcessor::Node
	{
	Macro macro;
	Herbs::String arg_str;
	};
	
Doxymax::CommentProcessor::CommentProcessor(DoxyTok& classifier
	,const Herbs::String& name_scope):
	m_classifier(classifier),m_name_scope(escape(name_scope))
	,node_current(nullptr)
	{
	Herbs::Fileutils::touch(Herbs::Path(STR("auxfile.dat")));
	Herbs::FileIn auxfile(Herbs::Path(STR("auxfile.dat")));
	if(!load(auxfile,counters))
		{return;}
	if(!load(auxfile,labels))
		{return;}
	if(!load(auxfile,terms))
		{return;}
	}
	
Doxymax::CommentProcessor::~CommentProcessor()
	{
	Herbs::FileOut auxfile(Herbs::Path(STR("auxfile.dat")));
	store(counters,auxfile);
	store(labels,auxfile);
	store(terms,auxfile);
	}

void Doxymax::CommentProcessor::process(const Herbs::Tokenizer::TokenInfo& info)
	{
	if(info.tok_class==DoxyTok::ARG_BEGIN)
		{
		if(*info.buffer==CHAR('$'))
			{
			nodes.push(node_current);
			node_current=new Node;
			node_current->macro.name=Herbs::String(info.buffer+1);
			return;
			}	
		}
		
	if(node_current!=nullptr)
		{
		switch(info.tok_class)
			{
			case DoxyTok::ARG_DELIM:
				node_current->arg_str.append(quoteKill(Herbs::String(info.buffer)));
				node_current->arg_str.terminate();
				node_current->macro.args.append(node_current->arg_str);
				node_current->arg_str.clear();
				return;
				
			case DoxyTok::ARG_END:
				{
				node_current->arg_str.append(quoteKill(Herbs::String(info.buffer)));
				node_current->arg_str.terminate();
				node_current->macro.args.append(node_current->arg_str);
				node_current->arg_str.clear();
			
				auto i=expanders.find(node_current->macro.name);
				Herbs::String ret;
				if(i!=expanders.end())
					{
					ret=i->second->expand(node_current->macro,*this);
					}
				else
					{ret=Herbs::String(STR("[Unknown macro]"));}
					
				if(nodes.depth())
					{
					delete node_current;
					node_current=nodes.pop();
					if(node_current==nullptr)
						{print(ret);}
					else
						{
						node_current->arg_str.append(ret);
						}
					}
				else
					{
					print(Herbs::String(STR("[Unterminated macro]")));
					}
				}
				return;
			
			case DoxyTok::SPACE:
				node_current->arg_str.append(quoteKill(Herbs::String(info.buffer)));
				return;
			}
		}
	else
		{
		print(Herbs::String(info.buffer).append(info.delimiter));
		}
	}

void Doxymax::CommentProcessor::labelSet(const Herbs::String& label,size_t counter)
	{
	labels[label]=counter;
	}

size_t Doxymax::CommentProcessor::labelGet(const Herbs::String& label)
	{
	return labels[label];
	}

void Doxymax::CommentProcessor::counterSet(const char_t* counter_name,size_t value)
	{
	counters[Herbs::String(counter_name)]=value;
	}

size_t Doxymax::CommentProcessor::counterGet(const char_t* name)
	{
	return counters[Herbs::String(name)];
	}

void Doxymax::CommentProcessor::expanderRegister(const char_t* name,Expander& expander)
	{
	expanders[Herbs::String(name)]=&expander;
	}

const Herbs::String* Doxymax::CommentProcessor::definitionGet(const Herbs::String& term) const
	{
	auto i=terms.find(term);
	if(i==terms.end())
		{return nullptr;}
	return &i->second;
	}

void Doxymax::CommentProcessor::definitionSet(const Herbs::String& term,const Herbs::String& def)
	{
	terms[term]=def;
	}

bool Doxymax::CommentProcessor::definitionsEnum(DefsEnumCallback& defenum) const
	{
	auto i=terms.begin();
	while(i!=terms.end())
		{
		if(!defenum(i->first,i->second))
			{return 0;}
		++i;
		}
	return 1;
	}
