VssBase v0.1.0
=======

VssBase is a simple command line application designed to help those who still suffer using Visual Source Safe. If you have a working directory with some development that you can't remember, VssBase can help you on getting from your Visual Source Safe repository the "parent revision" from which you started this particular development.

VssBase reads the content of the vssver2.scc file that is placed in your Visual Source Safe working directory, identifies the parent version of each file under version control and creates a BAT file to get an entire copy of the parent revision from the Visual Source Safe repository.

With the copy of the parent revision in your computer, you can compare the files and figure out your changes.