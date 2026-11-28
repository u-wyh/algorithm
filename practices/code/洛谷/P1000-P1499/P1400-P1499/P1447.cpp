// https://www.luogu.com.cn/problem/P1447
// 题意：植物位于所有整数坐标 (x,y)，
// 其中 x 从 1 到 n、y 从 1 到 m。
// 对每株植物，数它到原点的线段内部还有几株，若有 k 株则损失 2k+1。
// 输出每株损失之和。
// 数据范围：1 ≤ n,m ≤ 10^5。
// 难度评分：1800（洛谷分级换算）
// 算法标签：欧拉函数、线性筛

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

int main(){
    int n,m;
    cin>>n>>m;
    if(n<m){
        swap(n,m);
    }
    prepare(n);
    long long ans=-1ll*n*m;
    for(int d=1;d<=m;d++){
        ans+=2ll*phi[d]*(n/d)*(m/d);
    }
    cout<<ans<<endl;
    return 0;
}