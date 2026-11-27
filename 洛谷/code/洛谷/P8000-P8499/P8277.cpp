// https://www.luogu.com.cn/problem/P8277
// 题意：给定 1..N 的排列 p_1..p_N 和长为 N-1 的 U/D
// 字符串，求最大的 K <= N-1
// 使得存在 p 的子序列 a_0..a_K 满足对所有 1 <= j <= K，
// 字符串第 j 位为 U 时 a_{j-1} < a_j
// 为 D 时 a_{j-1} > a_j。
// 数据范围：2 <= N <= 3*10^5（测试点 13-22 无额外限制）。
// 算法标签：树状数组、动态规划
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n;
int val[MAXN];
char s[MAXN];

int tree[2][MAXN];

inline int lowbit(int x){
    return x&-x;
}

void update(int op,int x,int val){
    while(x<=n){
        tree[op][x]=max(tree[op][x],val);
        x+=lowbit(x);
    }
}

int query(int op,int x){
    int ans=0;
    while(x){
        ans=max(ans,tree[op][x]);
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&val[i]);
    }
    scanf("%s",s+1);
    
    int ans=0;
    for(int i=1;i<=n;i++){
        int res=max(query(0,val[i]),query(1,n-val[i]));
        ans=max(ans,res);

        if(s[res+1]=='U'){
            update(0,val[i],res+1);
        }
        else{
            update(1,n-val[i]+1,res+1);
        }
    }

    cout<<ans<<endl;
    return 0;
}