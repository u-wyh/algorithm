// https://www.luogu.com.cn/problem/P3278
// 题意：维护无穷多项式 f(x)=sum a_i x^i（初始全 0），
// 支持 n 次操作：
// mul L R v（[L,R] 次项系数乘 v）、add L R
// v（[L,R] 次项系数加 v）。
// mulx L R（[L,R] 次项乘 x）、query
// v（输出 f(v) mod 20130426，不改多项式）。
// 逐行输出每个 query 的结果。
// 数据范围：
// N <= 10^5（操作数 n）
// 0 <= L <= R <= 10^5（次项范围）
// 0 <= v <= 10^9（参数值，query 操作不超过 10 次）
// 难度评分：2600（洛谷分级换算）
// 算法标签：FHQ-Treap、懒标记
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 20130426;
const int MAXN = 2e5+5;

int n;

int head=0;
int cnt=0;
int key[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
double priority[MAXN];
int addtag[MAXN];
int multag[MAXN];

int newnode(int val){
    int cur=++cnt;
    key[cur]=val;
    multag[cur]=1;
    sz[cur]=1;
    priority[cur]=(double)rand()/RAND_MAX;
    return cnt;
}

void up(int i){
    sz[i]=sz[ls[i]]+sz[rs[i]]+1;
}

void mullazy(int i,int v){
    key[i]=(1ll*key[i]*v)%MOD;
    addtag[i]=(1ll*addtag[i]*v)%MOD;
    multag[i]=(1ll*multag[i]*v)%MOD;
}

void addlazy(int i,int v){
    key[i]=(key[i]+v)%MOD;
    addtag[i]=(addtag[i]+v)%MOD;
}

void down(int i){
    if(multag[i]!=1){
        mullazy(ls[i],multag[i]);
        mullazy(rs[i],multag[i]);
        multag[i]=1;
    }
    if(addtag[i]){
        addlazy(ls[i],addtag[i]);
        addlazy(rs[i],addtag[i]);
        addtag[i]=0;
    }
}

int merge(int l,int r){
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        down(l);//下发懒信息
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        down(r);
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

void split(int l, int r, int i, int rank) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        down(i);
        if (sz[ls[i]] + 1 <= rank) {
            rs[l] = i;
            split(i, r, rs[i], rank - sz[ls[i]] - 1);
        } else {
            ls[r] = i;
            split(l, i, ls[i], rank);
        }
        up(i);
    }
}

// 查询第pos位置的值是多少  注意这道题是0based
int query(int rk){
    split(0,0,head,rk);
    int lm=rs[0];
    int r=ls[0];
    split(0,0,lm,rk-1);
    int ans=key[ls[0]];
    head=merge(merge(rs[0],ls[0]),r);
    return ans;
}

void add(int x,int y,int v){
    split(0,0,head,y);
    int lm=rs[0];
    int r=ls[0];
    split(0,0,lm,x-1);
    addlazy(ls[0],v);
    head=merge(merge(rs[0],ls[0]),r);
}

void mul(int x,int y,int v){
    split(0,0,head,y);
    int lm=rs[0];
    int r=ls[0];
    split(0,0,lm,x-1);
    mullazy(ls[0],v);
    head=merge(merge(rs[0],ls[0]),r);
}

void change(int x,int y){
    split(0,0,head,y);
    int lm=rs[0];
    int r=ls[0];
    split(0,0,lm,y-1);
    int val=key[ls[0]];
    head=merge(rs[0],r);
    add(y,y,val);
    split(0,0,head,x-1);
    lm=rs[0];
    r=ls[0];
    head=merge(merge(lm,newnode(0)),r);
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int i=0;i<=100002;i++){
        head=merge(head,newnode(0));
    }
    int now=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        string op;
        int l,r,v;
        cin>>op;
        if(op[0]=='q'){
            cin>>v;
            long long ans=0;
            int power=1;
            for(int p=1;p<=now;p++){
                ans=(ans+1ll*power*query(p)%MOD)%MOD;
                power=(power*v)%MOD;
            }
            ans=(ans%MOD+MOD)%MOD;
            cout<<ans<<endl;
        }
        else{
            cin>>l>>r;
            l++,r++;
            if(op=="mulx"){
                change(l,r);
            }
            else{
                cin>>v;
                if(op[0]=='m'){
                    mul(l,r,v);
                }
                else{
                    add(l,r,v);
                }
            }
            now=max(now,r+1);
        }
    }
    return 0;
}