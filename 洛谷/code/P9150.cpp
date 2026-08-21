#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1500005;
const int MAXM = 3000005;
const int MAXV = 3000005;

int n,m;
int k[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cntg;

bool vis[MAXN];
int pos[MAXN];
int seq[MAXN];

int fa1[MAXV];
int fa2[MAXV];
int pre[MAXV];
int loc[MAXV];

int ans1[MAXN];
int ans2[MAXN];

int find1(int x)
{
    if(fa1[x]==x) return x;
    return fa1[x]=find1(fa1[x]);
}

int find2(int x)
{
    if(fa2[x]==x) return x;
    return fa2[x]=find2(fa2[x]);
}

inline void addedge(int u,int v)
{
    // 建立反图
    nxt[++cntg]=head[v];
    to[cntg]=u;
    head[v]=cntg;
}

void calc(int st)
{
    int cnt=0;
    int u=st;

    // 取出当前钥匙置换环
    while(!vis[u]){
        vis[u]=true;
        seq[++cnt]=u;
        pos[u]=cnt;
        u=k[u];
    }

    // 将环复制一遍，从右向左处理
    for(int i=cnt*2;i>=1;i--){
        u=seq[(i-1)%cnt+1];

        fa1[i]=i;
        fa2[i]=i;
        pre[i]=0;
        loc[i]=0;

        for(int e=head[u];e;e=nxt[e]){
            int v=to[e];
            if(!pos[v]) continue;

            int p=pos[v];

            // v -> u，取u左侧最近的v
            if(p>i) p-=cnt;
            if(p+cnt<i) p+=cnt;
            pre[i]=max(pre[i],p);

            // v -> u，取u右侧最近的v
            if(p<i) p+=cnt;
            if(p<=cnt*2){
                int r=find2(p);
                loc[r]=max(loc[r],find1(p));
            }
        }

        while(true){
            // 利用返回边扩大强连通区间
            while(true){
                int r1=find1(i);
                int r2=find2(i);

                if(r1>=loc[r2]) break;
                fa1[r1]=r1+1;
            }

            int r1=find1(i);
            int r2=find2(i);
            loc[r2]=0;

            // 当前强连通区间能进入下一个可达区间
            if(r2==cnt*2) break;
            if(r1!=r2) break;
            if(pre[r2+1]<i) break;

            fa2[r2]=r2+1;
        }

        ans1[u]=min(cnt,find2(i)-i+1);
        ans2[u]=min(cnt,find1(i)-i+1);
    }

    for(int i=1;i<=cnt;i++){
        pos[seq[i]]=0;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;

    while(T--){
        cin>>n>>m;

        for(int i=1;i<=n;i++){
            cin>>k[i];
            head[i]=0;
            vis[i]=false;
        }

        cntg=0;

        for(int i=1;i<=m;i++){
            int x,y;
            cin>>x>>y;
            addedge(x,y);
        }

        for(int i=1;i<=n;i++){
            if(!vis[i]){
                calc(i);
            }
        }

        for(int i=1;i<=n;i++){
            cout<<ans1[i]<<' '<<ans2[i]<<'\n';
        }
    }

    return 0;
}