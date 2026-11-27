#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1505;
const int MAXH = 20;
const int INF = 1e9+5;

int n,p;
int fa[MAXN];
int val[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

int dep[MAXN];
int st[MAXN][MAXH];

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=19;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,u);
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=19;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }

    for(int i=19;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

int main()
{
    int op;
    cin>>op;
    cin>>n;
    for(int i=2;i<=n;i++){
        cin>>fa[i];
        addedge(fa[i],i);
    }
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }

    if(op==1){
        cout<<n<<endl;
        for(int i=2;i<=n;i++){
            cout<<fa[i]<<' ';
        }
        cout<<endl;
        for(int i=1;i<=n;i++){
            cout<<val[i]<<' ';
        }
        cout<<endl;
        cout.flush();
    }
    else{
        dfs(1,0);
        int q;
        cin>>q;
        for(int i=1;i<=q;i++){
            int a,b;
            cin>>a>>b;
            int lcafa=lca(a,b);

            int ans=val[lcafa];
            int cnt=1;
            while(a!=lcafa){
                // ans=min(ans,val[a]);
                if(ans==val[a]){
                    cnt++;
                }
                else if(val[a]<ans){
                    ans=val[a];
                    cnt=1;
                }
                a=fa[a];
            }
            while(b!=lcafa){
                if(ans==val[b]){
                    cnt++;
                }
                else if(val[b]<ans){
                    ans=val[b];
                    cnt=1;
                }
                b=fa[b];
            }
            cout<<ans<<' '<<cnt<<endl;
            cout.flush();
        }
    }
    return 0;
}