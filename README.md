Vector Space Model : Information Retrieval<br><br>

Implementation Details:<br>
-> A Global Hash Table for term document frequency.<br>
-> A simple linear linked list for each ducument to store the term frequencies<br>
-> Owing to the fact that VSM does not take context into picture , We can sort the document to generate the linear linked list.<br>
	Make sure you have the original document for retrieval process.<br>
	To save space,Make sure you delete this sorted file once you have indexed that document.<br>
-> The Documents are then length Normalised<br>
-> Score is as follows:  log(1+tf) * log(n/dft) <br>
	where tf is the term frequency<br>
	dft is the term document frequency <br>
-> When a Phrase is queried, An Approach similar to N pointer Merge is used to calcuate score w.r.t to each document.<br>


Code Explained: <br>
-> hash.h is the header file for the hash table <br>
-> doc_gen.sh is the script file written to generate sorted ( in a new folder called temp) <br>
-> doc_sort.cpp is the actual file which sorts each file one by one <br>
	( which is used in doc_gen.sh) <br>
-> inverted_index.h contains all the functions required to build the inverted index for each file<br>
-> dolphin.cpp is the file where Global Hash Tables are built, Inverted Indexes are built and Queries are Processed<br>

How to run it?<br>
-> Copy files in a folder called docs<br>
-> run doc_gen.sh<br>
-> run dolphin.cpp<br>


PROBLEMS i faced:<br>
1) Unicode problem , solution i found : wchar_t <br>
2) xml text extraction when the file is really big ?? <br>



