// https://www.luogu.com.cn/problem/P2158
// 题意：N*N 方阵，站在左下角 (0,0) 向方阵内看，求能看到的学生人数。
// 输出能看到的学生人数。
// 数据范围：1 <= N <= 40000。
// 难度评分：1800（洛谷分级换算）
// 算法标签：线性筛、欧拉函数
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e4+5;

int n;
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
            }
            else{
                phi[i*pri[j]]=phi[i]*(pri[j]-1);
            }
        }
    }
}

int main()
{
    cin>>n;
    if(n==1){
        cout<<0<<endl;
        return 0;
    }
    prepare(n);
    long long ans=1;
    for(int i=1;i<n;i++){
        ans+=phi[i];
    }
    ans*=2;
    ans--;
    cout<<ans<<endl;
    return 0;
}