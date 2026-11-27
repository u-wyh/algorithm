// https://www.luogu.com.cn/problem/P2215
// 题意：给定长度为 N 的序列，M 次询问长度为 L 的严格上升子序列。
// 求下标序列字典序最小的那个，不存在输出 Impossible。
// 每组询问输出一行序列或 Impossible。
// 数据范围：N <= 10000，M <= 1000，保证数据随机。
// 算法标签：动态规划（LIS）、贪心
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;

int n,m,k;
int arr[MAXN];
int dp[MAXN];

void compute(){
    int u=1;
    while(dp[u]<k){
        u++;
    }
    int maxlen=k;
    int last=INT_MIN;
    for(int i=1;i<=k;i++){
        while(dp[u]<k-i+1||arr[u]<=last){
            u++;
        }
        cout<<arr[u]<<' ';
        last=arr[u];
        u++;
    }
    cout<<endl;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    int maxlen=0;
    for(int i=n;i>=1;i--){
        for(int j=i+1;j<=n;j++){
            if(arr[i]<arr[j]){
                dp[i]=max(dp[i],dp[j]);
            }
        }
        dp[i]+=1;
        maxlen=max(maxlen,dp[i]);
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>k;
        if(k>maxlen){
            cout<<"Impossible"<<endl;
        }
        else{
            compute();
        }
    }
    return 0;
}
