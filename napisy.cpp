#include <iostream>
#include <string>

using namespace std;
bool czyrozne(char* s)  // Return true only if every two next chars are different
{

    int i=0;
    while(s[i+1])  // whiles[i+1] is not null
    {
        if(s[i]==s[i+1]) return false;
        i++;
    }
    return true;
}

void drukuj_gwiazdki(char* s)  // change space for * in our text
{
    int i=0;
    while(s[i])
    {
        if(s[i]==' ') s[i]='*';
        i++;
    }
}



int main(){
char a[] = " ELo jestem rozny chyba jak cos";
char b[] = " a ja       nie ";

cout<<"napis1 -> "<<czyrozne(a)<< " napis2 -> "<< czyrozne(b)<<"\n";
drukuj_gwiazdki(a);
drukuj_gwiazdki(b);

int i=0;
while(a[i]){
    cout<<a[i];
    i++;
}
i=0;
cout<<"\n";
while(b[i]){
    cout<<b[i];
    i++;
}

return 0;
}
