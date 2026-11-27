// https://www.luogu.com.cn/problem/P3467
// 题意：输入自西向东紧挨着排成一排的建筑数量 n，以及每栋建筑的宽度 d_i 和高度 w_i。
// 用若干条边平行于坐标轴、互不重叠（允许边缘相接）且不能超出墙面的矩形海报，完全覆盖所有建筑的北立面。
// 输出一个整数，表示最少需要多少张矩形海报。
// 数据范围：1 <= n <= 2.5*10^5，1 <= d_i, w_i <= 10^9。
#include<bits/stdc++.h>
// 算法标签：单调栈
using namespace std;
int n,ans,y,r;
int st[250005],nums[250005];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>y>>nums[i];
    }
    int ans=n;
    for(int i=1;i<=n;i++){
        while(r>0&&nums[st[r-1]]>=nums[i]){
            if(nums[i]==nums[st[r-1]])
                ans--;
            r--;
        }
        st[r++]=i;
    }
    cout<<ans;
    return 0;
}

