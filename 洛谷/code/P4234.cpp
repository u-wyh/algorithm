#include<bits/stdc++.h>
using namespace std;

const int MAXN = 5e4+5;
const int MAXM = 2e5+5;
const int MAXV = MAXN+MAXM;
const int MAXW = 1e4;
const int INF = 1e9;

// 图中的边
struct Edge{
    int u;
    int v;
    int w;
};

int n,m;

// 排序后的边
Edge edge[MAXM];

// Link-Cut Tree 的父亲和两个儿子
int fa[MAXV];
int ch[MAXV][2];

// 节点代表的边权
int val[MAXV];

// 子树中最小权值节点的编号
int mn[MAXV];

// 区间翻转标记
bool revtag[MAXV];

// splay 下传标记使用的栈
int sta[MAXV];

// 边节点对应的两个端点
int eu[MAXV];
int ev[MAXV];

// 当前生成森林中每种边权的数量
int weightCnt[MAXW+5];

// 按照边权升序排序
bool cmpEdge(const Edge &a,const Edge &b){
    return a.w<b.w;
}

// 判断节点是否为当前辅助树的根
bool isroot(int x){
    int f=fa[x];
    return ch[f][0]!=x&&ch[f][1]!=x;
}

// 更新节点维护的信息
void up(int x){
    mn[x]=x;

    if(ch[x][0]&&val[mn[ch[x][0]]]<val[mn[x]]){
        mn[x]=mn[ch[x][0]];
    }

    if(ch[x][1]&&val[mn[ch[x][1]]]<val[mn[x]]){
        mn[x]=mn[ch[x][1]];
    }
}

// 给节点添加翻转标记
void pushrev(int x){
    if(!x){
        return;
    }

    swap(ch[x][0],ch[x][1]);
    revtag[x]^=1;
}

// 下传翻转标记
void down(int x){
    if(!revtag[x]){
        return;
    }

    pushrev(ch[x][0]);
    pushrev(ch[x][1]);
    revtag[x]=0;
}

// 旋转节点
void rotate(int x){
    int y=fa[x];
    int z=fa[y];
    int k=(ch[y][1]==x);
    int b=ch[x][k^1];

    if(!isroot(y)){
        ch[z][ch[z][1]==y]=x;
    }

    fa[x]=z;
    ch[x][k^1]=y;
    fa[y]=x;
    ch[y][k]=b;

    if(b){
        fa[b]=y;
    }

    up(y);
    up(x);
}

// 将节点旋转到辅助树根部
void splay(int x){
    int top=0;

    sta[++top]=x;

    for(int y=x;!isroot(y);y=fa[y]){
        sta[++top]=fa[y];
    }

    while(top){
        down(sta[top--]);
    }

    while(!isroot(x)){
        int y=fa[x];
        int z=fa[y];

        if(!isroot(y)){
            if((ch[y][0]==x)^(ch[z][0]==y)){
                rotate(x);
            }else{
                rotate(y);
            }
        }

        rotate(x);
    }
}

// 打通根到节点的首选路径
void access(int x){
    for(int y=0;x;y=x,x=fa[x]){
        splay(x);
        ch[x][1]=y;
        up(x);
    }
}

// 将节点设置为原树的根
void makeroot(int x){
    access(x);
    splay(x);
    pushrev(x);
}

// 查询节点所在原树的根
int findroot(int x){
    access(x);
    splay(x);

    down(x);

    while(ch[x][0]){
        x=ch[x][0];
        down(x);
    }

    splay(x);
    return x;
}

// 提取两个节点之间的路径
void split(int x,int y){
    makeroot(x);
    access(y);
    splay(y);
}

// 连接两个原树节点
void link(int x,int y){
    makeroot(x);

    if(findroot(y)!=x){
        fa[x]=y;
    }
}

// 删除两个节点之间的直接连边
void cut(int x,int y){
    makeroot(x);
    access(y);
    splay(y);

    if(ch[y][0]==x&&!ch[x][1]){
        ch[y][0]=0;
        fa[x]=0;
        up(y);
    }
}

// 初始化点节点
void init(){
    for(int i=1;i<=n;i++){
        val[i]=INF;
        mn[i]=i;
    }
}

// 计算最小边权差值
int solve(){
    if(n==1){
        return 0;
    }

    sort(edge+1,edge+m+1,cmpEdge);
    init();

    int treeEdgeCnt=0;
    int minWeight=MAXW+1;
    int maxWeight=0;
    int ans=INF;

    for(int i=1;i<=m;i++){
        int u=edge[i].u;
        int v=edge[i].v;
        int w=edge[i].w;

        // 自环不可能出现在生成树中
        if(u==v){
            continue;
        }

        // 每条边建立一个独立的边节点
        int id=n+i;

        val[id]=w;
        mn[id]=id;
        eu[id]=u;
        ev[id]=v;

        // 两个端点不连通，直接加入生成森林
        if(findroot(u)!=findroot(v)){
            link(u,id);
            link(id,v);

            treeEdgeCnt++;
            weightCnt[w]++;

            minWeight=min(minWeight,w);
            maxWeight=w;
        }else{
            // 已经连通，查询环上权值最小的边
            split(u,v);

            int old=mn[v];

            // 用新边替换环上的较小边
            if(val[old]<w){
                cut(old,eu[old]);
                cut(old,ev[old]);

                weightCnt[val[old]]--;
                weightCnt[w]++;

                if(val[old]==minWeight&&weightCnt[minWeight]==0){
                    while(minWeight<=MAXW&&weightCnt[minWeight]==0){
                        minWeight++;
                    }
                }

                link(u,id);
                link(id,v);

                maxWeight=w;
            }
        }

        // 当前生成森林已经成为生成树
        if(treeEdgeCnt==n-1){
            ans=min(ans,maxWeight-minWeight);
        }
    }

    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m;

    for(int i=1;i<=m;i++){
        cin>>edge[i].u>>edge[i].v>>edge[i].w;
    }

    cout<<solve()<<'\n';

    return 0;
}