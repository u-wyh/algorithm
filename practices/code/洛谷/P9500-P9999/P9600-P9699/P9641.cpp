// https://www.luogu.com.cn/problem/P9641
// 题意：多组数据（共 T 组）。
// 给定 n * m 网格，每格有方向字符（u/d/l/r）和步长 a_{i,j}。
// 任选起点并标记，之后不断按当前格方向移动 a_{i,j} 步到达新格并标记；
// 若目标格越界或已标记则结束。
// 判断是否存在起点能恰好标记全部 n * m 个格子各一次。
// 题意：第一行输入 T，
// 每组输入 n, m、n 行方向字符矩阵、n 行整数矩阵 a_{i,j}；
// 输出 Yes 或 No。
// 数据范围：1 <= n * m <= 10^5，
// 1 <= a_{i,j} <= max(n, m)
// sum(n * m) <= 10^6
// （未显式给出 T 上界，受 sum(n * m) 限制）。
// 难度评分：1300（洛谷分级换算）
// 算法标签：模拟、计数统计
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int nums[MAXN];
char str[MAXN];
int vis[MAXN];

int main()
{
    int t;
    cin>>t;
    while(t--){
        cin>>n>>m;
        for(int i=0;i<m*n;i++){
            cin>>str[i];
        }
        for(int i=0;i<m*n;i++){
            cin>>nums[i];
        }
        for(int i=0;i<m*n;i++){

            int x=i/m,y=i%m;
            if(str[i]=='u'){
                if(x-nums[i]>=0){
                    vis[i-nums[i]*m]++;
                }
            }
            if(str[i]=='d'){
                if(x+nums[i]<n){
                    vis[i+x*nums[i]]++;
                }
            }
            if(str[i]=='l'){
                if(y-nums[i]>=0){
                    vis[i-nums[i]]++;
                }
            }
            if(str[i]=='r'){
                if(y+nums[i]<m){
                    vis[i+nums[i]]++;
                }
            }
        }
        int cnt0=0,cnt2=0,f=0;
        for(int i=0;i<m*n;i++){
            if(vis[i]==0){
                cnt0++;
            }
            if(vis[i]==2){
                cnt2++;
            }
            if(vis[i]>=3){
                f=1;
                break;
            }
        }
        if(f){
            cout<<"No\n";
        }
        else{
            if((cnt0==0&&cnt2==0)||(cnt0==1&&cnt2==1)||(cnt0==1&&cnt2==0))
                cout<<"Yes\n";
            else
                cout<<"No\n";
        }

        for(int i=0;i<m*n;i++){
            nums[i]=0;
            str[i]=' ';
            vis[i]=0;
        }
    }
    return 0;
}
