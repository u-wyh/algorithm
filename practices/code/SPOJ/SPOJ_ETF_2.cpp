// https://www.spoj.com/problems/ETF/
// 题意：T 组数据，每组给正整数 n。
// 输出：每组输出 1..n 中与 n 互质的整数个数。
// 数据范围：T <= 20000，1 <= n <= 10^6。
// 难度评分：1300（估算）
// 算法标签：欧拉筛、欧拉函数
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int phi[MAXN];
int pri[MAXN];
int len;
bool vis[MAXN];

void prepare(int n){
    phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            phi[i]=i-1;
            pri[++len]=i;
        }
        for(int j=1;j<=len&&(i*pri[j]<=n);j++){
            vis[i*pri[j]]=true;
            if(i%pri[j]==0){
                phi[i*pri[j]]=phi[i]*pri[j];
                break;
            }
            else{
                phi[i*pri[j]]=phi[i]*(pri[j]-1);
            }
        }
    }
}

int main()
{
    prepare(1000000);
    int T;
    cin>>T;
    while(T--){
        int x;
        cin>>x;
        cout<<phi[x]<<endl;
    }
    return 0;
}