// 用邮票贴满网格图
// 给你一个 m * n 的二进制矩阵 grid
// 每个格子要么为 0 （空）要么为 1 （被占据）
// 给你邮票的尺寸为 stampHeight * stampWidth
// 我们想将邮票贴进二进制矩阵中，且满足以下 限制 和 要求 ：
// 覆盖所有空格子，不覆盖任何被占据的格子
// 可以放入任意数目的邮票，邮票可以相互有重叠部分
// 邮票不允许旋转，邮票必须完全在矩阵内
// 如果在满足上述要求的前提下，可以放入邮票，请返回 true ，否则返回 false
// 测试链接 : https://leetcode.cn/problems/stamping-the-grid/
//这道题的思路是将所有可以贴的位置全部贴上 然后统计是不是所有的地方都被贴上了
#include<bits/stdc++.h>
using namespace std;

int m,n,h,w;
int arr[100][100],sum[100][100],nums[100][100];

int fun(int X1,int Y1,int X2,int Y2){
    return sum[X2][Y2]+sum[X1-1][Y1-1]-sum[X2][Y1-1]-sum[X1-1][Y2];
}

void Set(int a,int b,int c,int d,int v){
    nums[a][b]+=v;
    nums[a][d+1]-=v;
    nums[c+1][b]-=v;
    nums[c+1][d+1]+=v;
}

int main()
{
    cin>>n>>m>>h>>w;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>arr[i][j];
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+arr[i][j];
        }
    }

    for (int a = 1, c = a + h - 1; c <= n; a++, c++) {
        for (int b = 1, d = b + w - 1; d <= m; b++, d++) {
            // 原始矩阵中 (a,b)左上角点
            // 根据邮票规格，h、w，算出右下角点(c,d)
            // 这个区域彻底都是0，那么:
            // sumRegion(sum, a, b, c, d) == 0
            // 那么此时这个区域可以贴邮票
            if (fun(a,b,c,d)== 0) {
                Set(a, b, c, d,1);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            nums[i][j]+=nums[i-1][j]+nums[i][j-1]-nums[i-1][j-1];
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(arr[i][j]==0&&nums[i][j]==0){
                cout<<false;
                return 0;
            }
        }
    }
    cout<<true;
    return 0;
}