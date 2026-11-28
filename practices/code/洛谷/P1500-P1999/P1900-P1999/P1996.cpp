// https://www.luogu.com.cn/problem/P1996
// 题意：n 人按编号围成一圈，从第 1 人开始报数。
// 报到 m 的人出圈，再从他的下一人从 1 报起。输出所有人的出圈顺序。
// 数据范围：1 ≤ n,m ≤ 100。
// 难度评分：900（洛谷分级换算）
// 算法标签：模拟

#include<queue>
#include<iostream>

using namespace std;

int n,k;
queue<int>q;

void work(){
    int i;
    for(int i=1;i<=n;i++)
        q.push(i);
    while(q.size()){
        for(int i=1;i<k;i++){
            q.push(q.front());
            q.pop();
        }
        printf("%d ",q.front());
        q.pop();
    }
}

int main(){
    cin>>n>>k;
    work();
    return 0;
}
