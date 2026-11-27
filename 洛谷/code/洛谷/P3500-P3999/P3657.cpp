// https://www.luogu.com.cn/problem/P3657
// 题意：输入品种数 N，
// 以及道路左侧排列 a_1..a_N 和右侧排列
// b_1..b_N（均为 1..N 的排列）。
// 若左侧某品种 a 与右侧某品种 b 满足 |a - b| <= 4，
// 则可在两者之间画一条人行道；要求所有人行道互不相交且每个牧场至多连一条。
// 输出最多能画的人行道数量。
// 数据范围：1 <= N <= 10^5。
// 算法标签：动态规划、树状数组
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int a[MAXN];
int b[MAXN];
int pos[MAXN];

int tree[MAXN];

int help[MAXN];

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

void update(int x,int val){
    while(x<=n){
        tree[x]=max(tree[x],val);
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans=max(ans,tree[x]);
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    for(int i=1;i<=n;i++){
        b[i]=read();
        pos[b[i]]=i;
    }
    for(int p=1;p<=n;p++){
        int i=a[p];
        for(int j=max(i-4,1);j<=min(n,i+4);j++){
            help[j]=query(pos[j]-1);
        }
        for(int j=max(i-4,1);j<=min(n,i+4);j++){
            update(pos[j],help[j]+1);
        }
    }
    cout<<query(n)<<endl;
    return 0;
}