#include "hash.h"

int main ()
{

	char str[1000];

	initialise_hash();

	while(true){
		if( !(cin>>str) )
			break;
		if(lookup(str) == false)
			add(str);
	}//while

	print_hashtable();

  return 0;
}
