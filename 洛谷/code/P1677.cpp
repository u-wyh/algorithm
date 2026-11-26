// https://www.luogu.com.cn/problem/P1677
// 题意：给出直线上 N 头牛的位置。每头牛拿到球就传给最近的另一头牛，等距时传给位置更靠左的牛。求至少给几头牛发球，才能让每头牛都接到过球。
// 数据范围：1 ≤ N ≤ 100，1 ≤ x_i ≤ 1000，位置互不相同。

#include<bits/stdc++.h>
using namespace std;
#define MAX 105

int n;
int nums[MAX];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    sort(nums+1,nums+n+1);

    return 0;
}
