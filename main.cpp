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

const char* bajs="nullptr\\\"";

class DoxyTok:public Herbs::Tokenizer::CharClassifier
	{
	public:
		DoxyTok():ch_buff{0,0},char_literal(0),in_string(0),escape_next(0)
			{}
			
		Herbs::Tokenizer::tokclass_t charClassify(char_t delimiter)
			{
			if(escape_next)
				{
				escape_next=0;
				moveNext(delimiter);
				return Herbs::Tokenizer::NO_DELIMITER;
				}
				
			if(char_literal)
				{
				switch(delimiter)
					{
					case CHAR('\\'):
						escape_next=1;
						moveNext(delimiter);
						return  Herbs::Tokenizer::NO_DELIMITER;
					case CHAR('\''):
						char_literal=0;
						moveNext(delimiter);
						return CHARLIT_TOGGLE;
					default:
						moveNext(delimiter);
						return Herbs::Tokenizer::NO_DELIMITER;
					}				
				}
				
			if(in_string)
				{
				switch(delimiter)
					{
					case CHAR('\\'):
						escape_next=1;
						moveNext(delimiter);
						return  Herbs::Tokenizer::NO_DELIMITER;
					case CHAR('"'):
						in_string=0;
						moveNext(delimiter);
						return STRING_TOGGLE;
					default:
						moveNext(delimiter);
						return Herbs::Tokenizer::NO_DELIMITER;
					}	
				}

			if(ch_buff[0]==CHAR('/') && ch_buff[1]==CHAR('*') && delimiter==CHAR('*'))
				{
				moveNext(delimiter);
				return BLOCK_BEGIN;
				}
			
			if(ch_buff[1]==CHAR('*') && delimiter==CHAR('/'))
				{
				moveNext(delimiter);
				return BLOCK_END;
				}
			
			if(delimiter>=CHAR('\0') && delimiter<=CHAR(' ') && delimiter!=CHAR('\n'))
				{
				moveNext(delimiter);
				return SPACE;
				}
	
			switch(delimiter)
				{
				case CHAR('\''):
					char_literal=!char_literal;
					moveNext(delimiter);
					return CHARLIT_TOGGLE;
				case CHAR('"'):
					in_string=!in_string;
					moveNext(delimiter);
					return STRING_TOGGLE;
				case CHAR('\n'):
					moveNext(delimiter);
					return NEWLINE;
				case CHAR('('):
					moveNext(delimiter);
					return ARG_BEGIN;
				case CHAR(','):
					moveNext(delimiter);
					return ARG_DELIM;
				case CHAR(')'):
					moveNext(delimiter);
					return ARG_END;
				default:
					moveNext(delimiter);
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
		
		static const
		Herbs::Tokenizer::tokclass_t BLOCK_BEGIN=Herbs::Tokenizer::RESERVED_MAX+6;
		
		static const
		Herbs::Tokenizer::tokclass_t BLOCK_END=Herbs::Tokenizer::RESERVED_MAX+7;
		
		static const
		Herbs::Tokenizer::tokclass_t STRING_TOGGLE=Herbs::Tokenizer::RESERVED_MAX+8;
		
		static const
		Herbs::Tokenizer::tokclass_t CHARLIT_TOGGLE=Herbs::Tokenizer::RESERVED_MAX+9;
		
	private:
		void moveNext(char_t delimiter)
			{
			ch_buff[0]=ch_buff[1];
			ch_buff[1]=delimiter;
			}
	
		char_t ch_buff[2];
		bool char_literal;
		bool in_string;
		bool escape_next;
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

class ParseMode
	{
	public:
		virtual void process(const Herbs::Tokenizer::TokenInfo& tokinfo)=0;
	};

/**The"main" function. $label(name)
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
		Herbs::Tokenizer tok(decoder,classifier,16,CHAR('\0'));
		const Herbs::Tokenizer::TokenInfo& info=tok.infoGet();
		
		bool in_comment=0;
		bool in_string=0;

		while(tok.tokenGet())
			{
			switch(info.tok_class)
				{
				case DoxyTok::STRING_TOGGLE:
					in_string=!in_string;
					if(!in_comment)
						{
						printf("[%s]",toUTF8(info.buffer).begin());
						putchar(info.delimiter);
						}
				//	fputs(toUTF8(info.buffer).begin(),stdout);
				//	putchar(info.delimiter);
					break;
				case DoxyTok::BLOCK_BEGIN:
					if(!in_string)
						{in_comment=1;}
					fputs("/**",stdout);
					break;
				case DoxyTok::BLOCK_END:
					if(!in_string)
						{in_comment=0;}
					fputs("*/",stdout);
					break;
				default:
					if(in_comment)
						{
						if(*info.buffer || info.delimiter==CHAR('\n'))
							{
							printf("[%s]",toUTF8(info.buffer).begin());
							putchar(info.delimiter);
							}
						}
					else
						{
						printf("[%s]",toUTF8(info.buffer).begin());
						putchar(info.delimiter);
						}
				}
			}
		}
	catch(Herbs::Exception& err)
		{
		err.print(errlog);
		}
	
	return 0;
	}
