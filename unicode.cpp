#include<iostream>
#include<algorithm>
#include<cstring>
#include<cwchar>
using namespace std;



int main(){

  wchar_t str[10000];
  wchar_t * pwc ,*ptr;

  while(true){
    if( !(wcin>>str))
        break;

    pwc = wcstok (str,L" ,.-~[]():'{};?*&$!@#-–/\"\\|‘’+_=<>|",&ptr);
    while (pwc != NULL)
    {
        wcout<<pwc<<" ";
        pwc = wcstok (NULL,L" ,.-~[]():'{};?*&$!@#-–/\"\\|‘’+_=<>|",&ptr);
    }


    wcout<<str<<" ";

  }

    return 0;
}


/*
 wchar_t str1[1000],str2[1000];

    wcin>>str1>>str2;

    if ( wcscmp(str1,str2) < 0 )
        cout<<"str2 is greater lexicographically"<<endl;
    else
        cout<<"str1 is greater lexicographically"<<endl;

    cout<<"len of str1: "<<wcslen(str1)<<" len of str2: "<<wcslen(str2)<<endl;

    cout<<str1[0]*str2[0]<<endl;
*/

