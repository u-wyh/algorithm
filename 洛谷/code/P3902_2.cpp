// https://www.luogu.com.cn/problem/P3902
// 题意：给定长度为 n 的整数序列 A_1..A_n，每次修改可以将序列中某个数改成任意实数。
// 求最少修改多少个数字，使得整个序列严格单调递增。
// 数据范围：1 <= n <= 10^5，1 <= A_i <= 10^9。
#include<bits/stdc++.h>
// 算法标签：最长上升子序列、二分查找
using namespace std;
const int MAXN = 10005;

int n;
int nums[MAXN];

int bs1(int* ends, int len, int num) {
    int l = 0, r = len - 1, m, ans = -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (ends[m] >= num) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}
int lengthOfLIS2(int* nums,int n) {
    int ends [n];
    // len表示ends数组目前的有效区长度
    // ends[0...len-1]是有效区，有效区内的数字一定严格升序
    int len = 0;
    for (int i = 0, find; i < n; i++) {
        find = bs1(ends, len, nums[i]);
        if (find == -1) {
            ends[len++] = nums[i];
        } else {
            ends[find] = nums[i];
        }
    }
    return len;
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    cout<<n-lengthOfLIS2(nums,n);
    return 0;
}
