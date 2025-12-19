#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+5;

int n;
int cnt=1;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int fa[MAXN];
int sz[MAXN<<1];
int sz1[MAXN];

void dfs(int u,int f){
    fa[u]=f;
    sz[u]=1;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
            sz[u]+=sz[v];
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;

        sz1[u]++;
        sz1[v]++;
    }
    dfs(1,0);
//    for(int i=1;i<=n;i++){
//        printf("%3d",sz1[i]);
//    }
//    cout<<endl;
//    for(int i=1;i<=n;i++){
//        printf("%3d",sz[i]);
//    }
//    cout<<endl;
    if(n==1){
        cout<<1;
        return 0;
    }
    for(int i=1;i<=n;i++){
        if(sz1[i]==0){
            continue;
        }
        if((n-1)%sz1[i]!=0){
            continue;
        }
        //cout<<i<<' ';
        if(i==1){
            int f=0;
            for(int j=head[i];j>0;j=Next[j]){
                int v=to[j];
                if(sz[v]!=(n-1)/sz1[i])
                    f=1;
                    break;
            }
            if(f==0)
                cout<<i<<' ';
        }
        else{
            int f=0;
            if((n-sz[i])!=(n-1)/sz1[i]){
                //cout<<666<<' ';
                f=1;
                continue;
            }
            for(int j=head[i];j>0;j=Next[j]){
                //cout<<777<<' ';
                int v=to[j];
                //cout<<999<<' ';
                if(v!=fa[i]){
                    if(sz[v]!=(n-1)/sz1[i]){
                        f=1;
                        break;
                    }
                }
                //cout<<888<<' ';
            }
            if(f==0)
                cout<<i<<' ';
        }
    }
    return 0;
}
