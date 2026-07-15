#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 5e5+5;
const int MAXT = MAXM*32;

int n,m,k,op;
int u[MAXM],v[MAXM];//这道题不需要建立完整的边的信息 即不用建图
int cnt=0;
int tree[MAXT];//可持久化线段树  其中只有根部的信息才是有用的
int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int val[MAXN];//表示节点i到节点1的所有递减路径上最小权值的最大值是多少
//其中val[1]初始化为最大值 其余都是最小值
int res,ans;//res用于统计答案之和

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

int build(int l,int r){
    int rt=++cnt;
    if(l==r){
        tree[rt]=val[l];//初始化
    }
    else{
        int mid=(l+r)/2;
        ls[rt]=build(l,mid);
        rs[rt]=build(mid+1,r);
    }
    return rt;
}

int insert(int jobi, int l, int r, int i) {
    int rt = ++cnt;
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    if(l==r){
        tree[rt]=val[l];
    }
    else{
        int mid = (l + r) / 2;
        if (jobi <= mid) {
            ls[rt] = insert(jobi, l, mid, ls[rt]);
        } else {
            rs[rt] = insert(jobi, mid + 1, r, rs[rt]);
        }
    }
    return rt;
}

int query(int pos,int l,int r,int i){
    if(l==r){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            return query(pos,l,mid,ls[i]);
        }
        else{
            return query(pos,mid+1,r,rs[i]);
        }
    }
}

int main()
{
    n=read(),m=read(),k=read(),op=read();
    for(int i=1;i<=m;i++){
        u[i]=read(),v[i]=read();
    }
    for(int i=1;i<=n;i++){
        val[i]=INT_MIN;
    }
    val[1]=INT_MAX;
    root[0]=build(1,n);
    for(int i=1;i<=m;i++){
        val[u[i]]=max(val[u[i]],min(i,val[v[i]]));
        //这句话的含义是 新连接了一条边  从u[i]到v[i]  边权是i
        //这条边的连接可能会导致val[u[i]]发生了变化 也可能不变化
        //那么要么是v以前和1联通了  从而导致u多了一条到1的路  这或许会导致变化
        //也有可能是v没有联通 那么就是INT_MIN  不会影响答案  或者这条边对答案没有影响
        //之所以i和val[v[i]]要比较 是因为可能v是1
        root[i]=insert(u[i],1,n,root[i-1]);
    }
    for(int i=1;i<=k;i++){
        int x,l,r;
        x=read(),l=read(),r=read();
        x^=(res*op),l^=(res*op),r^=(res*op);
        ans=(query(x,1,n,root[r])>=l)?1:0;
        cout<<ans<<endl;
        res+=ans;
    }
    return 0;
}
