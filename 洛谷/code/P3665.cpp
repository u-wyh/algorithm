#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m,k,q;

struct node{
    int u,v,w;
    bool operator<(node other)const {
        return w<other.w;
    }
};
node nums[MAXN];

// 并查集
int fa[MAXN];

// 这个块的开头和结尾
int head[MAXN];
int tail[MAXN];

// 这个节点的前驱与后继  以及和后继节点之间的权值
int pre[MAXN];
int suf[MAXN];
int val[MAXN];

// 节点颜色
int col[MAXN];

multiset<int>ans;

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

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int main()
{
    n=read(),m=read(),k=read(),q=read();

    for(int i=1;i<=m;i++){
        nums[i].u=read(),nums[i].v=read(),nums[i].w=read();
    }
    sort(nums+1,nums+m+1);

    // 初始化  一个节点作为一个块
    for(int i=1;i<=n;i++){
        fa[i]=i;
        head[i]=i,tail[i]=i;
        pre[i]=0,suf[i]=0;
        val[i]=0;
    }

    // 这个过程可以认为是构建最小生成树  但是认为是kruskal重构树更合适
    // 因为这里的逻辑实际上是按照重构树来的
    for(int i=1;i<=m;i++){
        int u=nums[i].u,v=nums[i].v,w=nums[i].w;
        int fx=find(u),fy=find(v);
        if(fx!=fy){
            int fxtail=tail[fx];
            int fyhead=head[fy];
            suf[fxtail]=fyhead;
            pre[fyhead]=fxtail;
            val[fxtail]=w;
            fa[fy]=fx;
            tail[fx]=tail[fy];
        }
    }

    for(int i=1;i<=n;i++){
        col[i]=read();
    }

    for(int i=1;i<=n;i++){
        if(suf[i]){
            if(col[i]!=col[suf[i]]){
                ans.insert(val[i]);
            }
        }
    }

    while(q--){
        int a,b;
        a=read(),b=read();
        int old=col[a];
        col[a]=b;

        if(pre[a]){
            int p=pre[a];
            if(col[p]!=old){
                auto it=ans.find(val[p]);
                ans.erase(it);
            }
            if(col[p]!=b){
                ans.insert(val[p]);
            }
        }
        if(suf[a]){
            int s=suf[a];
            if(col[s]!=old){
                auto it=ans.find(val[a]);
                ans.erase(it);
            }
            if(col[s]!=b){
                ans.insert(val[a]);
            }
        }

        cout<<*ans.begin()<<endl;
    }
    return 0;
}