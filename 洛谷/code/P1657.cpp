#include<bits/stdc++.h>

using namespace std;

#define MAX 25

int vis[MAX];
int x,a[MAX],b[MAX],ans=0;

void dfs(int m){
    if(vis[a[m]]!=0&&vis[b[m]]!=0){
        return ;
    }
    if(m>x){
        ans++;
    }
    if(vis[a[m]]==0){
        vis[a[m]]=1;
        dfs(m+1);
        vis[a[m]]=0;
        if(vis[b[m]]==0){
            vis[b[m]]=1;
            dfs(m+1);
            vis[b[m]]=0;
        }
    }else{
        vis[b[m]]=1;
        dfs(m+1);
        vis[b[m]]=0;
        if(vis[a[m]]==0){
            vis[a[m]]=1;
            dfs(m+1);
            vis[a[m]]=0;
        }
    }
}

int main()
{
    scanf("%d",&x);
    for(int i=1;i<=x;i++){
        scanf("%d %d",&a[i],&b[i]);
    }
    memset(vis,0,sizeof(vis));
    dfs(1);
    printf("%d\n",ans);
    return 0;
}
