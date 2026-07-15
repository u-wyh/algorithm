#include<bits/stdc++.h>
using namespace std;
#define Max 5005

int father[Max],n,m,k;

void build(int n){
    for(int i=0;i<=n;i++){
        father[i]=i;
    }
}

int find(int i){
    if (i != father[i]){
        father[i] = find(father[i]);
    }
    return father[i];
}

bool issameset(int x,int y){
    return find(x)==find(y);
}

void un(int x,int y){
    father[find(x)] = find(y);
}


int main()
{
    cin>>n>>m>>k;
    build(n);
    int a,b;
    for(int i=1;i<=m;i++){
        cin>>a>>b;
        un(a,b);
    }
    for(int i=1;i<=k;i++){
        cin>>a>>b;
        if(issameset(a,b))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}

