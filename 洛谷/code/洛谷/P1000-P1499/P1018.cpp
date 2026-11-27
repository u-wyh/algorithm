// https://www.luogu.com.cn/problem/P1018
// 题意：给一个长度为 n 的数字串，要在相邻数字之间恰好插入 k 个乘号。
// 保持数字的原顺序，把切出的 k + 1 段各当作一个整数，
// 输出这些整数乘积的最大值。
// 数据范围：6 ≤ n ≤ 40，1 ≤ k ≤ 6，k < n。
// 算法标签：深度优先搜索

#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,mul,maxx;
int arr[45];

void dfs(int x,int ans,int last){
    if(x==m){
        mul=0;
        for(int j=last+1;j<n;j++){
            mul+=arr[j];
            mul*=10;
        }
        mul+=arr[n];
        maxx=max(maxx,ans*mul);
        return;
    }
    for(int i=last+1;i<=n-m+x;i++){
        mul=0;
        for(int j=last+1;j<i;j++){
            mul+=arr[j];
            mul*=10;
        }
        mul+=arr[i];
        dfs(x+1,ans*mul,i);
    }
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        char c;
        cin>>c;
        arr[i]=c-'0';
    }
    dfs(0,1,0);
    cout<<maxx<<endl;
    return 0;
}
