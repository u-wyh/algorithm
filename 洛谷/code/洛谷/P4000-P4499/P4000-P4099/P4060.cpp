// https://www.luogu.com.cn/problem/P4060
// 题意：第一行输入原始非负整数序列长度 n 和剩余已知元素个数 m，
// 接下来 m 行每行输入已知元素的下标 i 和数值 a_i。
// 序列 b 为 a 的异
// 或前缀和（b_1 = a_1，
// b_i = b_{i-1} xor a_i (i >= 2)）；
// 未知位置可取任意非负整数（可超过已知 a_i 上界），
// 求所有可能 a 序列对应的 b 序列总和 sum_{i=1}^n b_i
// 的最小值。
// 输出可能的最小总和。
// 数据范围：对于全部测试点，1 <= n <= 10^9，
// 0 <= m <= min{n, 10^5}，
// 已知 0 <= a_i <= 10^9
// 保证所有输入下标 i 互不相同
// 且 1 <= i <= n（未知 a_i 可超过已知 a_i 的范围）。
// 算法标签：贪心、位运算、排序
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXM = 1e5+5;

int n,m;
struct node{
    int pos,val;
}nums[MAXM];

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
    return a.pos<b.pos;
}

int compute(int l,int r){
    int res=0,ans=0;
    if(nums[l].pos==1){
        for(int i=l;i<=r;i++){
            ans^=nums[i].val;
            res+=ans;
        }
    }
    else{
        for(int i=30;i>=0;i--){
            int cnt[2],tot[2];
            cnt[0]=tot[0]=0;
            cnt[1]=tot[1]=1;
            for(int j=0;j<=1;j++){
                for(int k=l;k<=r;k++){
                    tot[j]^=(nums[k].val>>i)&1;
                    cnt[j]+=tot[j];
                }
            }
            res+=(1<<i)*min(cnt[0],cnt[1]);
        }
    }
    return res;
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        nums[i].pos=read();
        nums[i].val=read();
    }
    sort(nums+1,nums+m+1,cmp);
    int now=1;
    int ans=0;
    while(now<=m){
        int lst=now;
        while(now<=m&&nums[now].pos==nums[now+1].pos-1){
            now++;
        }
        ans+=compute(lst,now);
        now++;
    }
    cout<<ans<<endl;
    return 0;
}
