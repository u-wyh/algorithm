#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXB = 4005;

int n,limit,maxv;
int a[MAXN];
int b[MAXN];
long long ans;

int ls[MAXN];
int rs[MAXN];
int sta[MAXN];
int lt[MAXN];
int rt[MAXN];

// 小模数离线询问
// 一个询问表示：
// 在前缀[1,qx]中，统计与区间[ql,qr]余数相同的点对数量
// qk为容斥系数，qnxt和qhead组成按模数分类的链表
int qhead[MAXB];
int qk[MAXN<<2];
int qx[MAXN<<2];
int ql[MAXN<<2];
int qr[MAXN<<2];
int qnxt[MAXN<<2];
int qcnt=1;

// 这个实际上是用于收集所有的同一个模数的答案
int qord[MAXN<<2];

int valcnt[MAXN];
int modv[MAXN];

// remv[i]：处理当前大模数节点时，b[i]对该模数的余数
// remcnt[x]：余数x在临时区间中的出现次数
int remv[MAXN];
int remcnt[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void build(){
    int top = 0;
    for (int i = 1; i <= n; i++) {
        int pos = top;

        while (pos > 0 && a[sta[pos]] <= a[i]) {
            //单调栈  弹出不符合的元素
            pos--;
        }

        // 插入一个元素 它是连接在哪个节点的右孩子上的   哪些节点连接到它的左孩子
        if (pos > 0) {
            //那么就是没有弹干净   那么当前节点就会成为栈顶节点的右孩子
            rs[sta[pos]] = i;
        }

        if (pos < top) {
            //表示有元素弹出 那么一定是当前节点的左孩子节点
            ls[i] = sta[pos + 1];
        }

        sta[++pos] = i;//加入栈中
        top = pos;
    }
}

inline void addquerynode(int p,int x,int l,int r,int k){
    qnxt[qcnt]=qhead[p];
    qx[qcnt]=x;
    ql[qcnt]=l;
    qr[qcnt]=r;
    qk[qcnt]=k;
    qhead[p]=qcnt++;
}

inline void addquery(int x,int xl,int xr,int yl,int yr){
    if(xl>xr||yl>yr){
        return ;
    }
    if((xr-xl)>=(yr-yl)){
        swap(xr,yr);
        swap(xl,yl);
    }
    addquerynode(x,yr,xl,xr,1);
    addquerynode(x,yl-1,xl,xr,-1);
}

void collect(int l,int r,int u){
    if(u==0){
        return ;
    }
    lt[u]=l;
    rt[u]=r;
    if(a[u]<=limit){
        addquery(a[u],l,u-1,u+1,r);
        addquery(a[u],u,u,l,r);
    }

    collect(l,u-1,ls[u]);
    collect(u+1,r,rs[u]);
}

bool cmp(int x,int y){
    return qx[x]<qx[y];
}

void computesml(){
    for(int p=1;p<=limit;p++){
        if(qhead[p]==0){
            continue;
        }

        int cnt=0;
        for(int i=qhead[p];i;i=qnxt[i]){
            qord[++cnt]=i;
        }
        sort(qord+1,qord+cnt+1,cmp);

        for(int i=0;i<p;i++){
            valcnt[i]=0;
        }
        for(int i=1;i<=n;i++){
            modv[i]=b[i]%p;
        }

        int cur=1;
        for(int i=1;i<=cnt;i++){
            int id=qord[i];
            while(cur<=qx[id]){
                valcnt[modv[cur]]++;
                cur++;
            }

            long long res=0;
            for(int j=ql[id];j<=qr[id];j++){
                res+=valcnt[modv[j]];
            }

            ans+=res*qk[id];
        }
    }
}

void addbucket(int l,int r,int v){
    for(int i=l;i<=r;i++){
        valcnt[b[i]]+=v;
    }
}

// 桶中保存右子树，枚举左子树和节点u
inline void solveleft(int u){
    int l=lt[u];
    int p=a[u];
    int ur=b[u]%p;

    for(int i=l;i<=u;i++){
        int x=b[i]%p;

        // 统计(i,u)，其中i=u时统计单点区间
        ans+=(x==ur);

        // 统计当前点与右子树中所有同余位置
        for(int v=x;v<=maxv;v+=p)
            ans+=valcnt[v];
    }
}

// 桶中保存左子树，枚举节点u和右子树
inline void solveright(int u){
    int r=rt[u];
    int p=a[u];
    int ur=b[u]%p;

    for(int i=u;i<=r;i++){
        int x=b[i]%p;

        // 统计(u,i)，其中i=u时统计单点区间
        ans+=(x==ur);

        // 统计当前点与左子树中所有同余位置
        for(int v=x;v<=maxv;v+=p)
            ans+=valcnt[v];
    }
}

// 直接扫描整个子树，按余数统计当前大模数节点的答案
inline void solvebrute(int u){
    int l=lt[u];
    int r=rt[u];
    int p=a[u];
    int ur=b[u]%p;

    // 将节点u和右子树加入余数桶
    // 同时统计节点u与右侧位置形成的区间
    for(int i=u;i<=r;i++){
        remv[i]=b[i]%p;
        remcnt[remv[i]]++;
        ans+=(remv[i]==ur);
    }

    // 统计左子树与节点u、右子树之间的点对
    for(int i=l;i<u;i++){
        remv[i]=b[i]%p;
        ans+=remcnt[remv[i]];
    }

    // 清空临时余数桶
    for(int i=u;i<=r;i++)
        remcnt[remv[i]]--;
}

void computebig(int u){
    if(u==0){
        return ;
    }

    int l=lt[u];
    int r=rt[u];
    int ltlen=u-l;
    int rtlen=r-u;

    if(l==r){
        if(a[u]>limit){
            ans++;
        }
        valcnt[b[u]]++;
        return ;
    }

    if(ltlen<=rtlen){
        // 左子树较短，先处理并移出桶
        computebig(ls[u]);
        addbucket(l,u-1,-1);

        // 处理右子树后，桶中只保留右子树
        computebig(rs[u]);

        if(a[u]>limit){
            long long cost1=1LL*ltlen*(maxv/a[u]+1);
            long long cost2=ltlen+rtlen+1;

            if(cost1<cost2)
                solveleft(u);
            else
                solvebrute(u);
        }

        // 将左子树和节点u加入，恢复当前整棵子树
        addbucket(l,u,1);
    }
    else{
        // 右子树较短，先处理并移出桶
        computebig(rs[u]);
        addbucket(u+1,r,-1);

        // 处理左子树后，桶中只保留左子树
        computebig(ls[u]);

        if(a[u]>limit){
            long long cost1=1LL*rtlen*(maxv/a[u]+1);
            long long cost2=ltlen+rtlen+1;

            if(cost1<cost2)
                solveright(u);
            else
                solvebrute(u);
        }

        // 将节点u和右子树加入，恢复当前整棵子树
        addbucket(u,r,1);
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    for(int i=1;i<=n;i++){
        b[i]=read();
        maxv=max(maxv,b[i]);
    }
    limit=(int)(sqrt(n)*0.5)+1;

    build();

    int root=sta[1];

    collect(1,n,root);
    computebig(root);
    computesml();

    cout<<ans<<endl;
    return 0;
}