// https://codeforces.com/problemset/problem/617/E
// 题意：长为 n 的数组 a 与整数 k，m 次询问区间 [l, r]。
// 输出：每次询问输出 [l, r] 内异或和恰好等于 k 的连续子段个数。
// 数据范围：1 <= n, m <= 10^5，
// 0 <= k, a_i <= 10^6。
// 1 <= l <= r <= n。
// 难度评分：2200（CF 官方）
// 算法标签：莫队、前缀异或
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e6+5;

int n,m,k;
int arr[MAXN];
struct node{
    int l,r,id;
}nums[MAXN];
long long  ans[MAXN];
int pos[MAXN];
int tot[2000010];
long long  sum;


inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}return f*x;}

bool cmp(node a,node b){
    return (pos[a.l]==pos[b.l])?a.r<b.r:(pos[a.l]&1)?a.r<b.r:a.r>b.r;
}

void Add(int n){
    //将一个数字加入  并计算贡献
    sum+=tot[arr[n]^k];
    tot[arr[n]]++;
}

void Sub(int n){
    //减去一个数字   并处理影响
    tot[arr[n]]--;
    sum-=tot[arr[n]^k];
}

signed main()
{
    cin>>n>>m>>k;
    int siz=pow(n,2.0/3.0);
    for(int i=1;i<=n;i++){
        arr[i]=read();
        arr[i]^=arr[i-1];
        pos[i]=i/siz;
    }
    for(int i=1;i<=m;i++){
        nums[i].l=read();
        nums[i].r=read();
        nums[i].id=i;
    }
    sort(nums+1,nums+m+1,cmp);
    tot[0]=1;
    int l=0,r=0;
    for(int i=1;i<=m;i++){
        while(nums[i].l-1<l) Add(--l);
        while(nums[i].r>r) Add(++r);
        while(nums[i].l-1>l) Sub(l++);
        while(nums[i].r<r) Sub(r--);
        //匹配区间  得到答案
        ans[nums[i].id]=sum;
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}

