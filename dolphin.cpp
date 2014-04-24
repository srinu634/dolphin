/*
                Inverted Index is built
                Global Hash Table is populated
                SearchEngine where queries are processed
*/

#include "hash.h"
#include "inverted_index.h"
#include<cmath>
#include<unistd.h>
#include<cstring>
#include<cstdio>
#include <ctime>

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
    char str[1000000];
    int i,j,fre;
    FILE *fp;

    for(i=0;i<n;i++){
        cout<<"Indexed Document "<<i<<endl;
        sprintf(fname,"./temp/%d.txt",i);
        fp = fopen(fname,"r");

        while( fscanf(fp,"%s %d",str,&fre) != EOF ){
                    //cout<<str<<" "<<fre<<endl;
            if(lookup(str) == false)
                add(str); //Global Hash Table

            add_inv(i,str,fre); //Inverted Index

        //   cout<<str<<" "<<fre<<endl;
        }//while
    //    print_inv_list(inv_index[i]);
        fclose(fp);
        len[i] =0;
    }//for
return;
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
        cout<<"In Document: "<<i<<endl;
        while(trav != NULL){
            double res1,res2;
            fre = get_fre(trav->word); //From the global hash table
           // cout<<trav->word<<"Total fre: "<<fre<<" ";

            res1 = n/1.000;
            res1 = res1/fre;
            res1 = log(res1)/log(2);
            //cout<<"Doc fre: "<<trav->fre;
            res2 = log(1+trav->fre)/log(2);
            res = res1 * res2;
            //cout<<" res1: "<<res1<<" res2: "<<res2<<" res: "<<res<<endl;
            trav->score = res;
            trav = trav->next;
            len[i] += res*res;

        }//while
        len[i] = sqrt(len[i]);
    }//for

}//scores

double getDotProductValue(int n,int m){ // n -> Doc # , m -> #Words in Query
                                        //Something very similar to merge
    int i,j;
    double res;
    struct inv_node *trav;


    trav = inv_index[n];
    i = 0;
    res = 0;

    //cout<<"In file "<<n<<endl;

    while( trav != NULL && i <= m) {
        if( strcmp(trav->word,Q[i].qword) < 0 ){
            //cout<<trav->word<<" "<<Q[i].qword<<endl;
             trav = trav->next;
            }
        else if( strcmp(trav->word,Q[i].qword) > 0 ) {
            //cout<<trav->word<<" "<<Q[i].qword<<endl;
            i++;
            }
        else {
            //cout<<"MATCHING FOUND"<<endl;
            res  = res + trav->score*Q[i].score;
            i++;
            trav = trav->next;
            }
    }

    return res;
}

bool cmpfun(struct doc_node a,struct doc_node b){

    return a.dot_prod > b.dot_prod ;
}

int main(int argc, char *argv[]){

    int i,i1,i2,j; //iterators
    int doc_count;


    initialise_hash();
    initialise_inv_index();


    doc_count = 8;
    //int start_s=clock();
    build_index(doc_count);  //Global Hash Table + Inverted Index are built
    //int stop_s=clock();
    //cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;

    cout<<"Calculating scores"<<endl;
    calculate_scores(doc_count); //Update score for each term in every document


    print_tables(doc_count);

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
            cout<<Q[i].qword<<endl;

        cout<<"Done Tokenizing"<<endl;

        for(i1=0;i1<doc_count;i1++)
            D[i1].dot_prod=0 , D[i1].doc_no = i1;

        double qlen;  //Normalised Query Vector
        qlen = 0;

        for(i=0;i<fre_qw;i++){
            Q[i].score = doc_count/1.0;
            Q[i].score = Q[i].score / get_fre( Q[i].qword );

            Q[i].score = log( Q[i].score ) <= 0 ? 0 : log( Q[i].score );
            Q[i].score = Q[i].score/log(2);
            cout<<"Global Score is: "<<get_fre(Q[i].qword)<<endl;;
            qlen += Q[i].score*Q[i].score;
        }

        qlen = sqrt(qlen);

        if(qlen == 0 ){
            cout<<"Query does not exist in our database | The word is too frequent (i.e a stop word may be )"<<endl;
            continue;
        }
        cout<<"Score w.r.t each file"<<endl;


         for(i=0;i<doc_count;i++)
            D[i].dot_prod = getDotProductValue(i,fre_qw)/(len[i]*qlen); //Unit Vector

        //sort and then retrieve the top 5 docs :)
        //for(i=0;i<fre_qw;i++){
          //  cout<<Q[i].qword<<" "<<Q[i].score<<endl;
         //}

        sort(D,D+doc_count,cmpfun);

        for(i=0;i<doc_count;i++)
            cout<<D[i].doc_no<< ","<<D[i].dot_prod<<endl;;
        cout<<endl;


        cout<<"Enter File# To open the File (-1 to exit): "<<endl;

        while(true){
            int fno;


            cin>>fno;

            if(fno == -1)
                break;


            if(fno < 0|| fno >= doc_count){
                cout<<"Please Enter a valid file#: "<<"0 to "<<doc_count-1<<endl;
                continue;
            }

            int pid;
            char cmmnd[100];

            sprintf(cmmnd,"ls -1 ./docs | head -n %d | tail -n 1  > qtemp.out",fno+1);

            pid = fork();
            system(cmmnd);


            if(pid == 0){ //Displaying the file, inner details are a bit messy :(
                char tstr[1000];
                FILE *fp;
                fp = fopen("qtemp.out","r");

                fscanf(fp,"%s",tstr);
                  cout<<"File name is: "<<tstr<<endl;

                sprintf(cmmnd,"cp ./docs/%s doctemp.out",tstr);
                system(cmmnd);
                /*strcpy(tstr,"grep ");

                for(i=0;i<fre_qw;i++){
                    strcat(tstr," -e ");
                    strcat(tstr,Q[i].qword);
                }*/
                sprintf(tstr,"grep -n ");
                for(i=0;i<fre_qw;i++)

                    strcat(tstr," -e "), strcat(tstr,Q[i].qword);

                sprintf(cmmnd," cat doctemp.out | %s",tstr);
                system(cmmnd);
                fclose(fp);
                return 0;
            }//child
        }//while
    }//Infinite While Loop

    return 0;
    }//main


//  NOTE:
//          AS EACH WORD IN A QUERY IS GENERALLY REPEATED ONLY ONCE,TERM FREQUENCY OF QUERY IS NOT CONSIDERED.
