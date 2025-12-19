#include<bits/stdc++.h>
using namespace std;

int fa[30005],sz[30005],last[30005];
int father[30005];


int find(int i){
    if (i != father[i]){
        father[i] = find(father[i]);
    }
    return father[i];
}

void un(int x,int y){
    if(find(x)==find(y)){
        return ;
    }
    else{
        fa[y]=x;
        while(fa[x]!=x){
            //fa[y]=x;
            sz[x]+=sz[y];
            x=fa[x];
        }
        father[y]=x;
        sz[x]+=sz[y];
        last[x]=last[y];
    }
}

int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=30000;i++){
        fa[i]=i;
        sz[i]=1;
        last[i]=i;
        father[i]=i;
    }
    while(t--){
        char c;
        int a,b;
        cin>>c>>a>>b;
        if(c=='M'){
            un(last[find(b)],find(a));
        }
        else{
            if(find(a)!=find(b)){
                cout<<-1<<endl;
            }
            else{
                cout<<abs(sz[a]-sz[b])-1<<endl;
            }
        }
    }
    return 0;
}
