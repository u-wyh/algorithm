#include<bits/stdc++.h>
using namespace std;
map<string,string>p;

string s,s1;

string find(string x)
{
    if(x!=p[x])
        p[x]=find(p[x]);
    return  p[x];
}

int main()
{
    char ch;
    cin>>ch;
    while(ch!='$'){
        cin>>s;
        if(ch=='#'){
            s1=s;
            if(p[s]=="")
                p[s]=s;
        }else if(ch=='+')
            p[s]=s1;
        else
            cout<<s<<' '<<find(s)<<endl;
        cin>>ch;
    }
    return 0;
}
