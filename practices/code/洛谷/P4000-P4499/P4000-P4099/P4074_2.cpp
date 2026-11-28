// https://www.luogu.com.cn/problem/P4074
// 题意：第一行输入游览点数 n、糖果种类数 m 和操作数 q；
// 第二行输入 m 个美味指数 V_1..V_m；
// 第三行输入 n 个非递增的新奇指数 W_1..W_n。
// 接下来 n-1 行输入树的无向边 (A_i, B_i)，
// 第 n+3 行输入各点初始糖果种类 C_1..C_n；
// 随后 q 行操作：0 x y 将点 x 的糖果改为 y；
// 1 x y 询问从 x 到 y 唯一路径上第 i 次品尝某类糖果 j 累加
// V_j * W_i 的总愉悦指数。
// 对每个 Type = 1 的询问输出一行正整数。
// 数据范围：1 <= n, m, q <= 100000，
// 1 <= V_i, W_i <= 10^6（W 非递增），
// 1 <= A_i, B_i <= n
// 1 <= C_i <= m，1 <= x <= n，
// 修改时 1 <= y <= m、询问时 1 <= y <= n。
// 难度评分：2700（洛谷分级换算）
// 算法标签：树上带修改莫队、倍增、欧拉序
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXH = 20;

int n,m,q,p;
int val[MAXN];
int weight[MAXN];
int kind[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int dfncnt;
int sta[MAXN];
int ove[MAXN];
int seg[MAXN<<1];

int dep[MAXN];
int st[MAXN][MAXH];

long long sum;
int cnt[MAXN];

struct Query{
    int l,r,lca,t,id;
};
Query query[MAXN];
long long ans[MAXN];

struct Update{
    int pos,val;
};
Update update[MAXN];
int cntq,cntu;

int blen;
int bi[MAXN<<1];
bool vis[MAXN];

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u,int fa){
    sta[u]=++dfncnt;
    seg[dfncnt]=u;

    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
        }
    }

    ove[u]=++dfncnt;
    seg[dfncnt]=u;
}

void prepare(){
    p=log2(n)+1;
    dfs(1,0);

    blen=max(1.0,pow(dfncnt,2.0/3));
    for(int i=1;i<=dfncnt;i++){
        bi[i]=(i-1)/blen+1;
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }

    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

bool cmp(Query &a,Query &b){
    if(bi[a.l]!=bi[b.l]){
        return bi[a.l]<bi[b.l];
    }
    if(bi[a.r]!=bi[b.r]){
        return bi[a.r]<bi[b.r];
    }
    return a.t<b.t;
}

void add(int v){
    cnt[v]++;
    sum+=1ll*val[v]*weight[cnt[v]];
}

void del(int v){
    sum-=1ll*val[v]*weight[cnt[v]];
    cnt[v]--;
}

void change(int pos){
    vis[pos]^=1;
    if(vis[pos]){
        add(kind[pos]);
    }
    else{
        del(kind[pos]);
    }
}

void movetime(int t){
    int pos=update[t].pos;
    int val=update[t].val;
    if(vis[pos]){
        add(val);
        del(kind[pos]);
    }
    swap(update[t].val,kind[pos]);
}

void compute(){
    sort(query+1,query+cntq+1,cmp);

    int winl=1,winr=0,wint=0;
    for(int i=1;i<=cntq;i++){
        int l=query[i].l;
        int r=query[i].r;
        int t=query[i].t;
        int lca=query[i].lca;
        int id=query[i].id;

        while(winl>l){
            change(seg[--winl]);
        }
        while(winr<r){
            change(seg[++winr]);
        }
        while(winl<l){
            change(seg[winl++]);
        }
        while(winr>r){
            change(seg[winr--]);
        }
        while(wint<t){
            movetime(++wint);
        }
        while(wint>t){
            movetime(wint--);
        }
        if(lca){
            change(lca);
        }
        ans[id]=sum;
        if(lca){
            change(lca);
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>q;
    for(int i=1;i<=m;i++){
        cin>>val[i];
    }
    for(int i=1;i<=n;i++){
        cin>>weight[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        cin>>kind[i];
    }

    prepare();

    for(int i=1;i<=q;i++){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            int fa=lca(x,y);
            if(sta[x]>sta[y]){
                swap(x,y);
            }
            ++cntq;
            if(fa==x){
                query[cntq]={sta[x],sta[y],0,cntu,cntq};
            }
            else{
                query[cntq]={ove[x],sta[y],fa,cntu,cntq};
            }
        }
        else{
            ++cntu;
            update[cntu]={x,y};
        }
    }

    compute();

    for(int i=1;i<=cntq;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}