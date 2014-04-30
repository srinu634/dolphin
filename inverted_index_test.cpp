/*
Takes the docs in temp folder as input and builds a inverted index for each document.
*/

#include<iostream>
#include<algorithm>
#include<cstring>
#define MAXDOCS 2000
using namespace std;

struct inv_node{
    char *word;
    int fre;
    struct inv_node *next;
};


struct inv_node * inv_index[MAXDOCS];

void add(int inv_val,char str[],int fre){

    struct inv_node *temp;

    temp = inv_index[inv_val];


    inv_index[inv_val] = (struct inv_node  *) (struct inv_node *)malloc(sizeof(struct inv_node *) );

    inv_index[inv_val]->word = (char *)malloc(sizeof(char)*(5 + strlen(str)) );
    strcpy( inv_index[inv_val]->word ,str );
    inv_index[inv_val]->fre = fre;
    inv_index[inv_val]->next = temp;

    return ;
}

void print_list(struct inv_node *temp){ //Print a row in a hash table recursively.  i.e a particular hash value
    if(temp == NULL){
        cout<<endl;
        return;
    }
    cout<<temp->word<<" "<<temp->fre<<" ";
    print_list(temp->next);
}



int main(){

    int i,j; //iterators
    int doc_count; //# of documents in the corpus
    char str[100000];
    int fre;
    doc_count = 8;

    for(i=0;i<MAXDOCS;i++)
        inv_index[i] = NULL;



    while( true ){
        if( !(cin>>str>>fre))
            break;
        add(0,str,fre);
    }
    print_list(inv_index[0]);


    return 0;
}
