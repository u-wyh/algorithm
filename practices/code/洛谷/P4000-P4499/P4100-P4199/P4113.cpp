// https://www.luogu.com.cn/problem/P4113
// 题意：第一行输入花朵数 n、颜色数 c、行程数 m；
// 第二行输入每朵花的颜色 x_1..x_n；
// 接下来 m 行每行输入区间 [l, r]。
// 统计区间 [l, r] 中出现次数至少为 2 次的不同颜色有多少种。
// 输出 m 行，每行一个整数表示对应行程的答案。
// 数据范围：
// Subtask 1 保证 1 <= n, c, m <= 3*10^5；
// Subtask 2 保证 1 <= n, c, m <= 2*10^6；
// 1 <= x_i <= c，1 <= l <= r <= n。
// 算法标签：树状数组、离线算法、扫描线
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;

int last1[MAXN];
int last2[MAXN];
int n,c,m;
int arr[MAXN];
struct node{
    int l,r,sub;
}nums[MAXN];
int ans[MAXN];
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

inline int lowbit(int i) {
    return i & -i;
}

void add(int i, int v) {
    while (i <= n) {
        tree[i] += v;
        i += lowbit(i);
    }
}

int sum(int i) {
    int ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

int main()
{
    n=read(),c=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    for(int i=1;i<=m;i++){
        nums[i].l=read(),nums[i].r=read();
        nums[i].sub=i;
    }
    sort(nums+1,nums+m+1,cmp);
    int j=1;
    for(int i=1;i<=m;i++){
        for(;j<=nums[i].r;j++){
            if(!last1[arr[j]]){
                last1[arr[j]]=j;
            }
            else if(!last2[arr[j]]){
                add(last1[arr[j]],1);
                last2[arr[j]]=j;
            }
            else{
                add(last2[arr[j]],1);
                add(last1[arr[j]],-1);
                last1[arr[j]]=last2[arr[j]];
                last2[arr[j]]=j;
            }
        }
        ans[nums[i].sub]=sum(nums[i].r)-sum(nums[i].l-1);
    }
    for(int i=1;i<=m;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}
