#ifdef __WAND__
target[name[doxymax.exe] type[application]]
#endif

#include <herbs/main.h>
#include <herbs/filein.h>
#include <herbs/stringsys.h>
#include <herbs/tokenizer.h>
#include <herbs/textdecoder.h>
#include <herbs/textconverter.h>
#include <herbs/exception.h>
#include <herbs/messageprinterstdio.h>
#include <cstdio>

class DoxyTok:public Herbs::Tokenizer::CharClassifier
	{
	public:
		Herbs::Tokenizer::tokclass_t charClassify(char_t delimiter)
			{
		//	TODO skip everything expect text between /** and */
			if(delimiter>=CHAR('\0') && delimiter<=CHAR(' ') && delimiter!=CHAR('\n'))
				{
				return SPACE;
				}
			switch(delimiter)
				{
				case CHAR('\n'):
					return NEWLINE;
				case CHAR('('):
					return ARG_BEGIN;
				case CHAR(','):
					return ARG_DELIM;
				case CHAR(')'):
					return ARG_END;
				default:
					return Herbs::Tokenizer::NO_DELIMITER;
				}
			}
		
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
	};

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

/**The main function. $label(name)
*/
int MAIN(int argc,charsys_t* argv[])
	{
	Herbs::MessagePrinterStdio errlog(Herbs::StreamSpec::STDERR);
	try
		{
		if(argc<2)
			{return -1;}
		
		Herbs::FileIn src(Herbs::Path(Herbs::stringloc(argv[1])));
		Herbs::TextDecoder decoder(src);
		DoxyTok classifier;
		Herbs::TextConverter converter();
		Herbs::Tokenizer tok(decoder,classifier,16,CHAR('\\'));
		const Herbs::Tokenizer::TokenInfo& info=tok.infoGet();
		
		while(tok.tokenGet())
			{
			if(*info.buffer)
				{puts(toUTF8(info.buffer).begin());}
			}
		}
	catch(Herbs::Exception& err)
		{
		err.print(errlog);
		}
	
	return 0;
	}
