// https://www.luogu.com.cn/problem/P9132
// 这道题是利用根号分治实现  我们将度数大于blen的节点看是重点
// 小于等于的全部看成是轻点
// 然后使用可重复集合维护  具体而言 就是所有只要不涉及到重点的边使用6个堆来维护
// 对于所有的涉及到了重点的边  统一使用每个重点自己的集合维护  维护每个重点的所有连边节点的颜色
// 这道题只要求边权 所以我们记录边权即可
// 对于所有的修改操作 
// 如果这个点是轻点  那么更改他所有连接的边 如果连得是轻点  那么直接修改那6个集合即可
// 否则 修改重点的颜色集合组成
// 如果是重点 那么如果连接点是重点  那么更改他们的对应的颜色组成  轻点的话可以直接忽略不计
// 对于查询操作
// 答案要么是来自轻点内部之间的边  要么是涉及到了重点  轻点内部的边可以从集合中直接得到
// 涉及到重点的边  遍历所有重点统计答案也很快 毕竟只有blen个节点
#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9+7;
const int MAXN = 1e5+5;
const int MAXM = 5e5+5;
const int MAXB = 405;

int n,m;
int blen;
int col[MAXN];

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];
int cnt=1;

// 按照度排序 选出重点
struct point{
    int t,sub;
}arr[MAXN];
// 重点的标记
int vis[MAXN];
// 第i个重点的编号  方便收集答案
int id[MAXB];

multiset<int>st[7];
multiset<int>node[MAXB][4];

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

bool cmp(point a,point b){
    return a.t>b.t;
}

// 判断轻点组合的种类
int compute(int a,int b){
    if(a>b){
        swap(a,b);
    }
    if(a==1){
        return b;
    }
    else if(a==2){
        return a+b;
    }
    else{
        return 6;
    }
}

void prepare(){
    blen=sqrt(n);
    sort(arr+1,arr+n+1,cmp);
    for(int i=1;i<=blen;i++){
        vis[arr[i].sub]=i;
        id[i]=arr[i].sub;
    }
    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v<u){
                // 防止重复计数
                continue;
            }
            if(vis[v]||vis[u]){
                if(vis[v]){
                    node[vis[v]][1].insert(weight[i]);
                }
                if(vis[u]){
                    node[vis[u]][1].insert(weight[i]);
                }
            }
            else{
                st[1].insert(weight[i]);
            }
        }
    }
}

void query(int u,int v){
    int ans=INF;

    if(!st[compute(u,v)].empty()){
        ans=*st[compute(u,v)].begin();
    }
    for(int i=1;i<=blen;i++){
        if(col[id[i]]==u||col[id[i]]==v){
            if(!node[i][u+v-col[id[i]]].empty()){
                ans=min(ans,*node[i][u+v-col[id[i]]].begin());
            }
        }
    }

    if(ans==INF){
        cout<<"No Found!"<<endl;
    }
    else{
        cout<<ans<<endl;
    }
}

void update(int u,int c){
    // 其实这里的数据还是不够狠 没有添加自环
    if(!vis[u]){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(!vis[v]){
                int op=compute(col[u],col[v]);
                auto it=st[op].find(weight[i]);
                st[op].erase(it);
                op=compute(col[v],c);
                st[op].insert(weight[i]);
            }
            else{
                auto it=node[vis[v]][col[u]].find(weight[i]);
                node[vis[v]][col[u]].erase(it);
                node[vis[v]][c].insert(weight[i]);
            }
        }
    }
    else{
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(vis[v]){
                auto it=node[vis[v]][col[u]].find(weight[i]);
                node[vis[v]][col[u]].erase(it);
                node[vis[v]][c].insert(weight[i]);
            }
        }
    }
    col[u]=c;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
        arr[u].t++,arr[v].t++;
    }
    for(int i=1;i<=n;i++){
        col[i]=1;
        arr[i].sub=i;
    }
    prepare();
    int T;
    cin>>T;
    while(T--){
        string op;
        int x;
        cin>>op;
        if(op[0]=='A'){
            int u=op[3]-'A'+1;
            int v=op[4]-'A'+1;
            query(u,v);
        }
        else{
            cin>>x;
            int to=op[4]-'A'+1;
            if(col[x]==to){
                continue;
            }
            update(x,to);
        }
    }
    return 0;
}