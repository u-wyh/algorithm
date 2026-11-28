// https://www.luogu.com.cn/problem/P6503
// 题意：给出长度为 n 的序列 a，求所有连续子序列的最大值与最小值之差的和
// 即 sum_{i=1}^n sum_{j=i}^n
// (max_{i<=k<=j} a_k - min_{i<=k<=j} a_k)。
// 数据范围：2 <= n <= 3*10^5，1 <= a_i <= 10^8。
// 难度评分：1300（洛谷分级换算）
// 算法标签：单调栈、贡献法
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;  // 使用 ll 作为 long long 的别名
const ll MN = 3e5 + 5;

ll nums[MN];
ll Lmax[MN], Rmax[MN], Lmin[MN], Rmin[MN];
ll n,ans=0;
ll st[MN];
int cur;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>nums[i];
    int r=0;
    for(int i=1;i<=n;i++){
        while(r>0&&nums[st[r-1]]<nums[i]){
            cur=st[--r];
            Rmax[cur]=i;
            Lmax[cur]=r<=0?0:st[r-1];
        }
        st[r++]=i;
    }
    while(r>0){
        cur=st[--r];
        Rmax[cur]=n+1;
        Lmax[cur]=r>0?st[r-1]:0;
    }

    r=0;
    for(int i=1;i<=n;i++){
        while(r>0&&nums[st[r-1]]>nums[i]){
            cur=st[--r];
            Rmin[cur]=i;
            Lmin[cur]=r<=0?0:st[r-1];
        }
        st[r++]=i;
    }
    while(r>0){
        cur=st[--r];
        Rmin[cur]=n+1;
        Lmin[cur]=r>0?st[r-1]:0;
    }

    /*
    for(int i=1;i<=n;i++)
        printf("%3d",Rmax[i]);
    printf("\n");
    for(int i=1;i<=n;i++)
        printf("%3d",Lmax[i]);
    printf("\n");
    for(int i=1;i<=n;i++)
        printf("%3d",Rmin[i]);
    printf("\n");
    for(int i=1;i<=n;i++)
        printf("%3d",Lmin[i]);
    printf("\n");
    */

    for(int i=1;i<=n;i++){
        ans+=nums[i]*(i-Lmax[i])*(Rmax[i]-i);
        ans-=nums[i]*(i-Lmin[i])*(Rmin[i]-i);
    }
    cout<<ans<<endl;

    return 0;
}
