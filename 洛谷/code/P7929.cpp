#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int INF = 1e6+5;

int n;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int dfncnt;
int dfn[MAXN];
int from[MAXN];
bool cycle[MAXN];
int cnta;
int arr[MAXN];
int cntb;
int lt[MAXN],rt[MAXN];

int dp[MAXN][2][2];
int cy[MAXN][2][2];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u){
    dfn[u]=++dfncnt;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(dfn[v]==0){
            from[v]=u;
            dfs(v);
        }
        else if(dfn[u]<dfn[v]){
            ++cntb;
            lt[cntb]=cnta+1;
            cycle[u]=true;
            arr[++cnta]=u;
            for(int j=v;j!=u;j=from[j]){
                cycle[j]=true;
                arr[++cnta]=j;
            }
            rt[cntb]=cnta;
        }
    }
}

void dpOnTree(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dpOnTree(v,u);
        }
    }
    for(int c=0;c<=1;c++){
        int f0=c;
        int f1=INF;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=fa){
                int nf0=min(INF,f0+dp[v][0][c]);
                int nf1=min(INF,min(f0+dp[v][1][c],f1+dp[v][0][c]));

                f0=nf0;
                f1=nf1;
            }
        }
        dp[u][c][0]=f1;
        dp[u][c][1]=f0;
    }
}

void dpOnCycle(int u){
    for(int c=0;c<=1;c++){
        int f0=c;
        int f1=INF;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(!cycle[v]){
                int nf0=min(INF,f0+dp[v][0][c]);
                int nf1=min(INF,min(f0+dp[v][1][c],f1+dp[v][0][c]));

                f0=nf0;
                f1=nf1;
            }
        }

        cy[u][c][0]=f0;
        cy[u][c][1]=f1;
    }
}

int cost(int u,int l,int m,int r){
    int need=1-l-r;
    if(need<0){
        return INF;
    }
    return cy[u][m][need];
}

int compute(int l,int r){
    int len=r-l+1;

    if(len<3){
        return INF;
    }
    int ans=INF;

    for(int c0=0;c0<=1;c0++){
        for(int c1=0;c1<=1;c1++){
            int f[2][2];
            int nf[2][2];

            f[0][0]=INF;
            f[0][1]=INF;
            f[1][0]=INF;
            f[1][1]=INF;

            f[c0][c1]=0;

            for(int pos=3;pos<=len;pos++){
                nf[0][0]=INF;
                nf[0][1]=INF;
                nf[1][0]=INF;
                nf[1][1]=INF;

                int mid=arr[l+pos-2];
                for(int a=0;a<=1;a++){
                    for(int b=0;b<=1;b++){
                        if(f[a][b]>=INF){
                            continue;
                        }
                        for(int c=0;c<=1;c++){
                            if(a==1&&c==1){
                                continue;
                            }
                            nf[b][c]=min(nf[b][c],f[a][b]+cy[mid][b][1-a-c]);
                        }
                    }
                }

                f[0][0]=nf[0][0];
                f[0][1]=nf[0][1];
                f[1][0]=nf[1][0];
                f[1][1]=nf[1][1];
            }

            for(int a=0;a<=1;a++){
                for(int b=0;b<=1;b++){
                    if(f[a][b]>INF){
                        continue;
                    }

                    int u=arr[l];
                    int v=arr[r];

                    if(b==1&&c1==1){
                        continue;
                    }
                    if(a==1&&c0==1){
                        continue;
                    }
                    ans=min(ans,f[a][b]+cost(v,a,b,c0)+cost(u,b,c0,c1));
                }
            }
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    for(int i=1;i<=n;i++){
        if(dfn[i]==0){
            dfs(i);
        }
    }

    for(int i=1;i<=cntb;i++){
        for(int j=lt[i];j<=rt[i];j++){
            int u=arr[j];
            for(int e=head[u];e;e=nxt[e]){
                int v=to[e];
                if(!cycle[v]){
                    dpOnTree(v,u);
                }
            }
        }
        for(int j=lt[i];j<=rt[i];j++){
            dpOnCycle(arr[j]);
        }
    }

    int ans=0;
    for(int i=1;i<=cntb;i++){
        int cur=compute(lt[i],rt[i]);
        if(cur>=INF){
            cout<<-1<<endl;
            return 0;
        }
        ans+=cur;
    }
    cout<<ans<<endl;
    return 0;
}