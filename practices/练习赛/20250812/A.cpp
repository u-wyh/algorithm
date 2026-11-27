#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MAXH = 32;

int n,h;
int ls[MAXN];
int rs[MAXN];
int dep[MAXN];
int sz[MAXN];
int f[MAXN][MAXH];//f[i][j]表示以i为首的子树 保持高度为j的avl最少操作
int len[]={0,1,2,4,7,12,20,33,54,88,143,232,376,609,986,1596,2583,4180,6764,10945,17710,28656,46367,75024,121392,196417,317810,514228,832039,1346268};
int dfn[MAXN];
int dfncnt;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void prepare(){
    for(int i=1;i<=30;i++){
        if(n>len[i]){
            h=i;
        }
    }
    h+=2;
    for(int i=0;i<=h;i++){
        f[0][i]=len[i];
    }
    for(int i=1;i<=n;i++){
        ls[i]=0,rs[i]=0;
    }
}

void bfs(){
    dfncnt=0;
    queue<int>q;
    dfn[++dfncnt]=1;
    q.push(1);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(ls[u]){
            q.push(ls[u]);
            dfn[++dfncnt]=ls[u];
        }
        if(rs[u]){
            q.push(rs[u]);
            dfn[++dfncnt]=rs[u];
        }
    }
    for(int i=dfncnt;i>=1;i--){
        int u=dfn[i];
        sz[u]=1;
        if(ls[u]){
            sz[u]+=sz[ls[u]];
        }
        if(rs[u]){
            sz[u]+=sz[rs[u]];
        }
    }
}

signed main()
{
    int T=read();
    while(T--){
        n=read();
        prepare();
        for(int i=1;i<=n;i++){
            ls[i]=read(),rs[i]=read();
        }
        bfs();
        for(int i=dfncnt;i>=1;i--){
            int u=dfn[i];
            f[u][0]=sz[u];
            f[u][1]=sz[u]-1;
            for(int j=2;j<=h;j++){
                f[u][j]=min(min(f[ls[u]][j-1] + f[rs[u]][j-2],f[ls[u]][j-2] + f[rs[u]][j-1]),f[ls[u]][j-1] + f[rs[u]][j-1]);
            }
        }
        int ans=n;
        for(int i=1;i<=h;i++){
            ans=min(ans,f[1][i]);
        }
        cout<<ans<<endl;
    }
    return 0;
}