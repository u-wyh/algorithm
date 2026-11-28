// https://www.luogu.com.cn/problem/B3611
// 题意：给 n 个点的有向图，用 n × n 的 0/1 矩阵记录每条直接边。
// 输出另一个矩阵，若 i 可以沿边到达 j，则对应位置为 1，否则为 0。
// 数据范围：1 ≤ n ≤ 100，输入矩阵对角线为 0。
// 难度评分：1300（洛谷分级换算）
// 算法标签：Floyd、传递闭包

#include<bits/stdc++.h>
using namespace std;

int n;
int dis[105][105];

void floyd() {
    // O(N^3)的过程
    // 枚举每个跳板
    // 注意，跳板要最先枚举！跳板要最先枚举！跳板要最先枚举！
    for (int bridge = 1; bridge <= n; bridge++) { // 跳板
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dis[i][j] == 0&&dis[i][bridge] != 0&& dis[bridge][j] != 0) {
                    dis[i][j] = 1;
                }
            }
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>dis[i][j];
        }
    }
    floyd();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<dis[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}
