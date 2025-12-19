// https://www.luogu.com.cn/problem/P4716
//朱刘算法是一个用于解决有向图的最小生成树算法  时间复杂度是O(VE)
//主要步骤如下：
//1、  找到每个节点的入线的最小权值  记录这个权值以及来源点  也就是这条线
//     如果存在非根节点没有源点  说明无法构成以当前根节点为根的树
//2、  将上面所有的线看做有向边  答案加上所有的权值   如果不存在环  说明这就是一棵树  直接结束
//     否则将一个环缩点
//3、  缩完点之后  将原图上的边更新一下  权值全部更新为减去这个v的入度最小权值(因为这个环中多了一条边)
//     然后将u v改成缩完点之后的编号   n变为cnt  root=id[root]
// 类似的题目还有P2792
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 1e4+5;

int n,m,root;

struct node{
    int u,v,w;
}nums[MAXM];

int pre[MAXN];
int in[MAXN];
int id[MAXN];
int vis[MAXN];//这里之所以不是bool类型  主要是为了判断环   如果是bool类型 可能会导致不是环上的点也被计算

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
    for(int i=1;i<=n;i++){
        pre[i]=0;
        in[i]=INT_MAX;
        id[i]=0;
        vis[i]=false;
    }
}

int main()
{
    n=read(),m=read(),root=read();
    for(int i=1;i<=m;i++){
        nums[i].u=read(),nums[i].v=read(),nums[i].w=read();
    }
    long long ans=0;
    while(true){
        prepare();
        for(int i=1;i<=m;i++){
            int u=nums[i].u;
            int v=nums[i].v;
            int w=nums[i].w;
            if(u!=v&&w<in[v]){
                in[v]=w;
                pre[v]=u;
            }
        }

        for(int i=1;i<=n;i++){
            if(in[i]==INT_MAX){
                cout<<-1<<endl;
                return 0;
            }
        }

        for(int i=1;i<=n;i++){
            if(root==i){
                continue;
            }
            ans+=in[i];
        }

        int cnt=0;
        int idx=0;

        //注意 一个点只能有一条入边  所以如果被访问过了  
        //那么如果是环上的点  直接结束    不是环上的点  再次访问也没有什么用
        for(int i=1;i<=n;i++){
            if(vis[i]||i==root){
                //如果已经在环中  或者  是根节点（只能有出边）  那么直接结束
                continue;
            }
            idx++;
            // 这里实际上是想找到一个包含v的最小环（可能不是包含吧  可能是这个环上有一个点出发沿着最短路径可以走到v）
            // 从节点i开始，沿着最小入边的反向路径遍历，检测是否遇到环
            // 遇到了id[v]不等于0的  说明v一定是别的环中的了  一定不可能和自己组成最小环了
            // root不能有入边
            // 只有遇到了vis[v]==idx的  说明来到了环访问过的地方
            int v=i;
            while(vis[v]!=idx&&!id[v]&&v!=root){
                vis[v]=idx;
                v=pre[v];
            }
            //处理环上的节点
            if(v!=root&&!id[v]){
                cnt++;
                id[v]=cnt;
                for(int u=pre[v];u!=v;u=pre[u]){
                    id[u]=cnt;
                }
            }
        }
        
        if(cnt==0){
            break;
        }

        for(int i=1;i<=n;i++){
            if(!id[i]){
                id[i]=++cnt;
            }
        }

        //更新权值
        for(int i=1;i<=m;i++){
            if(nums[i].u!=nums[i].v){
                nums[i].w-=in[nums[i].v];
            }
            nums[i].u=id[nums[i].u];
            nums[i].v=id[nums[i].v];
        }

        //更新变量
        n=cnt;
        root=id[root];
    }

    cout<<ans<<endl;
    return 0;
}