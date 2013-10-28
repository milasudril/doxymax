#ifdef __WAND__
target[name[doxymax.exe] type[application]]
#endif

#include <herbs/main.h>
#include <herbs/filein.h>
#include <herbs/tokenizer.h>
#include <herbs/textdecoder.h>
#include <herbs/exception.h>
#include <herbs/messageprinterstdio.h>
#include <herbs/stringsys.h>

#include "doxytok.h"
#include "codeprocessor.h"
#include "commentprocessor.h"

#include "figure.h"
#include "ref.h"
#include "tablebegin.h"
#include "tableend.h"
#include "tableheader.h"
#include "tablerow.h"

int MAIN(int argc,charsys_t* argv[])
	{
	Herbs::MessagePrinterStdio errlog(Herbs::StreamSpec::STDERR);
	try
		{
		if(argc<2)
			{return -1;}
		
		Herbs::FileIn src(Herbs::Path(Herbs::stringloc(argv[1])));
		Herbs::TextDecoder decoder(src);
		Doxymax::DoxyTok classifier;
		Herbs::Tokenizer tok(decoder,classifier,16,CHAR('\0'));
		const Herbs::Tokenizer::TokenInfo& info=tok.infoGet();
				
		Doxymax::CommentProcessor comment(classifier,src.nameGet());
		Doxymax::Figure figure;
		Doxymax::Ref ref;
		Doxymax::TableBegin table_begin;
		Doxymax::TableEnd table_end;
		Doxymax::TableHeader table_header;
		Doxymax::TableRow table_row;
		
		comment.expanderRegister(STR("figure"),figure);
		comment.expanderRegister(STR("ref"),ref);
		comment.expanderRegister(STR("table_begin"),table_begin);
		comment.expanderRegister(STR("table_end"),table_end);
		comment.expanderRegister(STR("table_header"),table_header);
		comment.expanderRegister(STR("table_row"),table_row);
		
		Doxymax::CodeProcessor code;
		Doxymax::TokenProcessor* processor_current=&code;
		
		while (tok.tokenGet())
			{
			switch(info.tok_class)
				{
				case Doxymax::DoxyTok::BLOCK_BEGIN:
					processor_current->process(info);
					if(!classifier.inString())
						{processor_current=&comment;}
					break;
				case Doxymax::DoxyTok::BLOCK_END:
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
