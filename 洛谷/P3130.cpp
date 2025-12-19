#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 200005;

int n,m;
long long arr[MAXN];
long long  Min[MAXN<<2],sum[MAXN<<2],add[MAXN<<2];

void up(int i){
    sum[i]=sum[i<<1]+sum[i<<1|1];
    Min[i]=min(Min[i<<1],Min[i<<1]);
}

void lazy(int i, int v,int n) {
    sum[i] +=n*v;
    Min[i] += v;
    add[i] += v;//这个数组表示是否有信息可以向下传递
}

void down(int i,int l,int r) {
    if (add[i] != 0) {
        int mid=(l+r)/2;
        // 发左
        lazy(i << 1, add[i],mid-l+1);
        // 发右
        lazy(i << 1 | 1, add[i],r-mid);
        // 父范围懒信息清空
        add[i] = 0;
    }
}

void build(int l, int r, int i) {
    if (l == r) {
        Min[i] = arr[l];
        sum[i] = arr[l];
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    add[i]=0;//初始化每一个位置都没有向下传递的信息
}

void Add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv,r-l+1);
    }else{
        int mid=(l+r)/2;
        down(i,l,r);
        if (jobl <= mid) {
            Add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            Add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);//汇总修改数据
    }
}

long long  sumquery(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i,l,r);
    long ans = 0;
    if (jobl <= mid) {
        ans +=sumquery(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans +=sumquery(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

long long minquery(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return Min[i];
    }
    int mid = (l + r) >> 1;
    down(i,l,r);
    long long ans = 3e12;
    if (jobl <= mid) {
        ans =min(ans, minquery(jobl, jobr, l, mid, i << 1));
    }
    if (jobr > mid) {
        ans =min(ans, minquery(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    build(1,n,1);
    char op;
    long long jobv;
    for(int i=1,jobl,jobr;i<=m;i++){
        cin>>op>>jobl>>jobr;
        if(op=='P'){
            cin>>jobv;
            Add(jobl,jobr,jobv,1,n,1);
        }else if(op=='M'){
            cout<<minquery(jobl,jobr,1,n,1)<<endl;
        }else{
            cout<<sumquery(jobl,jobr,1,n,1)<<endl;
        }
    }
    return 0;
}
