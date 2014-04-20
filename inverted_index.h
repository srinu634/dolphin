#include<algorithm>
#include<cstring>
#include<cmath>
#define MAXDOCS 2000
using namespace std;

struct inv_node{
    char *word;
    int fre;
    double score;
    struct inv_node *next;
};


struct inv_node * inv_index[MAXDOCS];
double len[MAXDOCS]; // For Length Normalisation

void initialise_inv_index(){
	int i;

	for(i=0;i<MAXDOCS;i++)
		inv_index[i] = NULL , len[i] = 0;
}


void add_inv(int inv_val,char str[],int fre){

    struct inv_node *temp;

    temp = inv_index[inv_val];


    inv_index[inv_val] = (struct inv_node  *) (struct inv_node *)malloc(sizeof(struct inv_node *) );

    inv_index[inv_val]->word = (char *)malloc(sizeof(char)*(5 + strlen(str)) );
    strcpy( inv_index[inv_val]->word ,str );
    inv_index[inv_val]->fre = fre;
    inv_index[inv_val]->next = temp;

    return ;
}

void print_inv_list(struct inv_node *temp){ //Print a row in a hash table recursively.  i.e a particular hash value
    if(temp == NULL){
        cout<<endl;
        return;
    }
    cout<<temp->word<<","<<temp->fre<<","<<temp->score<<" ";
    print_inv_list(temp->next);
}
