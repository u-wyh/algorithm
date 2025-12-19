#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 1e6+5;
const int base = 1500005;
typedef unsigned int ui ;

int last=7;
int n,m;
ui seed;
int val[MAXN];

int head = 0;
int cnt = 0;
int key[MAXM];
int ls[MAXM];
int rs[MAXM];
int sz[MAXM];
double priority[MAXM];

int sta[MAXM];
int top=0;

int randNum( ui& seed , ui last , const ui m){ 
    seed = seed * 17 + last ; 
    return seed % m + 1; 
}

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

void up(int i) {
    sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
}

void split(int l, int r, int i, int num) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        if (key[i] <= num) {
            rs[l] = i;
            split(i, r, rs[i], num);
        } else {
            ls[r] = i;
            split(l, i, ls[i], num);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

void add(int num) {
    split(0, 0, head, num);
    int u;
    if(top){
        u=sta[top--];
    }
    else{
        cnt++;
        u=cnt;
    }
    key[u] = num;
    sz[u] = 1;
    ls[u]=rs[u]=0;
    priority[u] = (double)rand() / RAND_MAX;
    head = merge(merge(rs[0], u), ls[0]);
}

void remove(int num) {
    split(0, 0, head, num);
    int lm = rs[0];
    int r = ls[0];
    split(0, 0, lm, num - 1);
    int l = rs[0];
    int m = ls[0];
    sta[++top]=m;
    head = merge(merge(l, merge(ls[m], rs[m])), r);
}

int getRank(int num) {
    split(0, 0, head, num +1);
    int ans = sz[ls[0]];
    head = merge(rs[0], ls[0]);
    return ans;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cnt=0;
        top=0;
        head=0;
        m=read(),n=read(),seed=read();
        for(int i=1;i<=n;i++){
            int u=randNum(seed,(ui)last,(ui)m);
            int v=randNum(seed,(ui)last,(ui)m);
            if(val[u])
                remove(val[u]);
            val[u]+=(base-v);
            add(val[u]);
            last=getRank(val[u]);
            printf("%lld\n",last);
        }
    }
    return 0;
}