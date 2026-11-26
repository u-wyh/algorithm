// https://www.luogu.com.cn/problem/P5026
// 题意：长为 m 的直线初始水位全为 0
// 进行 n 次操作 (v, x)：按题面给定的分段等差增减规则叠加改变 x-3v+1 到 x+3v-1 区间的水位（在 x 处降 2v、x±2v 处升 2v、x±v 处不变）
// 求最终 1..m 每个位置的水位。
// 数据范围：n <= 10^6，1 <= x <= m <= 10^6，1 <= v <= 10000。
#include<bits/stdc++.h>
using namespace std;

const int offset=30005;

int n,m;
int v,x;
int arr[1030005];

void Set(int l,int r,int s,int e,int d){
    arr[l+offset]+=s;
    arr[l+1+offset]+=(d-s);
    arr[r+1+offset]-=(d+e);
    arr[r+2+offset]+=e;
}

void build(){
    for(int i=1;i<=n+offset;i++){
        arr[i]+=arr[i-1];
    }
    for(int i=1;i<=n+offset;i++){
        arr[i]+=arr[i-1];
    }
}

void fall(int v,int x){
    Set(x-3*v+1,x-2*v,1,v,1);
    Set(x-2*v+1,x,v-1,-v,-1);
    Set(x+1,x+2*v,-v+1,v,1);
    Set(x+2*v+1,x+3*v-1,v-1,1,-1);
}

int main()
{
    cin>>m>>n;
    while(m--){
        cin>>v>>x;
        fall(v,x);
    }
    build();
    for(int i=1;i<=n;i++){
        printf("%d ",arr[i+offset]);
    }
    return 0;
}
