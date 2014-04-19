# Run this script on a folder with n Documents
# It generates a sorted output for each document with the numbering system as follows:
#	1st document in ls is sorted as 0.txt
#	2nd document in ls is sorted as 1.txt .........
# This is done so that the Indexing of term frequencies can be done in O(n) , where n is the document size*AVG(Word Length) . Of course, Sorting takes O(nlogn).

declare -i count=0 #Number of documents to be indexed
declare -i remaining=8 
fname="temp"

g++ doc_sort.cpp -o doc_sort.out  #Sorts a given file in dictionary style.
mkdir temp #Create a Temp Directory to store the sorted documents 
echo "temp folder is created,Sorting each file is about to get started"

while [ 2 -eq 2 ]   # Always true with a break condition inside
	do 
		if [ $remaining -eq 0 ];then
			break;
		fi
		fname=$(ls ./docs | head -n $remaining | tail -n 1  )
		count=count+1
		remaining=remaining-1
		echo "Sorted: $fname to $remaining.txt"
		./doc_sort.out < ./docs/$fname > temp.txt 
		sort temp.txt	> ./temp/"$remaining.txt"  #The Awesomely Written CPP Program :)
	done
rm temp.txt
echo "Finished Sorting every file"
