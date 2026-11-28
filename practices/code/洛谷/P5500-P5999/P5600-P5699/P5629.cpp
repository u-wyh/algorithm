// https://www.luogu.com.cn/problem/P5629
// 题意：给定数列 a（长 n）、m 个原数 b 和参数 d，
// 一个数能被某原数消灭当
// 且仅当不断除以 d 下取整若干次能变成该原数（原数不消耗）；
// 多次询问区间 [l, r] 在消灭最多数前提下最少需要多少个原数。
// 输入 n, m, d, q、数列 a、原数 b 及 q 个询问区间；
// 每行输出一次询问的答案。
// 数据范围：n <= 5*10^5，m <= 60，
// 2 <= d <= 10，q <= 10^6，
// 0 <= a_i, b_i < 2^63。
// 难度评分：2000（洛谷分级换算）
// 算法标签：可持久化线段树、前缀和
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = MAXN*4;

int n,m,d,q;
long long a[MAXN],b[65];
bool c[65];
int root[MAXN];
int tree[MAXM];
int ls[MAXM];
int rs[MAXM];
int cnt=0;

int build(int l, int r) {
    int rt = ++cnt;
    tree[rt] = 0;
    if (l < r) {
        int mid = (l + r) / 2;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
    }
    return rt;
}

int insert(int jobi, int l, int r, int i) {
//    if(l==1&&r==m){
//        cout<<jobi<<endl;
//    }
    int rt = ++cnt;
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    tree[rt] = tree[i] + 1;
    if (l < r) {
        int mid = (l + r) / 2;
        if (jobi <= mid) {
            ls[rt] = insert(jobi, l, mid, ls[rt]);
        } else {
            rs[rt] = insert(jobi, mid + 1, r, rs[rt]);
        }
    }
    return rt;
}

int query(int l,int r,int u,int v){
    if(l==r){
        return tree[u]>tree[v]?1:0;
    }
    else{
        int mid=(l+r)/2;
        int ans=0;
        ans+=query(l,mid,ls[u],ls[v]);
        ans+=query(mid+1,r,rs[u],rs[v]);
        return ans;
    }
}

signed main()
{
    scanf("%d %d %d %d",&n,&m,&d,&q);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%lld",&b[i]);
        c[i]=true;
    }
    sort(b+1,b+m+1);
    for(int i=m;i>=1;i--){
        long long t=b[i];
        while(c[i]){
            for(int j=1;j<i;j++){
                if(b[j]==t){
                    c[i]=false;
                }
            }
            if(t==0){
                break;
            }
            t/=d;
        }
    }
    bool flag1= (b[1]==0) ;
    int pos=1;
    root[0]=build(1,m);
    for(int i=1;i<=n;i++){
        long long t=a[i];
        bool flag=false;
        while(t){
            for(int j=1;j<=m;j++){
                if(c[j]&&t==b[j]){
                    root[i]=insert(j,1,m,root[i-1]);
                    flag=true;
                }
                if(flag){
                    break;
                }
            }
            if(flag){
                break;
            }
            t/=d;
        }
        if(!flag&&flag1){
            root[i]=insert(pos,1,m,root[i-1]);
        }
    }
    for(int i=1;i<=q;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        printf("%d\n",query(1,m,root[v],root[u-1]));
    }
    return 0;
}
