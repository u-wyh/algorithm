// https://www.luogu.com.cn/problem/P3665
// 这道题确实非常好  考验对kruskal重构树的理解
// 首先我们可以知道 答案一定是最小生成树上的一条边权
// 证明：如果是一条路径（多条树上的边组成）的话  那么路径的开头和结尾一定是种类不同的
// 那么考虑中间的节点和开头结尾的种类是否相同  很明显可以得到这条路径一定不是答案
// 同理  不是树上的边也可以用类似的方法证明
// kruskal重构树建图  实际上建立的不是树 而是一条链  但是我们首先当做一棵树来处理
// 我们来判断一下那些边可以成为答案  他必须满足下面的条件
// 1、它的左右孩子内部颜色相同  否则它的孩子中产生的答案一定更优
// 2、它左右孩子颜色不同 否则他也不会是答案
// 我们需要再满足这些条件的边中找到一条权值小的边
// 其实根据上面的条件 我们也可以知道  如果左右子树可以产生答案 那么一定比当前更优
// 也就是说 对于当前（重构树）节点而言  如果答案在这个子树中产生  要么是他的左右孩子节点中产生
// 要么是他的左右孩子分别作为一个整体  相互影响产生  绝不可能是左右子树内部的某个节点互相影响产生
// 那么就这个性质  我们可以将整个图变成一个链
// 将这条链上只要相邻的颜色不同  那么就可能是答案   将可能值收集起来
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
    // 左子树的这个块的尾巴  后面  接上右子树的这个块的头
    // 这里这样做的逻辑是  如果左子树中的块内部颜色不同  那么答案肯定轮不到左右子树的连接边上
    // 如果左子树内部颜色相同  那么左子树和右子树链接的边可能成为答案  并且事实上也有资格成为答案
    // 这个是关键
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

    // 收集所有可能成为答案的值
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

        // 颜色发生变化  更改答案预备值
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