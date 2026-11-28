// https://www.luogu.com.cn/problem/B3626
// 题意：机器人从 1 号格出发，目标是 n 号格。
// 在 x 时可以跳到 x-1、x+1 或 2x，所有落点都要在 1 到 n 内。
// 输出最少跳跃次数。
// 数据范围：1 ≤ n ≤ 10^6。
// 难度评分：1000（洛谷分级换算）
// 算法标签：广度优先搜索

#include<bits/stdc++.h>

using namespace std;

#define MAX 1000000+5

queue<int>Q;
int d[MAX];
int n;

int main()
{
    scanf("%d",&n);
    Q.push(1);
    d[1]=0;
    while(!Q.empty()){
        int tmp=Q.front();
        Q.pop();
        if(tmp==n){
            printf("%d\n",d[tmp]);
            return 0;
        }
        for(int i=1;i<=3;i++){
            int k;
            if(i==1) k=-1;
            if(i==2) k=1;
            if(i==3) k=tmp;
            int x=tmp+k;
            if(x<=1||x>n||d[x]!=0){
                continue;
            }
            Q.push(x);
            d[x]=d[tmp]+1;
        }
    }
    return 0;
}
