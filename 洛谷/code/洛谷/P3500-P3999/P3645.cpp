// https://www.luogu.com.cn/problem/P3645
// 题意：输入摩天楼数量 N（编号 0..N-1）与 doge 数量 M，
// 以及每只 doge 的初始位置 B_i 和跳跃能力 P_i。
// 位于 b 的 doge 每次可跳到 b - P_i
// 或 b + P_i（须在 [0, N-1] 内），
// 且在同一座楼时可将消息传给该楼上的其他 doge。
// 输出将消息从 0 号 doge 传递到 1 号 doge 所需的最少总跳跃步数，
// 若无法到达输出 -1。
// 数据范围：1 <= N <= 30000，1 <= P_i <= 30000，
// 2 <= M <= 30000，0 <= B_i < N。
// 算法标签：广度优先搜索、bitset
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e4+5;

int n,m;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

struct node{
    int idx,jump,t;
};
queue<node>q;
bitset<MAXN>vis[MAXN];

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
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void trigger(int id,int t){
    for(int i=head[id];i;i=nxt[i]){
        int v=to[i];
        if(!vis[id].test(v)){
            vis[id].set(v);
            q.push({id,v,t});
        }
    }
    head[id]=0;
}

void extend(int id,int jump,int t){
    trigger(id,t);
    if(!vis[id].test(jump)){
        vis[id].set(jump);
        q.push({id,jump,t});
    }
}

int bfs(int st,int en){
    if(st==en){
        return 0;
    }
    trigger(st,0);
    while(!q.empty()){
        node tmp=q.front();
        q.pop();
        int id=tmp.idx;
        int jump=tmp.jump;
        int t=tmp.t;
        if(id-jump==en||id+jump==en){
            return t+1;
        }
        if(id-jump>=0){
            extend(id-jump,jump,t+1);
        }
        if(id+jump<n){
            extend(id+jump,jump,t+1);
        }
    }
    return -1;
}

int main()
{
    n=read(),m=read();
    int st,stjump,en,enjump;
    st=read(),stjump=read(),en=read(),enjump=read();
    addedge(st,stjump);
    addedge(en,enjump);
    for(int i=2;i<m;i++){
        int id,jump;
        id=read(),jump=read();
        addedge(id,jump);
    }
    cout<<bfs(st,en)<<endl;
    return 0;
}