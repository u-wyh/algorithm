#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int fa[MAXN*2];
int n,m;

void build(){
    for(int i=1;i<=2*n;i++){
        fa[i]=i;
    }
}

int find(int i){
    if(i!=fa[i]){
        fa[i]=find(fa[i]);
    }
    return fa[i];
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fy]=fx;
    }
}

int main()
{
    cin>>n>>m;
    build();
    for(int i=1;i<=m;i++){
        char c;
        int a,b;
        cin>>c>>a>>b;
        if(c=='A'){
            un(a,b+n);
            un(b,a+n);
        }
        if(c=='R'){
            un(a,b);
            un(b+n,a+n);
        }
        if(c=='Q'){
            if(find(a)==find(b)){
                cout<<'R'<<endl;
            }
            else if(find(a+n)==find(b)&&find(b+n)==find(a)){
                cout<<'A'<<endl;
            }
            else
                cout<<'?'<<endl;
        }
    }
    return 0;
}
