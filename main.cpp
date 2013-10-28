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
#include <herbs/exceptionmissing.h>

//Currently, Herbs lacks support for standard stream I/O. Therefore, 
#include <cstdio>

class DoxyTok:public Herbs::Tokenizer::CharClassifier
	{
	public:
		DoxyTok():whitespace_eat(0),ch_buff{0,0},char_literal(0)	
		,in_string(0),escape_next(0)
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
						return Herbs::Tokenizer::NO_DELIMITER;
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
				if(whitespace_eat)
					{return Herbs::Tokenizer::SKIP;}
				else
					{return SPACE;}
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
			
		bool inString() const
			{return in_string;}
			
		void whitespaceEatInc()
			{++whitespace_eat;}
			
		void whitespaceEatDec()
			{--whitespace_eat;}
		
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

		size_t whitespace_eat;
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
		CommentProcessor(DoxyTok& classifier):m_classifier(classifier)
		,is_string(0)
			{}
			
		void process(const Herbs::Tokenizer::TokenInfo& info)
			{
			if(info.tok_class==DoxyTok::ARG_BEGIN)
				{
				if(*info.buffer==CHAR('$'))
					{
					name=Herbs::String(info.buffer+1);
					m_classifier.whitespaceEatInc();
					}
				else
					{printf("%s%c",toUTF8(info.buffer).begin(),info.delimiter);}
				return;
				}
				
			if(name.length())
				{
				switch(info.tok_class)
					{
					case DoxyTok::ARG_BEGIN:
						throw Herbs::ExceptionMissing(___FILE__,__LINE__);
					case DoxyTok::ARG_DELIM:
						printf("arg[%s]",toUTF8(info.buffer).begin());
						args.append(Herbs::String(info.buffer));
						return;
					case DoxyTok::ARG_END:
						printf("arg[%s]",toUTF8(info.buffer).begin());
						args.append(Herbs::String(info.buffer));
						name.clear();
						m_classifier.whitespaceEatDec();
						return;
					default:
						throw Herbs::ExceptionMissing(___FILE__,__LINE__);
					}
				}
			else
				{printf("%s%c",toUTF8(info.buffer).begin(),info.delimiter);}
			}

	private:
		DoxyTok& m_classifier;
		Herbs::String name;
		Herbs::Array<Herbs::String> args;
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
		
		CommentProcessor comment(classifier);
		CodeProcessor code;
		TokenProcessor* processor_current=&code;

		while (tok.tokenGet())
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
					break;
				default:
					processor_current->process(info);
				}
			}
		}
	catch(Herbs::Exception& err)
		{
		err.print(errlog);
		return -1;
		}
	
	return 0;
	}
