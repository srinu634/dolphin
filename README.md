Vector Space Model : Information Retrieval

Implementation Details:
-> A Global Hash Table for term document frequency.
-> A simple linear linked list for each ducument to store the term frequencies
-> Owing to the fact that VSM does not take context into picture , We can sort the document to generate the linear linked list.
	Make sure you have the original document for retrieval process.
	To save space,Make sure you delete this sorted file once you have indexed that document.
-> The Documents are then length Normalised
-> Score is as follows:  log(1+tf) * log(n/dft) 
	where tf is the term frequency
	dft is the term document frequency 
-> When a Phrase is queried, An Approach similar to N pointer Merge is used to calcuate score w.r.t to each document. 

