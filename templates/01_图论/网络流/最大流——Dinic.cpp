// https://www.luogu.com.cn/problem/P3376
// dinic算法
// 如果某一时刻我们已经知道边 (u, v) 已经增广到极限（边 (u, v) 已无剩余容量或 v 的后侧已增广至阻塞），
// 则 u 的流量没有必要再尝试流向出边 (u, v)。据此，对于每个结点 u，我们维护 u 的出边表中第一条还有必要尝试的出边。
// 习惯上，我们称维护的这个指针为当前弧，称这个做法为当前弧优化。
// 多路增广是 Dinic 算法的一个常数优化——如果我们在层次图上找到了一条从 s 到 t 的增广路 p，
// 则接下来我们未必需要重新从 s 出发找下一条增广路，而可能从 p 上最后一个仍有剩余容量的位置出发寻找一条岔路进行增广。
// 考虑到其与回溯形式的一致性，这一优化在 DFS 的代码实现中也是自然的。
// 时间复杂度为O(v*v*E)  特别的在二分图匹配中是O(e*根号v)
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 205;
const int MAXM = 10005;
const int INF = 1e10;

int n,m,s,t;

int dep[MAXN];//记录深度数组
int iter[MAXN];//当前弧数组 记录这个节点有效访问的第一条边的编号

//这里编号从2开始 为了正反边编号寻找方便
int cnt=2;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int now[MAXM];//表示现在的流量
int cap[MAXM];//表示流量限制

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    cap[cnt]=w;
    now[cnt]=0;
    head[u]=cnt++;

    nxt[cnt]=head[v];
    to[cnt]=u;
    cap[cnt]=0;
    now[cnt]=0;
    head[v]=cnt++;
}

//BFS构建分层图，并判断是否存在增广路径
bool bfs(){
    for(int i=1;i<=n;i++){
        dep[i]=-1;
    }
    queue<int>q;
    dep[s]=0;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=cap[i];
            int k=now[i];
            if(dep[v]<0&&(k<w)){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[t]>=0;// 如果汇点未被访问到，说明无增广路径
}

// DFS寻找增广路径（多路增广）
// 多路增广的含义是来到了一个节点 不仅仅是只去一条边增广  而是去多条边一起增广
int dfs(int u,int f){
    //表示当前来到了u节点 有f的流量可供使用  f就是目前这条路最多可以消耗掉的流量
    if(u==t){
        return f;
    }
    int flow=0;
    for(int &i=iter[u];i;i=nxt[i]){
        //注意这里是引用  iter会随着i发生变化
        int v=to[i];
        int w=cap[i];
        int k=now[i];
        if(dep[u]+1==dep[v]&&k<w){
            int d=dfs(v,min(f,w-k));
            if(d>0){
                now[i]+=d;
                now[i^1]-=d;//更新反向边
                flow+=d;
                f-=d;
                if(f==0){
                    break;
                }
            }
        }
    }
    return flow;
}

// Dinic算法主函数
int maxflow(){
    int flow=0;
    while(bfs()){
        //当前弧全部初始化为最初值
        for(int i=1;i<=n;i++){
            iter[i]=head[i];
        }
        int maxflow;
        while((maxflow=dfs(s,INF))>0){
            flow+=maxflow;
        }
    }
    return flow;
}

signed main()
{
    cin>>n>>m>>s>>t;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
    }
    cout<<maxflow()<<endl;
    return 0;
}