// 柱状图中最大的矩形
// 给定 n 个非负整数，用来表示柱状图中各个柱子的高度
// 每个柱子彼此相邻，且宽度为 1 。求在该柱状图中，能够勾勒出来的矩形的最大面积
// 测试链接：https://leetcode.cn/problems/largest-rectangle-in-histogram
#include<bits/stdc++.h>
using namespace std;

int st[10000];
int n,r=0;
int nums[10000],L;
int ans=0;

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>nums[i];
    int cur;
    for(int i=0;i<n;i++){
        while(r>0&&nums[st[r-1]]>=nums[i]){
            cur=st[--r];
            L=r>0?st[r-1]:-1;
            ans=max(ans,nums[cur]*(i-1-L));
            //统计以自己作为最低时的面积 即左边和右边小于自己的之间为长度
            //这里需要注意 由于下标是从0开始的  所以可以最左侧无法到达的话就是-1
        }
        st[r++]=i;
    }

    while (r > 0) {
        cur = st[--r];
        L = r > 0 ? st[r - 1] : -1;
        ans=max(ans,nums[cur]*(n-1-L));
    }

    cout<<ans<<endl;
    return 0;
}