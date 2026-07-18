//https://www.luogu.com.cn/problem/P3388
// 我们判断割点的方法是：
// 1.如果这个点是根节点  那么如果他有两个儿子  则他一定是割点
// 这里的两个儿子指的是在深度优先搜索的条件下的两个儿子  即这两个儿子的子树一定是互不相干的  
// 否则其中一个儿子的子树一定会包括另外一个儿子
// 2.如果这个节点不是根节点，并且不是叶子结点 并且low[他的任意一个孩子]>=dfn[他]  则它是割点
// 如果是叶节点  那么不可能是割点 
// 并且他的所有孩子不能到达它的上面  即他扼死了孩子向上的通道
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;

vector<int>vec[MAXN];
//在割点的时候  dfn还是最早的序号 可是low却不再是这个节点可以到达的最小编号了
//和缩点的时候不同
int dfn[MAXN],low[MAXN];
int Time;
bool cut[MAXN];
bool instack[MAXN];
int n,m;

// v:当前点 r：本次搜索树的root
void tarjan(int u,int r) {
	dfn[u] = low[u] = ++Time;
	int child = 0;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		if (!dfn[v]) {
			tarjan(v, r);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u] && u != r){
                cut[u] = true;//不是根而且他的孩子无法跨越他回到祖先
            }
			if (r == u){
                child++; //如果是搜索树的根，统计孩子数目
                //其实所有的节点都可以统计孩子的数量 但是非根节点统计后没有什么作用
            }
		}
        else {
            low[u] = min(low[u], dfn[v]);//这里要特别注意 不能变成low[v]
            // 举个例子 比如a-b-c-d-b  并且还存在b-e-a
            // 那么首先b是一个割点  可是如果改成low[v] 那么low[d]=dfn[a]  导致b无法成为一个割点
            //可以简单的认为这个v是已访问过的   比如说父亲节点  父亲的其他儿子可以走向祖先  但是这个儿子不通过父亲无法走到
        }
	}
	if (child >= 2 && u == r){
        cut[r] = true;//对应第一种情况
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,i);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(cut[i]){
            ans++;
        }
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++){
        if(cut[i]){
            cout<<i<<' ';
        }
    }
    return 0;
}