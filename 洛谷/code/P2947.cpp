// https://www.luogu.com.cn/problem/P2947
// 题意：输入奶牛数量 N，以及站成一排的每头奶牛的身高 H_i。
// 每头奶牛 i 向右看，她离自己最近的仰望对象是满足 j > i 且 H_j > H_i 的最小下标 j。
// 对每头奶牛求其最近仰望对象的编号；若右侧没有比她更高的奶牛，则记为 0。
// 输出共 N 行，每行一个整数，依次为第 1 到第 N 头奶牛的最近仰望对象编号。
// 数据范围：对于 100% 的数据，1 <= N <= 10^5，1 <= H_i <= 10^6。
#include<bits/stdc++.h>
// 算法标签：单调栈
using namespace std;

int n;
int nums[100005],st[100005],R[100005];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>nums[i];
    int cur,r=0;
    for(int i=1;i<=n;i++){
        while(r>0&&nums[st[r-1]]<nums[i]){
            cur=st[--r];
            R[cur]=i;
        }
        st[r++]=i;
    }

    while (r > 0) {
        cur = st[--r];
        R[cur] = 0;
    }

    for(int i=1;i<=n;i++)
        cout<<R[i]<<endl;
    return 0;
}
