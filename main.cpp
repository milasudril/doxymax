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
						return Herbs::Tokenizer::NO_DELIMITER;
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
						return Herbs::Tokenizer::NO_DELIMITER;
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
					return Herbs::Tokenizer::NO_DELIMITER;
				case CHAR('"'):
					in_string=!in_string;
					moveNext(delimiter);
					return Herbs::Tokenizer::NO_DELIMITER;
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
		
		bool inString() const
			{return in_string;}
		
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

class TokenProcessor
	{
	public:
		virtual void process(const Herbs::Tokenizer::TokenInfo& tokinfo)=0;
	};

class CodeProcessor:public TokenProcessor
	{
	public:
		void process(const Herbs::Tokenizer::TokenInfo& info)
			{
			printf("%s%c",toUTF8(info.buffer).begin(),info.delimiter);
			}
	};
	
class CommentProcessor:public TokenProcessor
	{
	public:
		CommentProcessor():class_prev(Herbs::Tokenizer::NO_DELIMITER),is_string(0)
			{}
			
		void process(const Herbs::Tokenizer::TokenInfo& info)
			{
			switch(info.tok_class)
				{					
				case DoxyTok::ARG_BEGIN:
					if(*info.buffer==CHAR('$'))
						{name=Herbs::String(info.buffer+1);}
					else
						{printf("%s%c",toUTF8(info.buffer).begin(),info.delimiter);}
					break;
				
				case DoxyTok::ARG_DELIM:
					if(name.length())
						{args.append(Herbs::String(info.buffer));}
					else
						{printf("%s%c",toUTF8(info.buffer).begin(),info.delimiter);}
					break;
				
				case DoxyTok::ARG_END:
					if(name.length())
						{
						args.append(Herbs::String(info.buffer));
							{
							Herbs::String* ptr=args.begin();
							printf("%s: ",toUTF8(name.begin()).begin());
							while(ptr!=args.end())
								{
								printf("%s ",toUTF8(ptr->begin()).begin());
								++ptr;
								}
							}
						name.clear();
						}
					else
						{printf("%s%c",toUTF8(info.buffer).begin(),info.delimiter);}
					break;
					
				default:
					printf("%s%c",toUTF8(info.buffer).begin(),info.delimiter);
				}
			}

	private:
	
		Herbs::String name;
		Herbs::Array<Herbs::String> args;
		Herbs::Tokenizer::tokclass_t class_prev;
		bool is_string;
	};

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
		
		CommentProcessor comment;
		CodeProcessor code;
		TokenProcessor* processor_current=&code;

		while(tok.tokenGet())
			{
			switch(info.tok_class)
				{
				case DoxyTok::BLOCK_BEGIN:
					processor_current->process(info);
					if(!classifier.inString())
						{processor_current=&comment;}
					break;
				case DoxyTok::BLOCK_END:
					processor_current->process(info);
					if(!classifier.inString())
						{processor_current=&code;}
				//	fputs("*/",stdout);
					break;
				default:
					processor_current->process(info);
				}
			}
		}
	catch(Herbs::Exception& err)
		{
		err.print(errlog);
		}
	
	return 0;
	}
