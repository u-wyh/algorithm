// https://www.luogu.com.cn/problem/P1858
// 题意：K 个人各有容量 V 的背包。给定 N 种物品的体积和价值，每人同种最多选一件，必须恰好装满，且任意两人的物品集合不同。求所有背包的最大总价值。
// 数据范围：K ≤ 50，V ≤ 5000，N ≤ 200。

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXV = 5005;
const int MAXK = 55;

int m,v,n;
int f[MAXV][MAXK];
int tmp[MAXK];
int val[MAXN],cost[MAXN];

int main()
{
    cin>>m>>v>>n;
    memset(f,128,sizeof(f));//初始化为比较小值
    for(int i=1;i<=n;i++){
        cin>>cost[i]>>val[i];
    }
    f[0][1]=0;
    for(int i=1;i<=n;i++){
        for(int j=v;j>=cost[i];j--){
            int t1=1,t2=1,len=0;
            while(t1+t2<=m+1){
                if (f[j][t1]>f[j-cost[i]][t2]+val[i])
                    tmp[++len]=f[j][t1++];
                else
                    tmp[++len]=f[j-cost[i]][t2++]+val[i];
            }
            for(int k=1;k<=m;k++){
                f[j][k]=tmp[k];
            }
        }
    }
    int ans=0;
    for(int i=1;i<=m;i++){
        ans+=f[v][i];
    }
    cout<<ans<<endl;
    return 0;
}
