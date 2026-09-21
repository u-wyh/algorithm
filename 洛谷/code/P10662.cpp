// https://www.luogu.com.cn/problem/P10662
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,q;
int val[MAXN];
int dep[MAXN];

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];

// 提根之前，先处理沿途的翻转标记，准备一个栈记录沿途节点
int sta[MAXN];

int odd[MAXN];
int even[MAXN];
int oddtag[MAXN];
int eventag[MAXN];

// 判断节点x是不是辅助splay的顶部节点
bool isroot(int x) {
    return ls[fa[x]] != x && rs[fa[x]] != x;
}

// x不是辅助splay的顶部节点才能调用，返回x是其父的哪侧儿子
int lr(int x) {
    return ls[fa[x]] == x ? 0 : 1;
}

void lazy(int x,int o,int e){
    if(x==0){
        return ;
    }
    odd[x]^=o;
    even[x]^=e;
    oddtag[x]^=o;
    eventag[x]^=e;
}

// 处理翻转懒更新
void down(int x) {
    if(oddtag[x]||eventag[x]){
        lazy(ls[x],oddtag[x],eventag[x]);
        lazy(rs[x],oddtag[x],eventag[x]);
        oddtag[x]=0;
        eventag[x]=0;
    }
}

// x向上旋转
void rotate(int x) {
    int f = fa[x], g = fa[f];
    if (lr(x) == 0) {
        ls[f] = rs[x];
        if (ls[f] != 0) {
            fa[ls[f]] = f;
        }
        rs[x] = f;
    } else {
        rs[f] = ls[x];
        if (rs[f] != 0) {
            fa[rs[f]] = f;
        }
        ls[x] = f;
    }
    if (!isroot(f)) {
        if (lr(f) == 0) {
            ls[g] = x;
        } else {
            rs[g] = x;
        }
    }
    fa[f] = x;
    fa[x] = g;
}

// x提到辅助splay的顶部
void splay(int x) {
    int siz = 0;
    sta[++siz] = x;
    for (int y = x; !isroot(y); y = fa[y]) {
        sta[++siz] = fa[y];
    }
    while (siz != 0) {
        down(sta[siz--]);
    }
    while (!isroot(x)) {
        int f = fa[x];
        if (!isroot(f)) {
            if (lr(x) == lr(f)) {
                rotate(f);
            } else {
                rotate(x);
            }
        }
        rotate(x);
    }
}

// 打通当前原树根到x的路径，使其成为一条实链
// 可以认为这个函数就是最关键的函数
void access(int x) {
    // 从x开始，一路向上，直至达到树根所在的实链
    for (int y = 0; x != 0; y = x, x = fa[x]) {
        // 先提根，这样的话自己的右边就是应该要断掉的实链
        splay(x);
        // 断开老的实链之后,将之前已经组成的实链接上去
        rs[x] = y;
    }
}

void change(int x,int o,int e){
    access(x);
    splay(x);
    lazy(x,o,e);
}

int query(int x){
    access(x);
    splay(x);
    if(dep[x]&1){
        return even[x];
    }
    else{
        return odd[x];
    }
}

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u,int f){
    dep[u]=dep[f]+1;
    fa[u]=f;

    if(dep[u]&1){
        odd[u]=val[u];
    }
    else{
        even[u]=val[u];
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
            odd[u]^=odd[v];
            even[u]^=even[v];
        }
    }
}

int main()
{
    cin>>n>>m;
    m++;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        val[i]%=m;
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    int ans=0;
    cin>>q;
    for(int i=1;i<=q;i++){
        int op,u,v,x;
        cin>>op;
        if(op==1){
            cin>>u;
            u^=ans;
            int res=query(u);
            if(res){
                cout<<"Yes"<<endl;
                ans++;
            }
            else{
                cout<<"No"<<endl;
            }
        }
        else if(op==2){
            cin>>u>>v;
            u^=ans;
            v^=ans;
            v%=m;

            long long delta=val[u]^v;
            if(dep[u]&1){
                change(u,delta,0);
            }
            else{
                change(u,0,delta);
            }
            val[u]=v;
        }
        else{
            cin>>u>>v>>x;
            u^=ans;
            v^=ans;
            x^=ans;
            x%=m;

            dep[v]=1+dep[u];
            val[v]=x;
            fa[v]=u;

            if(dep[v]&1){
                change(v,x,0);
            }
            else{
                change(v,0,x);
            }
        }
    }
    return 0;
}