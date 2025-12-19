#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;

map<string ,string >father;
int n,k;

string find(string s){
    if(s!=father[s])
        father[s]=find(father[s]);
    return father[s];
}

void un(string u,string v){
    father[find(u)]=find(v);
}

bool issameset(string u,string v){
    return find(u)==find(v);
}

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        father[s]=s;
    }
    for(int i=1;i<=k;i++){
        string a,b;
        cin>>a>>b;
        un(a,b);
    }
    int m;
    cin>>m;
    for(int i=1;i<=m;i++){
        string u,v;
        cin>>u>>v;
        if(issameset(u,v)){
            cout<<"Yes.\n";
        }
        else
            cout<<"No.\n";
    }
    return 0;
}
