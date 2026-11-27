// https://www.luogu.com.cn/problem/P1204
// 题意：给定 n 个农民各自的挤奶起止时间区间 [l, r]（单位秒）。
// 题意：求从有人开始挤奶到全部结束期间，
// 最长至少一人在挤奶和最长无人挤奶的连续时长。
// 输入：第一行输入正整数 n，接下来 n 行每行输入两个非负整数 l, r。
// 输出：一行输出两个整数（空格隔开），依次为最长有人挤奶时长和最长无人挤奶时长。
// 数据范围：1 <= n <= 5000。
// 数据范围：0 <= l <= r <= 10^6。
// 算法标签：排序、区间合并
#include<bits/stdc++.h>
using namespace std;

struct range{
    int L,R;
}nums[5005];
int n,ans1=0,ans2=0;

bool cmp(const range a,const range b){
    return a.L < b.L;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].L>>nums[i].R;
    }
    sort(nums+1,nums+n+1,cmp);
    int l=nums[1].L,r=nums[1].R,ans1=nums[1].R-nums[1].L;
    for(int i=2;i<=n;i++){
        if(nums[i].L<=r){
            r=max(r,nums[i].R);
        }else{
            ans1=max(ans1,r-l);
            ans2=max(ans2,nums[i].L-r);
            l=nums[i].L;
            r=nums[i].R;
        }
    }
    cout<<ans1<<' '<<ans2;
    return 0;
}
