#ifdef __WAND__
target[name[doxymax.exe] type[application] platform[;Windows]]
target[name[doxymax] type[application]]
#endif

#include "doxytok.h"
#include "codeprocessor.h"
#include "commentprocessor.h"

#include "figure.h"
#include "ref.h"
#include "tablebegin.h"
#include "tableend.h"
#include "tableheader.h"
#include "tablerow.h"
#include "termref.h"
#include "termdef.h"
#include "termlist.h"
#include "unquote.h"
#include "old.h"
#include "paragraph.h"
#include "paragraph_end.h"
#include "item.h"
#include "notecond.h"

#include <herbs/main/main.h>
#include <herbs/filein/filein.h>
#include <herbs/tokenizer/tokenizer.h>
#include <herbs/textdecoder/textdecoder.h>
#include <herbs/exception/exception.h>
#include <herbs/logwriterstdout/logwriterstdout.h>
#include <herbs/stringsys/stringsys.h>

int MAIN(int argc,charsys_t* argv[])
	{
	Herbs::LogWriterStdout errlog;
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
		Doxymax::TermRef term_ref;
		Doxymax::TermDef term_def;
		Doxymax::TermList term_list;
		Doxymax::Unquote unquote;
		Doxymax::Old old;
		Doxymax::Paragraph paragraph;
		Doxymax::ParagraphEnd paragraph_end;
		Doxymax::Item item;
		Doxymax::NoteCond notecond;
		
		comment.expanderRegister(STR("figure"),figure);
		comment.expanderRegister(STR("ref"),ref);
		comment.expanderRegister(STR("table_begin"),table_begin);
		comment.expanderRegister(STR("table_end"),table_end);
		comment.expanderRegister(STR("table_header"),table_header);
		comment.expanderRegister(STR("table_row"),table_row);
		comment.expanderRegister(STR("term_ref"),term_ref);
		comment.expanderRegister(STR("term_def"),term_def);
		comment.expanderRegister(STR("term_list"),term_list);
		comment.expanderRegister(STR("unquote"),unquote);
		comment.expanderRegister(STR("old"),old);
		comment.expanderRegister(STR("paragraph"),paragraph);
		comment.expanderRegister(STR("paragraph_end"),paragraph_end);
		comment.expanderRegister(STR("item"),item);
		comment.expanderRegister(STR("notecond"),notecond);
		
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
