// https://www.luogu.com.cn/problem/P5542
// 题意：在二维平面上画了 n 个边平行坐标轴的矩形（每画一个涂一层油漆），求最终恰好被覆盖 K 层的区域总面积。
// 输入 n, K 及每个矩形的左下角与右上角整数坐标；输出被涂 K 层的面积。
// 数据范围：1 <= K <= n <= 10^5，0 <= x1 < x2 <= 1000，0 <= y1 < y2 <= 1000。
#include<bits/stdc++.h>
// 算法标签：二维差分、二维前缀和
using namespace std;

int nums[1005][1005];
int n,k;
int ans=0;

int main()
{
    cin>>n>>k;
    for(int i=1,a,b,c,d;i<=n;i++){
        cin>>a>>b>>c>>d;
        nums[a+1][b+1]+=1;
        nums[c+1][d+1]+=1;
        nums[a+1][d+1]-=1;
        nums[c+1][b+1]-=1;
    }
    for(int i=1;i<=1000;i++){
        for(int j=1;j<=1000;j++){
            nums[i][j]+=nums[i-1][j]+nums[i][j-1]-nums[i-1][j-1];
        }
    }
    for(int i=1;i<=1000;i++){
        for(int j=1;j<=1000;j++){
            if(nums[i][j]==k){
                ans++;
            }
        }
    }
    cout<<ans;
    return 0;
}
