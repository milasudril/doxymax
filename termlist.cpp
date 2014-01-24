#ifdef __WAND__
target[name[termlist.o] type[object]]
#endif

#include "termlist.h"
#include "output.h"
#include "commentprocessor.h"

#include <herbs/intformat/intformat.h>
#include <herbs/exceptionmissing/exceptionmissing.h>

namespace
	{
	class TermPrinter:public Doxymax::CommentProcessor::DefsEnumCallback
		{
		public:
			TermPrinter(Herbs::String& buffer):m_buffer(buffer){}
			bool operator()(const Herbs::String& term,const Herbs::String& def)
				{
				m_buffer.append(STR("<tr><td class=\"termdef\">")).append(term)
					.append(STR("</td><td>"))
					.append(def).append(STR("</td></tr>"));
				m_buffer.terminate();
				Doxymax::print(m_buffer);
				return 1;
				}
		private:
			Herbs::String& m_buffer;
		};
	}

void Doxymax::TermList::expand(const Macro& macro,CommentProcessor& processor)
	{
	Herbs::String str_out(128);
	str_out.append(STR("<table class=\"doxtable\" style=\"margin-left:auto;margin-right:auto;\">"));
	print(str_out);
	str_out.clear();

	str_out.append(STR("<tr>"))
		.append(STR("<th>Term</th></th><th>Definition</th>"))
		.append(STR("</tr>"));
	str_out.terminate();
	print(str_out);
	str_out.clear();
	
	TermPrinter printer(str_out);
	processor.definitionsEnum(printer);
	

	
	}
