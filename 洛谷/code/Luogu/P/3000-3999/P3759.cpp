#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
const int MAXN = 1e5+5;
const int MAXT = 5e4*250;

int n, m;
int pos[MAXN],val[MAXN];

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
long long sum[MAXT];
int tree[MAXT];
int cnt=0;
long long ans = 0;

int lowbit(int i) {
    return i & -i;
}

// 线段树单点修改，jobi这个数字词频增加jobv
int innerAdd(int jobi, int jobv,int k, int l, int r, int i) {
    if (i == 0)
        i = ++cnt;
    if (l == r) {
        sum[i] += jobv;
        tree[i]+=k;
    } else {
        int mid = (l + r) / 2;
        if (jobi <= mid) {
            ls[i] = innerAdd(jobi, jobv,k, l, mid, ls[i]);
        } else {
            rs[i] = innerAdd(jobi, jobv,k, mid + 1, r, rs[i]);
        }
        sum[i] = sum[ls[i]] + sum[rs[i]];
        tree[i] = tree[ls[i]] + tree[rs[i]];
    }
    return i;
}

// 查询的数字范围[jobl...jobr]，线段树的数字范围[l..r]，节点编号i
// 返回有多少逆序权值
pair<long long,int> innerQuery(int jobl, int jobr, int l, int r, int i) {
    if (i == 0)
        return {0,0};
    if (jobl <= l && r <= jobr)
        return {sum[i],tree[i]};
    int mid = (l + r) / 2;
    long long ans = 0;
    int tot=0;
    pair<long long,int>p;
    if (jobl <= mid) {
    	p= innerQuery(jobl, jobr, l, mid, ls[i]);
    	ans+=p.first;
    	tot+=p.second;
    }
    if (jobr > mid) {
    	p= innerQuery(jobl, jobr, mid + 1, r, rs[i]);
    	ans+=p.first;
    	tot+=p.second;
    }
    return {ans,tot};
}

// arr的i位置的数字，pos词频增加val
void add(int i, int pos,int val,int k) {
    for (int j = i; j <= n+1; j += lowbit(j)) {
        root[j] = innerAdd(pos, val,k, 1, n+1, root[j]);
    }
}

// arr[al..ar]范围上，有多少数字在[numl..numr]范围上
pair<long long,int> query(int al, int ar, int numl, int numr) {
    long long ans = 0;
    int tot=0;
    if(numl>numr){
        return {0,0};
    }
    pair<long long,int>p;
    for (int i = ar; i > 0; i -= lowbit(i)) {
        p= innerQuery(numl, numr, 1, n+1, root[i]);
        ans+=p.first;
    	tot+=p.second;
    }
    for (int i = al - 1; i > 0; i -= lowbit(i)) {
        p= innerQuery(numl, numr, 1, n+1, root[i]);
        ans-=p.first;
    	tot-=p.second;
    }
    return {ans,tot};
}

// 交换a和b位置的数字，保证a在前，b在后
// 修正好逆序对的数量ans
void compute(int a, int b) {
    pair<long long,int>p;

    p= query(a + 1, b - 1, 1, pos[a] - 1);
    ans-=(p.second*val[a]+p.first),ans%=MOD;

    p= query(a + 1, b - 1, pos[a] + 1, n);
    ans+=(p.second*val[a]+p.first),ans%=MOD;

    p= query(a + 1, b - 1, pos[b] + 1, n);
    ans-=(p.second*val[b]+p.first),ans%=MOD;

    p= query(a + 1, b - 1, 1, pos[b] - 1);
    ans+=(p.second*val[b]+p.first),ans%=MOD;

    if (pos[a] < pos[b])
        ans+=(val[a]+val[b]),ans%=MOD;
    else if (pos[a] > pos[b])
        ans-=(val[a]+val[b]),ans%=MOD;

    add(a, pos[a], -val[a],-1);
    add(b, pos[b], -val[b],-1);
    swap(pos[a], pos[b]);
    swap(val[a], val[b]);
    add(a, pos[a], val[a],1);
    add(b, pos[b], val[b],1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>pos[i]>>val[i];
        add(i,pos[i],val[i],1);
    }
    pos[n+1]=n+1,val[n+1]=0;
    add(n+1,pos[n+1],val[n+1],1);

    for(int i=2;i<=n;i++){
        pair<long long,int>p;
        p= query(1, i - 1, pos[i] +1 ,n+1);
        ans+=(p.second*val[i]+p.first);
    }

    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        if(x>y){
            swap(x,y);
        }
        if(x==y){
            cout<<ans<<endl;
            continue;
        }
        compute(x,y);
        ans=(ans%MOD+MOD)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}

