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

