// 满足不等式的最大值
// 给你一个数组 points 和一个整数 k
// 数组中每个元素都表示二维平面上的点的坐标，并按照横坐标 x 的值从小到大排序
// 也就是说 points[i] = [xi, yi]
// 并且在 1 <= i < j <= points.length 的前提下，xi < xj 总成立
// 请你找出 yi + yj + |xi - xj| 的 最大值，
// 其中 |xi - xj| <= k 且 1 <= i < j <= points.length
// 题目测试数据保证至少存在一对能够满足 |xi - xj| <= k 的点。
// 测试链接 : https://leetcode.cn/problems/max-value-of-equation/
#include<bits/stdc++.h>
using namespace std;

struct node{
    int x,y;
}nums[10005];
int n,k;
int q[10005],h,t;

int main()
{
    cin>>n>>k;
    for(int i=0;i<n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    int ans=-1e9;
    for(int i=0;i<n;i++){
        while(h<t&&nums[i].x-nums[q[h]].x>k){
            h++;
        }
        if(h<t){
            ans=max(ans,nums[i].x+nums[i].y+nums[q[h]].y-nums[q[h]].x);
        }
        while(h<t&&nums[q[t]].y-nums[q[t]].x<=nums[i].y-nums[i].x){
            //每次根据y-x的值判断位置  因为每次计算结果的时候就是 x+y+(头位置的y-x)
            t--;
        }
        q[t++]=i;
    }
    cout<<ans;
    return 0;
}