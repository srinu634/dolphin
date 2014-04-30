# Run this script on a folder with n Documents
# It generates a sorted output for each document with the numbering system as follows:
#	1st document in ls is sorted as 0.txt
#	2nd document in ls is sorted as 1.txt .........
# This is done so that the Indexing of term frequencies can be done in O(n) , where n is the document size*AVG(Word Length) . Of course, Sorting takes O(nlogn).
#Also, all capital are converted to small case

declare -i count=0 #Number of documents indexed

g++ doc_sort.cpp -o doc_sort.out  #Sorts a given file in dictionary style.
mkdir temp #Create a Temp Directory to store the sorted documents 
echo "temp folder is created,Sorting each file is about to get started"

while [ "$count" -lt 199328 ]   #199328
	do 
		echo "Sorted: ./data/$count.txt to ./temp/$count.txt"
		./doc_sort.out < ./data/$count.txt   > temp1.txt
		sort -r temp1.txt > temp2.txt
		cp temp2.txt  ./temp/$count.txt
		count=count+1	
	done
rm temp1.txt temp2.txt
echo "Finished Sorting every file"
