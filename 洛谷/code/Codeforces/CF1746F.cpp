// https://codeforces.com/problemset/problem/1746/F
// 题意：给长为 n 的数组和 q 次操作。
// 1 i x 将 a_i 改成 x。
// 2 l r k 问区间内每种数的出现次数是否都是 k 的倍数。
// 输出：逐行输出每次查询的 YES 或 NO。
// 数据范围：1 <= n, q <= 3*10^5，
// 1 <= a_i, x <= 10^9，1 <= k <= n，
// 1 <= i <= n，1 <= l <= r <= n。
// 算法标签：随机化、树状数组、离散化
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;
const int MOD = 1e9+7;

int n,q,m=1;
int nums[MAXN];
int tmp[MAXN<<1];
bool ans[MAXN];
int cnt;
int h[MAXN<<1];

int op[MAXN];
int l[MAXN],r[MAXN],k[MAXN];
int pos[MAXN],v[MAXN];

int tree[MAXN];
mt19937_64 rng(time(0));

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

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

int find(int val){
    int l=1,r=m,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(tmp[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

signed main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
        tmp[i]=nums[i];
    }
    cnt=n;
    for(int i=1;i<=q;i++){
        ans[i]=true;
        op[i]=read();
        if(op[i]==1){
            pos[i]=read(),v[i]=read();
            tmp[++cnt]=v[i];
        }
        else{
            l[i]=read(),r[i]=read(),k[i]=read();
        }
    }
    sort(tmp+1,tmp+cnt+1);
    for(int i=2;i<=cnt;i++){
        if(tmp[i]!=tmp[i-1]){
            tmp[++m]=tmp[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i]=find(nums[i]);
    }
    for(int i=1;i<=q;i++){
        if(op[i]==1){
            v[i]=find(v[i]);
        }
    }
    for(int i=1;i<=n;i++){
        tmp[i]=nums[i];
    }
    int T=20;
    while(T--){
        for(int i=1;i<=n;i++){
            tree[i]=0;
            nums[i]=tmp[i];
        }
        for(int i=1;i<=m;i++){
            h[i]=rng()%MOD;
        }
        for(int i=1;i<=n;i++){
            add(i,h[nums[i]]);
        }
        for(int i=1;i<=q;i++){
            if(op[i]==1){
                add(pos[i],h[v[i]]-h[nums[pos[i]]]);
                nums[pos[i]]=v[i];
            }
            else{
                if(ans[i]){
                    if((r[i]-l[i]+1)%k[i]){
                        ans[i]=false;
                    }
                    int all=query(r[i])-query(l[i]-1);
                    if(all%k[i]){
                        ans[i]=false;
                    }
                }
            }
        }
    }
    for(int i=1;i<=q;i++){
        if(op[i]==2){
            if(ans[i]){
                cout<<"YES"<<endl;
            }
            else{
                cout<<"NO"<<endl;
            }
        }
    }
    return 0;
}