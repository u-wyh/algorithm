// https://www.luogu.com.cn/problem/P2032
// 题意：给定 n 个整数，长度为 k 的窗口从左向右每次移动一格。按顺序输出每个窗口的最大值。
// 数据范围：1 ≤ k ≤ n ≤ 2×10^6，元素为不超过 10^4 的正整数。

#include<bits/stdc++.h>
using namespace std;

int a[1000010],q[1000010];
int n,k;

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    int head=0,tail=0;
    for(int i=1;i<=n;i++){
        while(head<tail&&q[head]+k<=i){
            head++;
        }
        while(head<tail&&a[q[tail-1]]<a[i]){
            tail--;
        }
        q[tail]=i;
        tail++;
        if(i>=k)
            cout<<a[q[head]]<<endl;
    }
    return 0;
}

