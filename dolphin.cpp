/*
    Features:
                Inverted Index is built
                Global Hash Table is populated
                SearchEngine where queries are processed
*/

#include "hash.h"
#include "inverted_index.h"
#include<cmath>
#include<cstring>
#include<cstdio>


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

    int i1,i2; //iterators
    int doc_count;


    initialise_hash();
    initialise_inv_index();


    doc_count = 8;
    build_index(doc_count);  //Global Hash Table + Inverted Index are built

    calculate_scores(doc_count); //Update score for each term in every document


    print_tables(doc_count);



    return 0;
    }
