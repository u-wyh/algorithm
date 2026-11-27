// https://www.luogu.com.cn/problem/P2347
// 题意：给出 1g、2g、3g、5g、10g、20g 砝码的各自数量。
// 求用这些砝码能称出的不同正整数重量个数。
// 按 Total=N 格式输出。
// 数据范围：所有砝码总重 <= 1000。
#include<bits/stdc++.h>
// 算法标签：生成函数、动态规划
using namespace std;

int a[7];
int b[7]={0,1,2,3,5,10,20};
int ans;
int m;
int c[1005];
int d[1005];

void compute(){
    for(int i=0;i<=a[1];i++){
        c[i]=1;
        m=a[1];
    }
    for(int i=2;i<=6;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=b[i]*a[i];k+=b[i]){
                d[j+k]+=c[j];
            }
        }
        m+=b[i]*a[i];
        for(int j=0;j<=m;j++){
            c[j]=d[j];
            d[j]=0;
        }
    }
    for(int i=1;i<=m;i++){
        if(c[i]){
            ans++;
        }
    }
}

int main()
{
    for(int i=1;i<=6;i++){
        cin>>a[i];
    }
    compute();
    cout<<"Total="<<ans<<endl;
    return 0;
}