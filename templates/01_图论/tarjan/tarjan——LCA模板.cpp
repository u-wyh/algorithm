// tarjan算法解法
// 测试链接 : https://www.luogu.com.cn/problem/P3379
// 提交以下的code，提交时请把类名改成"Main"
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code03_Tarjan2文件
//tarjan算法求lca是离线操作  他的思想也很简单 lca就是说明这两个点最早同时出现于lca的子树中
//不可能比这个点更早  当然他们也会同时出现于lca的祖先节点的子树中  但是那就太晚了
//根据这个性质  即寻找最早同时出现的子树的头结点 求lca
//这种方法适用于存在多次查询操作 可以离线处理的情况
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
const int LIMIT = 20;

int n,m,root;

//建图的链式前向星
int head[MAXN];
int Next[MAXN];
int to[MAXN];
int tcnt=1;

//问题的链式前向星   包含一个问题的编号数组  用来填答案
int headQuery[MAXN];
int queryNext[MAXN << 1];
int queryTo[MAXN << 1];
// 问题的编号，一旦有答案可以知道填写在哪
int queryIndex[MAXN << 1];
int qcnt=1;

// 某个节点是否访问过
bool visited[MAXN];
// 并查集
int father[MAXN];
// 收集的答案
int ans[MAXN];

void build(){
    for(int i=1;i<=n;i++){
        father[i]=i;
    }
}

int Find(int i) {
    if (i != father[i]) {
        father[i] = Find(father[i]);
    }
    return father[i];
}

void tarjan(int u, int f) {
    visited[u] = true;
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            tarjan(v, u);//向下递归  直到叶节点
            father[v] = u;
        }
    }
    for (int e = headQuery[u], v; e != 0; e = queryNext[e]) {
        v = queryTo[e];
        if (visited[v]) {
            //如果说这个问题节点已经被访问过  才可以进行答案填写
            //填写的答案是这个节点所在并查集的头结点
            ans[queryIndex[e]] = Find(v);
        }
    }
}

int main()
{
    cin>>n>>m>>root;
    build();
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;

        Next[tcnt]=head[u];
        to[tcnt]=v;
        head[u]=tcnt++;

        Next[tcnt]=head[v];
        to[tcnt]=u;
        head[v]=tcnt++;

    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;

        queryNext[qcnt] = headQuery[u];
		queryTo[qcnt] = v;
		queryIndex[qcnt] = i;
		headQuery[u] = qcnt++;

        queryNext[qcnt] = headQuery[v];
		queryTo[qcnt] = u;
		queryIndex[qcnt] = i;
		headQuery[v] = qcnt++;
    }
    tarjan(root,0);
    for(int i=1;i<=m;i++){
        if(ans[i]==0)
            ans[i]=root;
        cout<<ans[i]<<endl;
    }
    return 0;
}