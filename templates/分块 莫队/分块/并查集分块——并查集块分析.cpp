// https://www.luogu.com.cn/problem/P8360
// 这道题的思路是很巧妙的  大思路是按照每块进行操作 看看每块的贡献
// 计算每块的时候 用到了树形数据结构和并查集  将原始的数据建立一个图
// 并查集的作用是收集每个党派的代表树上节点的编号  同时设置sum实时维护块的和
// 叶子结点是每个位置上的值  每个节点包含4个信息  父亲节点 子树中叶节点个数（即实际包含位置个数） 所属党派  以及新添加的军队数量（懒标记）
// 对于整块操作而言  操作1 如果qx不存在  那么跳过    如果qy不存在  那么将qx这个党派的信息全部过渡给y这个党派  
// 否则新建一个节点 将qx和qy的父亲节点设置为这个新结点
// 操作二的话  直接更新懒信息即可   操作3  收集区间
// 对于散块操作的话  那么直接将所有的懒信息下发   使得所有叶节点上就是此时的真实信息
// 然后暴力更新操作 收集答案  最后重新建立好这个树  
// 注意无论是一开始建立的树  还是散块操作之后建立的树   它们实际上是森林 也就是不是一个联通块  按照他们的党派进行划分
// 时间复杂度  如果是整块  操作代价是O(1)  那么整块操作的总代价是O(q*根号n)
// 散块操作最多是2*q个操作  暴力更新的代价也是O(q*根号n)  
// 考虑建立树的代价 最多节点个数不会超过叶子结点的2倍 也就是每次最多2*根号n
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 250005;
const int MAXB = 505;
const int MAXM = MAXB*3;

int n,q,m;
// 初始时每个位置上的军队数量以及所属党派
int army[MAXN];
int bel[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int op[MAXN];
int ql[MAXN];
int qr[MAXN];
int qx[MAXN];
int qy[MAXN];

// 新建节点的编号
int cnt;
// 每个党派的代表节点
int fa[MAXN];
// 每个树上节点的父亲节点
int f[MAXM];
// 子树中叶子结点个数
int sz[MAXM];
// 这个节点所属党派
int col[MAXM];
// 新添加的军队数量
long long tag[MAXM];
// 区间总数量
long long sum;

long long ans[MAXN];

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
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }
}

void compute(int l,int r){
    // 所有党派的信息最初代表都是0  表示这个块中没有这个党派
    for(int i=1;i<=m;i++){
        fa[i]=0;
    }
    // 收集这个块中的初始信息
    for(int i=l;i<=r;i++){
        tag[i-l+1]=army[i];
        col[i-l+1]=bel[i];
    }
    int len=r-l+1;
    sum=0;
    // 将以前的信息清空  col信息在设置这个节点的时候 就会被设置  所以不需要管
    for(int i=len+1;i<=cnt;i++){
        f[i]=0;
        tag[i]=0;
    }
    cnt=len;
    // 最初  全部都是叶子结点
    for(int i=1;i<=len;i++){
        f[i]=0;
        sum+=tag[i];
        sz[i]=1;
    }
    for(int i=1;i<=len;i++){
        // 第一次出现
        if(!fa[col[i]]){
            ++cnt;
            fa[col[i]]=cnt;
            sz[cnt]=1;
            col[cnt]=col[i];
            f[i]=cnt;
        }
        else{
            int u=fa[col[i]];
            // if(u<=len){
            //     // 这里的操作实际上是为了第一次操作时设置的   只有非叶节点才能成为代表节点
            //     // 这样设置是很巧妙的  其实第一次出现时也可以设置这样一个节点  但是这样可能会导致树的节点个数变多 并且是没必要的
            //     // 用上面的写法也是一样的 但是注意此时MAXM=MAXN*3 
            //     ++cnt;
            //     fa[col[i]]=cnt;
            //     f[u]=cnt;
            //     u=cnt;
            //     sz[cnt]=1;
            //     col[cnt]=col[i];
            // }
            f[i]=u;
            ++sz[u];
        }
    }

    for(int i=1;i<=q;i++){
        if(ql[i]>r||qr[i]<l){
            continue;
        }
        // 整块包含
        if(ql[i]<=l&&r<=qr[i]){
            if(op[i]==1){
                if(qx[i]==qy[i]||!fa[qx[i]]){
                    continue;
                }
                else if(!fa[qy[i]]){
                    col[fa[qx[i]]]=qy[i];
                    fa[qy[i]]=fa[qx[i]];
                    fa[qx[i]]=0;
                }
                else{
                    // 合并两个根节点  实际上就是将两个党派合并
                    int u=++cnt;
                    f[fa[qx[i]]]=u;
                    f[fa[qy[i]]]=u;
                    col[u]=qy[i];
                    sz[u]=sz[fa[qx[i]]]+sz[fa[qy[i]]];
                    fa[qy[i]]=u;
                    fa[qx[i]]=0;
                }
            }
            else if(op[i]==2){
                if(fa[qx[i]]){
                    // 懒更新  不要忘记更新sum
                    tag[fa[qx[i]]]+=qy[i];
                    sum+=1ll*qy[i]*sz[fa[qx[i]]];
                }
            }
            else{
                ans[i]+=sum;
            }
        }
        else{
            // 将所有信息全部下发
            for(int u=cnt;u;u--){
                if(f[u]){
                    tag[u]+=tag[f[u]];
                    col[u]=col[f[u]];
                }
            }
            for(int u=len+1;u<=cnt;u++){
                tag[u]=0,f[u]=0;
            }
            cnt=len;
            for(int j=1;j<=len;j++){
                fa[col[j]]=0;
                f[j]=0;
            }

            int lt=max(ql[i],l)-l+1;
            int rt=min(qr[i],r)-l+1;
            // 暴力维持信息
            if(op[i]==1){
                for(int u=lt;u<=rt;u++){
                    if(col[u]==qx[i]){
                        col[u]=qy[i];
                    }
                }
            }
            else if(op[i]==2){
                for(int u=lt;u<=rt;u++){
                    if(col[u]==qx[i]){
                        sum+=qy[i];
                        tag[u]+=qy[i];
                    }
                }
            }
            else{
                for(int u=lt;u<=rt;u++){
                    ans[i]+=tag[u];
                }
            }

            // 重新建立树
            for(int p=1;p<=len;p++){
                if(!fa[col[p]]){
                    fa[col[p]]=p;
                }
                else{
                    int u=fa[col[p]];
                    if(u<=len){
                        ++cnt;
                        fa[col[p]]=cnt;
                        f[u]=cnt;
                        u=cnt;
                        sz[cnt]=1;
                        col[cnt]=col[p];
                    }
                    f[p]=u;
                    ++sz[u];
                }
            }
        }
    }
}

int main()
{
    n=read(),q=read(),m=read();
    for(int i=1;i<=n;i++){
        army[i]=read();
    }
    for(int i=1;i<=n;i++){
        bel[i]=read();
    }
    for(int i=1;i<=q;i++){
        op[i]=read(),ql[i]=read(),qr[i]=read();
        if(op[i]!=3){
            qx[i]=read(),qy[i]=read();
        }
    }
    prepare();
    for(int i=1;i<=bnum;i++){
        compute(bl[i],br[i]);
    }
    for(int i=1;i<=q;i++){
        if(op[i]==3){
            printf("%lld\n",ans[i]);
        }
    }
    return 0;
}