// https://www.luogu.com.cn/problem/P10506
// 题意：给 n 堆珠子，两人轮流选一堆数量 p 大于 1 的珠子，把它换成大小各为 p 的一个真约数的若干堆，再删去其中一堆。
// 无法行动者输，双方最优时输出先手 freda 或后手 rainbow。
// 数据范围：多组数据读到 EOF，1 ≤ n ≤ 100，1 ≤ a[i] ≤ 1000。

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n;
int sg[MAXN];
bool appear[MAXN];

void build(){
    sg[1]=0;
    for (int i = 2; i <= 1000; i++) {
        int k=0;
        memset(appear, false, sizeof(appear)); // 重置 appear 数组
        for (int j = 1; j <= i/2; j++) {
            if(i%j==0){
                k^=sg[j];
            }
        }
        for (int j = 1; j <= i/2; j++) {
            if(i%j==0){
                appear[k^sg[j]]=1;
            }
        }
        for (int s = 0; s < MAXN; s++) {
            if (!appear[s]) {
                sg[i] = s; // 找到最小的未出现的 SG 值
                break;
            }
        }
        //cout<<i<<": "<<sg[i]<<endl;
    }
}

int main()
{
    build();
    while(cin>>n){
        int ans=0;
        for(int i=1;i<=n;i++){
            int u;
            cin>>u;
            ans^=sg[u];
        }
        if(ans){
            cout<<"freda"<<endl;
        }
        else{
            cout<<"rainbow"<<endl;
        }
    }
    return 0;
}
