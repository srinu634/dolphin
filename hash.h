#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

typedef long long ll;
#define MAX 373
#define true 1
#define false 0
#define rep(i,n) for(i=0;i<n;i++)


struct node{
    char* word;
    ll docfre;
    struct node *next;
};

struct node *h [MAX];  //hash table

void initialise_hash(){
    ll i,j;

    rep(i,MAX)
        h[i] = NULL;

}

ll generate_hash(char * str){
    int i,hashvalue,len;

    hashvalue = 0;
    len = strlen(str);

    for(i=0;i<len;i++)

        hashvalue =  ( hashvalue + ( 43 * (str[i] - 'a')  )%MAX )%MAX;
    return hashvalue;

}

int lookup(char * str){

    int hashvalue;
    struct node *trav;

    hashvalue = generate_hash(str);


    trav = h[hashvalue];

    while(trav != NULL){

        if( strcmp(str,trav->word) == 0){
            trav->docfre++;
            return true;
        }

        trav = trav->next;

    }

    return false;
} //lookup

void add(char * str){
    int hashvalue;
    struct node *temp;

    hashvalue = generate_hash(str);

    //cout<<"Hash value: "<<hashvalue<<endl;
    temp = h[hashvalue];


    h[hashvalue] = (struct node  *) (struct node *)malloc(sizeof(struct node *) );

    h[hashvalue]->word = (char *)malloc(sizeof(char)*(5 + strlen(str)) );
    strcpy( h[hashvalue]->word ,str );
    h[hashvalue]->docfre = 1;
    h[hashvalue]->next = temp;

    return;
}

void print_list(struct node *temp){ //Print a row in a hash table recursively.  i.e a particular hash value
    if(temp == NULL){
        cout<<endl;
        return;
    }
    cout<<temp->word<<" "<<temp->docfre<<" ";
    print_list(temp->next);
}

void print_hash(){
    ll i;

    rep(i,MAX){
        if(h[i] == NULL)
            continue;
        else
            print_list(h[i]);
    }
}
