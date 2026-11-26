// https://www.luogu.com.cn/problem/P5486
// 题意：多组数据，已知 M 天内 N 间公寓每天的空闲状态，求从第 s 天晚住到第 t+1 天中午（即第 s..t 天）最少换房次数且字典序最小的安排方案。
// 输入 M, N、公寓每日状态矩阵及 s, t（M=N=0 结束）；按格式输出方案编号与每段居住区间，无解输出 Not available。
// 数据范围：M <= 100，N <= 26，1 <= s < t <= M+1。
#include<bits/stdc++.h>
using namespace std;
const int MAXM = 101;
const int MAXN = 27;

int n,m;
int st,en;
int arr[MAXM][MAXN];

int main()
{
    int flag=0;
    while(cin>>m>>n){
        if(flag){
            cout<<endl;
        }
        flag++;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                char c;
                arr[i][j]= c=='O';
            }
        }
        cin>>st>>en;
        en--;
    }
    return 0;
}