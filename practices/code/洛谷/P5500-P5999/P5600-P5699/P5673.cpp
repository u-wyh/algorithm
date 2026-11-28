// https://www.luogu.com.cn/problem/P5673
// 题意：给定 n 个商品的种类 p_i 和价值 v_i 以及参数 k；
// m 次询问区间 [l, r]，从右往左看，
// 若某一种类累计出现达到 k 次则该种类（含第 k 个）之后的均失效，
// 求有效礼物价值和。
// 输入 n, m, k、序列 p、序列 v 及 m 个询问区间；输出 m 行答案。
// 数据范围：1 <= n <= 10^6，1 <= m <= 5*10^5，
// 2 <= k <= n，1 <= p_i <= n
// 1 <= v_i <= 2000，1 <= l <= r <= n。
// 难度评分：1900（洛谷分级换算）
// 算法标签：树状数组、离线处理
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MAXM = 5e5+5;

int n,m,k;
int kind[MAXN];
int val[MAXN];
int t[MAXN];//表示这个种类的出现了多少次
int nxt[MAXN];//表示下一个相同种类的在什么位置
int st[MAXN];//表示这个种类第一次出现的位置
int en[MAXN];//表示这个种类上一次出现的位置
int ans[MAXN];
struct node{
    int l,r,sub;
}nums[MAXN];
int tree[MAXN];

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

bool cmp(node a,node b){
    return a.r<b.r;
}

int lowbit(int x){
    return x&(-x);
}

int sum(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void add(int x,int val){
    while(x<=n){
        tree[x]+=val;
        x+=lowbit(x);
    }
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++){
        kind[i]=read();
        if(st[kind[i]]==0){
            st[kind[i]]=i;
        }
        else{
            nxt[en[kind[i]]]=i;
        }
        en[kind[i]]=i;
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=m;i++){
        nums[i].l=read(),nums[i].r=read();
        nums[i].sub=i;
    }
    sort(nums+1,nums+m+1,cmp);
    int r=0;
    for(int i=1;i<=n;i++){
        en[kind[i]]=st[kind[i]];
    }
    for(int i=1;i<=m;i++){
        while(nums[i].r>r){
            r++;
            t[kind[r]]++;
            add(r,val[r]);
            if(t[kind[r]]>=k){
                t[kind[r]]--;
                add(en[kind[r]],-val[en[kind[r]]]);
                en[kind[r]]=nxt[en[kind[r]]];
            }
        }
        ans[nums[i].sub]=sum(nums[i].r)-sum(nums[i].l-1);
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
