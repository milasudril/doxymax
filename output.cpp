#ifdef __WAND__
target[name[output.o] type[object]]
#endif

#include "output.h"

#include <herbs/string/string.h>
#include <herbs/textconverter/textconverter.h>
#include <cstdio>

namespace
	{
	Herbs::Stringbase<char> toUTF8(const Herbs::String& str)
		{
		Herbs::TextConverter converter(ENCODING_LOCAL,Herbs::TextConverter::Encoding::UTF_8);
		size_t length_in=str.length();
		Herbs::Stringbase<char> ret(converter.lengthFactorGet()*length_in);
		size_t n_bytes=converter.convert(str.begin(),ret.begin(),length_in*sizeof(char_t));
		ret.lengthValidSet(n_bytes/sizeof(charsys_t));
		return ret;
		}
	}

void Doxymax::print(const Herbs::String& string)
	{
	fputs(toUTF8(string).begin(),stdout);
	}
