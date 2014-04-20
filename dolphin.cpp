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

struct doc_node{
    double dot_prod;  // Normalised Dot Product
    int doc_no;
}D[MAXDOCS];


struct query_node{
    char *qword; // to store each word of the query
    double score;
} Q[100];

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

      /*      cout<<str<<" "<<fre<<endl;
              Uncomment this for better debugging
      */
        }//while
        // cout<<"length is: "<<len[i]<<endl;
        fclose(fp);
        len[i] = sqrt(len[i]);
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
            len[i] += res*res;
        }//while
        len[i] = sqrt(len[i]);
    }//for

}//scores


int main(){

    int i,i1,i2,j; //iterators
    int doc_count;


    initialise_hash();
    initialise_inv_index();


    doc_count = 8;
    build_index(doc_count);  //Global Hash Table + Inverted Index are built
    calculate_scores(doc_count); //Update score for each term in every document


    //print_tables(doc_count);

    for(i=0;i<100;i++)
        Q[i].qword = (char *)( malloc(sizeof(char) *200) );

    while(true){         //ONLINE PROCESSING
        cout<<"Enter the phrase query: (End it with a ; )"<<endl;
        int fre_qw; //frequency query words
        fre_qw=0;

        while(true){
            cin>>Q[fre_qw].qword;
            if( strcmp(Q[fre_qw].qword,";") == 0)
                break;
            fre_qw++;
        }

        cout<<"Tokenizing Phrase Query: "<<endl;

       for(i1=0;i1<fre_qw-1;i1++)
        for(i2=0;i2<fre_qw-1;i2++)
            if( strcmp(Q[i2].qword,Q[i2+1].qword) > 0 )
                swap(Q[i2],Q[i2+1]);        //Bubble sort as query is supposedly small and does not exceed 10 words at max
                                                    // No Point in doing Quick/Merge for such a small input size

       for(i=0;i<fre_qw;i++)
            cout<<Q[i].qword<<endl , Q[i].score = 2.33;  //To avoid Truncated Integer Values

        cout<<"Done Tokenizing"<<endl;

        for(i1=0;i1<doc_count;i1++)
            D[i1].dot_prod=0 , D[i1].doc_no = i1;

        double qlen;  //Normalised Query Vector
        qlen = 0;

        for(i=0;i<fre_qw;i++){
            Q[i].score = doc_count;
            Q[i].score /= get_fre( Q[i].qword );
            Q[i].score = log( Q[i].score ) < 0 ? 0 : log( Q[i].score );
            qlen += Q[i].score*Q[i].score;
        }

        qlen = sqrt(qlen);

        /*cout<<qlen<<endl;

         for(i=0;i<fre_qw;i++){
            cout<<Q[i].qword<<" "<<Q[i].score<<endl;
         }*/



    }//Infinite While Loop

    return 0;
    }//main



//  NOTE:
//          AS EACH WORD IN A QUERY IS GENERALLY REPEATED ONLY ONCE,TERM FREQUENCY OF QUERY IS NOT CONSIDERED.
