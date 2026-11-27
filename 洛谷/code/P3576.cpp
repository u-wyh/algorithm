// https://www.luogu.com.cn/problem/P3576
// 题意：输入树上洞穴数 n、蚁群批数 g、食蚁兽胃口大小 k，各批蚁群大小 m_1..m_g，以及 n-1 条边（第一条边上有食蚁兽）。
// 每批蚁群从所有度数为 1 的出入口同时依次进入（山内无蚂蚁才进下一批）
// 经过有 d 条其余出边的洞穴时分裂为 d 群大小为 floor(x/d) 的蚁群（多余消失）；
// 经过第一条边且大小恰好为 k 的蚁群会被全部吃掉。
// 输出食蚁兽一共吃掉多少只蚂蚁。
// 数据范围：2 <= n, g <= 10^6，1 <= k, m_i <= 10^9，1 <= a_i, b_i <= n。
#include<bits/stdc++.h>
// 算法标签：深度优先搜索、二分查找、排序
using namespace std;
const int MAXN = 1e6+5;
const long long INF = 1e9+1;

int n,m,k;
int val[MAXN];
int root1,root2;

int minn[MAXN];
int maxx[MAXN];
int in[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

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

inline void addedge(int u,int v){
    in[u]++;
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        minn[v]=min(INF,1ll*minn[u]*(in[u]-1));
        maxx[v]=min(INF,1ll*(maxx[u]+1)*(in[u]-1)-1);
        dfs(v,u);
    }
}

int find1(int v){
    int l=1,r=m,ans=m+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(val[mid]>v){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int find2(int v){
    int l=1,r=m,ans=m+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(val[mid]>=v){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=m;i++){
        val[i]=read();
    }
    sort(val+1,val+m+1);
    root1=read(),root2=read();
    addedge(0,root1);
    addedge(0,root2);
    addedge(root1,0);
    addedge(root2,0);
    for(int i=2;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }

    minn[0]=k,maxx[0]=k;
    dfs(0,0);

    long long ans=0;
    for(int i=1;i<=n;i++){
        if(in[i]==1){
            ans+=find1(maxx[i])-find2(minn[i]);
        }
    }
    cout<<(ans*k)<<endl;
    return 0;
}