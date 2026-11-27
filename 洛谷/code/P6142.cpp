// https://www.luogu.com.cn/problem/P6142
// 题意：给定一棵 N 个节点的树，将整棵树的所有边划分为若干条简单链，使得每条链长度均至少为 K，求正整数 K 的最大值。
// 数据范围：1 <= N <= 10^5。
// 算法标签：二分答案、贪心、深度优先搜索
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
bool flag;
int f[MAXN];

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

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int fa,int len){
    if(!flag){
        return ;
    }
    multiset<int>s;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u,len);
        s.insert(f[v]+1);
    }
    int sz=s.size();
    bool tag=false;
    if((u==1&&(sz&1))||(u!=1&&!(sz&1))){
        s.insert(0);
    }
    while(!s.empty()){
        if(!flag){
            break;
        }
        int val;
        multiset<int>::iterator l=s.begin(),r;
        val=*l;
        s.erase(l);
        r=s.lower_bound(len-val);
        if(u==1){
            if(r==s.end()){
                flag=false;
                break;
            }
            s.erase(r);
        }
        else{
            if(r==s.end()&&tag){
                flag=false;
                break;
            }
            if(r==s.end()){
                f[u]=val;
                tag=true;
            }
            if(r!=s.end()){
                s.erase(r);
            }
        }
    }
}

bool check(int len){
    flag=true;
    for(int i=1;i<=n;i++){
        f[i]=0;
    }
    dfs(1,0,len);
    return flag;
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    int l=1,r=n-1,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    cout<<ans<<endl;
    return 0;
}