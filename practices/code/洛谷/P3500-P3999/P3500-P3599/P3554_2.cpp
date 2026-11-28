// https://www.luogu.com.cn/problem/P3554
// 题意：输入树上节点数 n 和 n-1 条树边。
// 初始 1 号点为黑、其余为白，B 初始在 1 号点；
// 每轮 A 先选至多 k 个点染黑，然后 B 移动到相邻节点，
// B 踩到白点则 B 胜，全黑则 A 胜。
// 输出能让 A 必胜的最小 k。
// 数据范围：1 <= n <= 3*10^5。
// 难度评分：1800（洛谷分级换算）
// 算法标签：二分答案、树形动态规划
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int son[MAXN];
int dep[MAXN];
int need[MAXN];

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

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int f){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==f){
            continue;
        }
        son[u]++;
        dfs(v,u);
    }
}

void dfs1(int u,int fa){
    if(!son[u]){
        return ;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs1(v,u);
            if(need[v]<0){
                need[u]+=need[v];
            }
        }
    }
    need[u]-=son[u];
}

bool check(int k){
    for(int i=1;i<=n;i++){
        if(son[i]){
            need[i]=k;
        }
    }
    dfs1(1,0);
    return need[1]>=0;
}

int main()
{
    n=read();
    if(n==1){
        cout<<0<<endl;
        return 0;
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    int l=1,r=n,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}