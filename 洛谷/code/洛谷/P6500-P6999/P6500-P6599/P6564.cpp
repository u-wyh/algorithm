// https://www.luogu.com.cn/problem/P6564
// 题意：从下往上给定 n 块积木上的数 a_1..a_n，
// 可删除任意块积木使上方积木下落，
// 得到序列 b_1..b_m 的价值为 sum [b_i = i]
// 求最大价值。
// 数据范围：1 <= n <= 10^5，1 <= a_i <= 10^6。
// 算法标签：动态规划、树状数组、排序
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int tree[MAXN];
struct node{
    int val,sub;
}nums[MAXN];

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
    return ((a.val-a.sub)==(b.val-b.sub))?(a.sub<b.sub):((a.val-a.sub)>(b.val-b.sub));
}

int lowbit(int x){
    return x&(-x);
}

int query(int x){
    int ans=0;
    while(x){
        ans=max(tree[x],ans);
        x-=lowbit(x);
    }
    return ans;
}

void update(int x,int val){
    while(x<=n){
        tree[x]=max(tree[x],val);
        x+=lowbit(x);
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i].val=read();
        nums[i].sub=i;
    }
    sort(nums+1,nums+n+1,cmp);
    int ans=0;
    for(int i=1;i<=n;i++){
        if(nums[i].sub-nums[i].val<0)
            continue;
        int val=query(nums[i].val-1)+1;
        update(nums[i].val,val);
        ans=max(ans,val);
    }
    cout<<ans<<endl;
    return 0;
}
