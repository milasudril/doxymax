doxymax
=======

doxymax is a macro processor intended to be used inside Doxygen [1] comment blocks. The need for such a processor raise from the fact that Doxygen currently seems to lack support for numerical references like "Figure 1" [2].


Installation
------------

doxymax relies on the Herbs interfaces and the Wand build tool. An implementation of Herbs and Wand can both be obtained from the Gabi project [3]. To install doxymax, run

    wand "flags[install] debugmode[off]"

	
Usage
-----

### Enable use of doxymax

To use doxymax, set `INPUT_FILTER` in `doxyfile` to `doxymax`. When running Doxygen on your project, it will then feed all data through doxymax.


### Macro syntax

A macro follows the syntax

    $macro_name( arg1, arg2, ... )
	
There must be no space between the `macro_name` and the opening parenthesis. Literal argument values should be enclosed with quotation marks. Argument values containing spaces must be enclosed wtih quotation marks.


### Maintaining counters

To keep track on label numbers, a file called `auxfile.dat` is created. This file will contain tables of all labels and counters after a Doxygen run. If labels were added since last run, Doxygen needs to be run again. If any label was changed, `auxfile.dat` needs to be removed and Doxygen needs to be run twice.


### Supported macros

This section lists all currently implemented macros. Arguments inside ´[´ and ´]´ are optional

#### figure &mdash; Inserts a figure

    $figure(filename, caption, label [,width[,height]])
	
#### ref &mdash; Inserts a reference to a label
	
	$ref(label)

#### table_begin &mdash; Starts a table

	$table_begin(caption, label)
	
#### table_header &mdash; Adds a column headers to current table

    $table_header(col1 [,col2[,...]])
	
#### table_row &mdash; Adds a row to current table

	$table_row(col1 [,col2[,...]])
	
#### table_end &mdash; Ends the current table

	$table_end()
	
### term_def &mdash; Defines a new term
	
	$term_def(name,name showed, description)
	
### term_ref &mdash; Referrs to a defined term

	$term_ref(name, name showed)
	
### term_list &mdash; Generates a list of all terms

	$term_list()
	
### unquote &mdash; Prints argument

	$unquote(argument)
	
Notes
------------

 * Eventhough the doxymax source is distributed under BSD 2-Clause license, compiling it together with the implementation of Herbs from the Gabi project will bound the compiled module to LGPL version 3 or later.
 
 * If there was an error when running doxymax, Doxygen seems to not report any error output from doxymax. Also Doxygen will keep running despite doxymax returns a non-zero status code. This is an issue in Doxygen rather than doxymax.
 
 * Any file mentioned in a macro will not be copied to the Doxygen output directory. Doing so requiers parsing of the current ´doxyfile´. This should be implemented in a future release.



[1]:http://www.doxygen.org

[2]:http://stackoverflow.com/questions/11799435/numbered-anchors-in-doxygen

[3]:http://http://milasudril.github.io/gabi/

