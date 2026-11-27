// https://www.luogu.com.cn/problem/P1725
// 题意：从 0 号格子出发，每次向右跳 L 到 R 格，落在编号大于 N 的位置就结束。每次落在河中的格子 i 得到 A_i，求过河能获得的最大总和。
// 数据范围：1 ≤ L ≤ R ≤ N ≤ 2×10^5，A_0=0，−1000 ≤ A_i ≤ 1000，答案 ≤ 2^31−1。
// 算法标签：动态规划、单调队列

#include<bits/stdc++.h>
using namespace std;
#define MAX 200005

int n,L,R;
int a[MAX],f[MAX];
int h=0,t=0,ans=-2e9;
int q[MAX];

int main()
{
    cin>>n>>L>>R;
    for(int i=0;i<=n;i++){
        cin>>a[i];
        if(L==R&&i%L==0)
            ans+=a[i];
    }
    if(L==R)
    {
        cout<<ans+2e9<<endl;
        return 0;
    }
    for(int j=L;j<=n;j++){
        int i=j-L;
        while(h<t&&f[q[t]]<=f[i]){
            t--;
        }
        q[t++]=i;
        while(h<t&&i-q[h]>R){
            h++;
        }
        f[i]=a[i]+f[q[h]];
        if(i+R>n)
            ans=max(f[i],ans);
    }
    cout<<ans<<endl;
    return 0;
}
