// 子数组的最小值之和
// 给定一个整数数组 arr，找到 min(b) 的总和，其中 b 的范围为 arr 的每个（连续）子数组。
// 由于答案可能很大，答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/sum-of-subarray-minimums/
#include<bits/stdc++.h>
using namespace std;

const int MOD = 100000007;
int n;
int st[10000];
int arr[10000];

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>arr[i];

    long ans = 0;
    int r = 0;
    for (int i = 0; i < n; i++) {
        while (r > 0 && arr[st[r - 1]] >= arr[i]) {
            //严格大压小
            int cur = st[--r];
            int left = r == 0 ? -1 : st[r - 1];
            ans = (ans + (long) (cur - left) * (i - cur) * arr[cur]) % MOD;
        }
        st[r++] = i;
    }
    while (r > 0) {
        int cur = st[--r];
        int left = r == 0 ? -1 : st[r - 1];
        ans = (ans + (long) (cur - left) * (n - cur) * arr[cur]) % MOD;
    }
    cout<<ans;
    return 0;
}