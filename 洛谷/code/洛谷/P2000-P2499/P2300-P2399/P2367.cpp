// https://www.luogu.com.cn/problem/P2367
// 题意：n 名学生各有初始成绩，共 p 次操作，
// 每次给闭区间 [x,y] 的学生加 z 分。
// 求所有操作完成后全班的最低分。
// 输出最低分。
// 数据范围：n <= 5*10^6，p <= n，
// 初始成绩 <= 100，z <= 100。
// 算法标签：差分、前缀和
#include<bits/stdc++.h>
using namespace std;

int n,m;
int nums[5000005],d[5000005],minans=1e5;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        d[i]=nums[i]-nums[i-1];
    }
    while(m--){
        int l,r,z;
        cin>>l>>r>>z;
        d[l]+=z;
        d[r+1]-=z;
    }
    for(int i=1;i<=n;i++){
        d[i]+=d[i-1];
        minans=min(minans,d[i]);
    }
    cout<<minans;
    return 0;
}
