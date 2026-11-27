#include<bits/stdc++.h>
using namespace std;

int m,n;
int row[5];
int col[5];
int ans;

void dfs(int x,int y){
    if(y==n){
        dfs(x+1,0);
        return ;
    }

    if(x==n-1&&y==n-1){
        if(row[x]==col[x]){
            ans++;
        }
        return ;
    }

    if(x==n-1){
        int v=col[y];
        if(v<=row[x]){
            row[x]-=v;
            col[y]-=v;
            dfs(x,y+1);
            row[x]+=v;
            col[y]+=v;
        }
        return ;
    }

    if(y==n-1){
        int v=row[x];
        if(v<=col[y]){
            row[x]-=v;
            col[y]-=v;
            dfs(x,y+1);
            row[x]+=v;
            col[y]+=v;
        }
        return ;
    }

    int maxval=min(row[x],col[y]);
    for(int v=0;v<=maxval;v++){
        row[x]-=v;
        col[y]-=v;
        dfs(x,y+1);
        row[x]+=v;
        col[y]+=v;
    }
    return ;
}

int main()
{
    cin>>m>>n;
    for(int i=0;i<n;i++){
        row[i]=m;
        col[i]=m;
    }
    dfs(0,0);
    cout<<ans<<endl;
    return 0;
}