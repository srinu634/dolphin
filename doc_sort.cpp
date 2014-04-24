#include "hash.h"
#include<cstring>
#include<algorithm>

struct wnode {
char word[1000];
int fre;
}a[100000];


int cmpfun(struct wnode a,struct wnode b){
    //cout<<a.word<<" "<<b.word<<" "<<-strcmp(a.word,b.word)<<endl;
    return -strcmp(a.word,b.word) ;
}

int main ()
{

	char str[1000];
	char *tok;
    int i,n,j;

	initialise_hash();
    n = 0;

	while(true){
		if( !(cin>>str) )
			break;

        for(int i = 0; str[i]; i++){
            str[i] = tolower(str[i]);
            }

            //tokenise it,add tokens

            tok = strtok (str," ,.-~[]():'{};?*&$!@#-–/\"\\|‘’");
            while (tok != NULL)
                {
   //                 cout<<tok<<" "<<tok[0]<<endl;


                    if(tok != NULL &&  lookup(tok)==false)     // As " can't be tokenised,we have to remove it explicitly
                        add(tok);
                    tok = strtok (NULL, " ,.-~[]():'{};?*&$!@#-–/\"\\|‘’");
                }


	}//while

	for(i=0;i<MAX;i++){
        struct node *trav;
        trav = h[i];

        while(trav != NULL){
            strcpy(a[n].word,trav->word);
            a[n].fre = trav->fre;
    //        cout<<a[n].word<<" "<<a[n].fre<<endl;
            n++;
            trav = trav->next;
        }
	}


    for(i=0;i<n;i++)
        cout<<a[i].word<<" "<<a[i].fre<<endl;


  return 0;
}


/*

for(i=0;i<n;i++)
    for(j=0;j<n-1;j++)
        if(strcmp(a[j].word,a[j+1].word) < 0 )
            swap(a[j],a[j+1]);
            */
