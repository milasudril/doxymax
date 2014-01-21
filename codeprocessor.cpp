#ifdef __WAND__
target[name[codeprocessor.o] type[object]]
#endif

#include "codeprocessor.h"

#include <herbs/string.h>
#include <herbs/textconverter.h>

//Currently, Herbs lacks support for standard stream I/O. Therefore, 
#include <cstdio>

static
Herbs::Stringbase<char> toUTF8(const char_t* str)
	{
	Herbs::TextConverter
		converter(ENCODING_LOCAL,Herbs::TextConverter::Encoding::UTF8);
	size_t length_in=Herbs::String::count(str);
	Herbs::Stringbase<char> ret(converter.lengthFactorGet()*length_in);
	size_t n_bytes=converter.convert(str,ret.begin()
		,length_in*sizeof(char_t));
	ret.lengthValidSet(n_bytes/sizeof(charsys_t));
	return ret;
	}

void Doxymax::CodeProcessor::process(const Herbs::Tokenizer::TokenInfo& info)
	{
	printf("%s%c",toUTF8(info.buffer).begin(),info.delimiter);
	}
