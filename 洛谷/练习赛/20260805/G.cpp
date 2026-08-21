#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m,k;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int ans[MAXN];
int cnt;

bool win[MAXN];
int wincnt[MAXN];
bool special[MAXN];

int q[MAXN];

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void init(){
    for(int i=1;i<=n;i++){
        head[i]=0;
        win[i]=false;
        wincnt[i]=0;
        special[i]=false;
    }
    cntg=1;
    cnt=0;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>k;
        init();
        for(int i=1;i<=m;i++){
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }
        int l=1,r=0;
        for(int i=1;i<=k;i++){
            int u;
            cin>>u;
            q[++r]=u;
            win[u]=true;
            special[u]=true;
        }

        while(l<=r){
            int u=q[l++];
            for(int i=head[u];i;i=nxt[i]){
                int v=to[i];
                if(special[v]){
                    continue;
                }

                wincnt[v]++;
                if(wincnt[v]>=2&&!win[v]){
                    q[++r]=v;
                    win[v]=true;
                    ans[++cnt]=v;
                }
            }
        }

        for(int u=1;u<=n;u++){
            if(win[u]){
                continue;
            }
            for(int i=head[u];i;i=nxt[i]){
                int v=to[i];
                if(win[v]){
                    ans[++cnt]=u;
                    break;
                }
            }
        }

        cout<<cnt<<endl;
        for(int i=1;i<=cnt;i++){
            cout<<ans[i]<<' ';
        }
        cout<<endl;
    }
    return 0;
}