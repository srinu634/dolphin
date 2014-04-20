/*
                Inverted Index is built
                Global Hash Table is populated
                SearchEngine where queries are processed
*/

#include "hash.h"
#include "inverted_index.h"
#include<cmath>
#include<cstring>
#include<cstdio>

double dot_prod[MAXDOCS];  //Length Normalised Dot Product

void build_index(int n){ // n #of documents

    char fname[100];
    char str[1000];
    int i,j,fre;
    FILE *fp;

    for(i=0;i<n;i++){

        sprintf(fname,"./temp/%d.txt",i);
        fp = fopen(fname,"r");

        while( fscanf(fp,"%s %d",str,&fre) != EOF ){
            if(lookup(str) == false)
                add(str); //Global Hash Table

            add_inv(i,str,fre); //Inverted Index
            len[i] += fre;

      /*      cout<<str<<" "<<fre<<endl;
              Uncomment this for better debugging
      */
        }//while
        // cout<<"length is: "<<len[i]<<endl;
        fclose(fp);

    }//for

}//build_index

void print_tables(int doc_count){
    int i;

    cout<<"Global Hash Table is: "<<endl;
    print_hashtable();

    cout<<"Inverted Index is: "<<endl;
    for(i=0;i<doc_count;i++)
        print_inv_list(inv_index[i]);
}

void  calculate_scores(int n){

    double res;
    int i,j,fre;
    struct inv_node * trav;

    for(i=0;i<n;i++){
        trav = inv_index[i];

        while(trav != NULL){
            fre = get_fre(trav->word); //From the global hash table
            res = n;
            res /=fre;
            res = log(res);
            res *= log(1+trav->fre);
            trav->score = res;
            trav = trav->next;
        }//while
    }//for

}//scores


int main(){

    int i,i1,i2,j; //iterators
    int doc_count;
    char *query[100]; // to store each word of the query


    initialise_hash();
    initialise_inv_index();


    doc_count = 8;
    build_index(doc_count);  //Global Hash Table + Inverted Index are built
    calculate_scores(doc_count); //Update score for each term in every document


//    print_tables(doc_count);

    for(i=0;i<100;i++)
        query[i] = (char *)( malloc(sizeof(char) *200) );

    while(true){         //ONLINE PROCESSING
        cout<<"Enter the phrase query: (End it with a ; )"<<endl;
        int fre_qw; //frequency query words
        fre_qw=0;

        while(true){
            cin>>query[fre_qw];
            if( strcmp(query[fre_qw],";") == 0)
                break;
            fre_qw++;
        }

       for(i1=0;i1<fre_qw-1;i1++)
        for(i2=0;i2<fre_qw-1;i2++)
            if( strcmp(query[i2],query[i2+1]) > 0 )
                swap(query[i2],query[i2+1]);        //Bubble sort as query is supposedly small and does not exceed 10 words at max
                                                    // No Point in doing Quick/Merge for such a small input size

       //for(i=0;i<fre_qw;i++)
         //   cout<<query[i]<<endl;

        for(i1=0;i1<doc_count;i1++)
            dot_prod[i1]=0;


    }

    return 0;
    }//main



//  NOTE:
//          AS EACH WORD IN A QUERY IS GENERALLY REPEATED ONLY ONCE,TERM FREQUENCY OF QUERY IS NOT CONSIDERED.
